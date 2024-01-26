#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
  size_t idx;               // current index
  int fd;                   // file discriptor
  unsigned char buffer[6];  // r/w buffer
} utf8_file_t;

int utf8_write(utf8_file_t* f, const unsigned* str, size_t count);
int utf8_read(utf8_file_t* f, unsigned* res, size_t count);
utf8_file_t* utf8_fromfd(int fd);
