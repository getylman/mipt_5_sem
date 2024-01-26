#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int rw_file(char *buffer, unsigned long long file_size, int fd,
            int with_flush) {
  if (read(fd, buffer, file_size) == -1) {
    return 1; // не смогли прочесть
  }
  buffer[file_size] = '\0';
  // записали с файла в buffer
  if (with_flush) {
    fflush(stdout);
  }
  if (write(STDOUT_FILENO, buffer, strlen(buffer)) == -1) {
    return 2;
  }
  return 0; // если никак не упал то вернётся 0
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    return 1;
  }
  off_t file_size = lseek(fd, 0, SEEK_SET);
  char *buffer = (char *)malloc(file_size * sizeof(char));
  char *new_buffer = NULL;
  off_t new_file_size = 0;
  lseek(fd, 0, SEEK_SET);
  // выделили память под buffer
  if (rw_file(buffer, file_size, fd, 0) != 0) {
    free(buffer);
    close(fd);
    return 1;
  }
  fflush(stdout);

  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = SIG_DFL;
  sigaction(SIGTERM, &sa, NULL);

  for (;;) {
    new_file_size = lseek(fd, 0, SEEK_END);
    if (new_file_size <= file_size) {
      fflush(stdout); // сброс буфера потока вывода
      continue;
    }
    lseek(fd, file_size, SEEK_SET);
    new_buffer = (char *)malloc((new_file_size - file_size + 1) * sizeof(char));
    if (new_buffer == NULL) {
      perror("malloc");
      free(buffer);
      close(fd);
      return 1;
    }
    if (rw_file(new_buffer, new_file_size - file_size, fd, 1) != 0) {
      break;
    }
    file_size = new_file_size;
    free(new_buffer);
    fflush(stdout); // сброс буфера потока вывода
  }
  if (new_buffer != NULL) {
    free(new_buffer);
  }
  free(buffer);
  close(fd);
  return 1;
}
