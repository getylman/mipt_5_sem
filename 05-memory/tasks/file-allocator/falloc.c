#include "falloc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void falloc_init(file_allocator_t *allocator, const char *filepath,
                 uint64_t allowed_page_count) {
  allocator->allowed_page_count = allowed_page_count;

  int file_exists = access(filepath, F_OK) != -1;
  // Проверяем существование файла
  const size_t kPageMaskSize = PAGE_MASK_SIZE * sizeof(uint64_t);
  const size_t kFileSize = PAGE_SIZE * allowed_page_count;
  const uint64_t kNumOfBits = 64;

  int fd = open(filepath, O_CREAT | O_RDWR, 0666);
  if (fd < 0 ||
      (!file_exists && ftruncate(fd, kFileSize + kPageMaskSize) < 0)) {
    perror("open or ftruncate");
    exit(EXIT_FAILURE);
  }
  // Получаем отображение файла в память
  allocator->base_addr = mmap(NULL, kFileSize + kPageMaskSize,
                              PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (allocator->base_addr == MAP_FAILED) {
    perror("base_addr mmap");
    exit(EXIT_FAILURE);
  }
  allocator->fd = fd;
  allocator->page_mask = (uint64_t *)(allocator->base_addr + kFileSize);

  // Все страницы будут доступны для выделения
  if (!file_exists) {
    allocator->curr_page_count = 0;
    return;
  }
  for (uint64_t i = 0; i <= allowed_page_count / kNumOfBits; ++i) {
    for (uint64_t j = 0; j < kNumOfBits; ++j) {
      allocator->curr_page_count += !!(allocator->page_mask[i] & (1ULL << j));
    }
  }
  if (allocator->curr_page_count > allowed_page_count) {
    allocator->curr_page_count = allowed_page_count;
  }
}

void falloc_destroy(file_allocator_t *allocator) {
  munmap(allocator->base_addr, allocator->allowed_page_count * PAGE_SIZE +
                                   PAGE_MASK_SIZE * sizeof(uint64_t));
  // Освобождаем память, отображенную на файл
  close(allocator->fd);
  allocator->base_addr = allocator->page_mask = NULL;
}

void *falloc_acquire_page(file_allocator_t *allocator) {
  if (allocator->allowed_page_count == allocator->curr_page_count) {
    return NULL;
  }
  const uint64_t kNumOfBits = sizeof(uint64_t) * 8;
  for (uint64_t i = 0; i <= allocator->allowed_page_count / kNumOfBits; ++i) {
    if (allocator->page_mask[i] < UINT64_MAX) {
      for (uint64_t j = 0; j < kNumOfBits; ++j) {
        if ((allocator->page_mask[i] & (1ULL << j))) {
          continue;
        }
        allocator->page_mask[i] |= (1ULL << j);
        ++allocator->curr_page_count;
        return (void *)((char *)allocator->base_addr +
                        (i * kNumOfBits + j) * PAGE_SIZE);
      }
    }
  }
  return NULL;
}

void falloc_release_page(file_allocator_t *allocator, void **addr) {
  const uint64_t kSizeOfByte = 8;
  uintptr_t address = (uintptr_t)(*addr) - (uintptr_t)allocator->base_addr;
  const size_t kPageNumber = address / PAGE_SIZE;
  const size_t kIndex = kPageNumber / (sizeof(uint64_t) * kSizeOfByte);
  const size_t kBitPosition = kPageNumber % (sizeof(uint64_t) * kSizeOfByte);

  allocator->page_mask[kIndex] &= ~(1ULL << kBitPosition);
  --allocator->curr_page_count;
  *addr = NULL;
}
