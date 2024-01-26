#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
// rm
int set_opts(int argc, char *argv[], int *r_flag) {
  const char *short_options = "r";
  int res = 0;

  while ((res = getopt(argc, argv, short_options)) != -1) {
    switch (res) {
      case 'r': {
        *r_flag = 1;  // was seen -p
        break;
      };
      default: {
        return -1;  // something wrong
        break;
      }
    }
  }
  return 0;  // finished without any errors
}

char *cr_name(const char *str, const char *new_name) {
  const unsigned len = 128;
  char* new_str = (char*)malloc(len * sizeof(char));
  for (unsigned i = 0, j = 0, flag = 0;; i += !flag, j += flag) {
    if (!flag && str[i] == '\0') {
      flag = 1;
      new_str[i] = '/';
      continue;
    }
    new_str[i + j] = ((flag) ? new_name[j - 1] : str[i]);
    if (flag && (new_name[j - 1] == '\0')) {
      break;
    }  // криво строится 
  }
  return new_str;
}  // creaking name to remove a dir or file

int r_rm(const char *cur_dir, unsigned r_flag) {
  struct stat buffer;
  if (lstat(cur_dir, &buffer) != 0) {
    perror("lstat\n");
    exit(1);
  }
  if (unlink(cur_dir) != 0) {
    // exit(1);
  }
  if (r_flag && S_ISDIR(buffer.st_mode)) {
    // если это директория
    DIR *dir;
    struct dirent *de;
    dir = opendir(cur_dir);
    while (dir) {
      de = readdir(dir);
      if (!de) {
        break;
      }
      if (strcmp(".", de->d_name) == 0 || strcmp("..", de->d_name) == 0) {
        continue;
      }
      char *cur_str = cr_name(cur_dir, de->d_name);
      // выделяем память и создаём строку с которой сможем удалить директорию
      if (r_rm(cur_str, r_flag) != 0) {
        // что-то не получилось не фартонуло
        // exit(1);
      }
      // printf("%s\n", cur_str);
      free(cur_str);
    }
    closedir(dir);
  }
  if (remove(cur_dir) != 0) {
    // exit(1);
  }
  return (!r_flag && S_ISDIR(buffer.st_mode)) ? -1 : 0;
}

int main(int argc, char *argv[]) {
  int r_flag = 0;
  if (set_opts(argc, argv, &r_flag) == -1) {
    return 1;
    // somthing wrong
  }
  int e_flag = 0;
  for (unsigned i = 1; i < argc; ++i) {
    if (strcmp("-r", argv[i]) == 0) {
      continue;
    }
    e_flag = (r_rm(argv[i], r_flag) == -1) ? 1 : e_flag;
  }
  return (e_flag);
}