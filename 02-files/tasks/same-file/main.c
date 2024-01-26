#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

bool is_same_file(const char *lhs_path, const char *rhs_path) {
  struct stat stat1, stat2;
  if (lstat(lhs_path, &stat1) || lstat(rhs_path, &stat2)) {
    return false;
  }
  if (S_ISLNK(stat1.st_mode) || S_ISLNK(stat2.st_mode)) {
    char *resolved_lhs_path, *resolved_rhs_path;
    resolved_lhs_path = realpath(lhs_path, NULL);
    resolved_rhs_path = realpath(rhs_path, NULL);
    struct stat s_stat1, s_stat2;
    if (access(resolved_lhs_path, F_OK) == -1 ||
        access(resolved_rhs_path, F_OK) == -1 ||
        lstat(resolved_lhs_path, &s_stat1) == -1 ||
        lstat(resolved_rhs_path, &s_stat2) == -1) {
      return false;
    }
    return (!strcmp(resolved_lhs_path, resolved_rhs_path) ||
            s_stat1.st_ino == s_stat2.st_ino);
  } else {
    return stat1.st_ino == stat2.st_ino;
  }
}

int main(int argc, const char **argv) {
  if (argc != 3) {
    return 1;
  }
  printf("%s", (is_same_file(argv[1], argv[2])) ? "yes" : "no");
  return 0;
}
