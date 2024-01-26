#include "lca.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pid_t GetPPid(pid_t kid) {
  const unsigned kSize = 1000;
  char *path = (char *)malloc(kSize * sizeof(char));
  if (path == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  char *line = (char *)malloc(kSize * sizeof(char));
  if (line == NULL) {
    free(path);
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  sprintf(path, "/proc/%d/stat", kid);
  int fd = open(path, O_RDONLY, 0666);
  if (fd == -1) {
    free(path);
    free(line);
    return -1;
  }
  int read_res = read(fd, line, kSize * sizeof(char));
  if (read_res == -1) {
    free(path);
    free(line);
    close(fd);
    perror("read");
    exit(EXIT_FAILURE);
  }
  char *token = strtok(line, " ");
  const unsigned kNum = 3;
  for (unsigned i = 0; i < kNum; ++i) {
    token = strtok(NULL, " ");
  }
  pid_t res = atoi(token);
  close(fd);
  free(path);
  free(line);
  return res;
}

pid_t find_lca(pid_t x, pid_t y) {
  if (x == 1 || x == 0 || y == 1 || y == 0) {
    return (x > y) ? y : x;
  }
  pid_t *path_x = (pid_t *)malloc(MAX_TREE_DEPTH * sizeof(pid_t));
  if (path_x == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  pid_t *path_y = (pid_t *)malloc(MAX_TREE_DEPTH * sizeof(pid_t));
  if (path_y == NULL) {
    free(path_x);
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  unsigned len_x = 0;
  unsigned len_y = 0;
  // Находим путь от процесса x к корню
  while (x != 1 && x != 0 && x != -1 && len_x < MAX_TREE_DEPTH) {
    path_x[len_x++] = x;
    x = GetPPid(x);
  }
  // Находим путь от процесса y к корню
  while (y != 1 && y != 0 && y != -1 && len_y < MAX_TREE_DEPTH) {
    path_y[len_y++] = y;
    y = GetPPid(y);
  }
  unsigned iter_x = (len_x > len_y) * (len_x - len_y);
  unsigned iter_y = (len_x < len_y) * (len_y - len_x);
  while (iter_x < len_x && iter_y < len_y) {
    if (path_x[iter_x++] == path_y[iter_y++]) {
      pid_t tmp = path_x[iter_x - 1];
      free(path_x);
      free(path_y);
      return tmp;
    }
  }
  return 1;
}

/*pid_t GetPPid(pid_t kid) {
  const unsigned kSize = MAX_TREE_DEPTH;
  char *path = (char *)malloc(kSize * sizeof(char));
  if (path == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  char *line = (char *)malloc(kSize * sizeof(char));
  if (line == NULL) {
    free(path);
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  sprintf(path, "/proc/%d/stat", kid);
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    free(path);
    free(line);
    return -1;
  }
  char *read_res = fgets(line, kSize, file);
  char *token = strtok(line, " ");
  const unsigned kNum = 3;
  for (unsigned i = 0; i < kNum; ++i) {
    token = strtok(NULL, " ");
  }
  fclose(file);
  free(path);
  free(line);
  return atoi(token);
}
*/