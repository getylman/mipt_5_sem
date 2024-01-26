#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int get_mode_from_str(char *str) {
  // функия для преобразования параметра -m в число и обработка ошибки ввода
  int mode = 0;
  unsigned len = 0;
  while (str[len] != '\0') {
    if (str[len] < '0' || str[len++] > '9') {
      return -1;  // invalid mode
    }
  }
  if (len == 0) {
    return -2;
  }
  for (unsigned i = len - 1, start = 1; i < len; --i, start *= 8) {
    mode += start * (str[i] - '0');
  }
  return mode;
}  // good

int set_mode(char *str) {
  int tmp_mode = get_mode_from_str(str);
  if (tmp_mode == -1) {
    printf("mkdir: invalid mode %s\n", str);
    return -1;
  }
  if (tmp_mode == -2) {
    printf(
        "mkdir: option requires an argument -- \'--mode\'\nTry \'mkdir "
        "--help\' for more information.\n");
    return -1;
  }
  // пока забьём на проверку переполнения числа прав доступа
  return tmp_mode;
}

int set_opts(int argc, char *argv[], mode_t *cur_mode, int *p_flag) {
  const char *short_options = "pm:";

  const struct option long_options[] = {{"mode", required_argument, NULL, 'm'},
                                        {NULL, 0, NULL, 0}};

  int res = 0;
  int option_index = 0;
  const mode_t default_mode = 0755;  // rwxr-xr-x 493
  *p_flag = 0;                       // has not been mentiond -p

  *cur_mode = default_mode;  // текущие права доступа

  while ((res = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (res) {
      case 'm': {
        int cur_arg = set_mode(optarg);
        if (cur_arg == -1) {
          return -1;  // bad mode
        }
        // пока забьём на проверку переполнения числа прав доступа
        *cur_mode = cur_arg;
        break;
      };
      case 'p': {
        *p_flag = 1;
        break;
      }
    }
  }
  return 0;  // finished without any errors
}

int p_mkdir(const char *str, mode_t cur_mode) {
  const unsigned len_of_str = 128;
  const mode_t default_mode = 0755; // rwxr-xr-x 493
  char *cur_str = malloc(len_of_str * sizeof(char));
  for (unsigned i = 0; ; ++i) {
    if ((str[i] == '/' || str[i] == '\0') && i != 0) {
      cur_str[i] = '\0';
      if (mkdir(cur_str, (str[i] == '\0') ? cur_mode : default_mode) == -1) {
        /// TODO: какая-то обработка ситуации
        // return -1;
      }
      if (str[i] == '\0') {
        break;
      }
    }
    cur_str[i] = str[i];
  }
  free(cur_str);
  return 0;  // finished good
}

int main(int argc, char *argv[]) {
  mode_t cur_mode = 0;
  int p_flag = 0;
  if (set_opts(argc, argv, &cur_mode, &p_flag) != 0) {
    return 1;
    // function finished with error
  }
  for (unsigned i = 1; i < argc; ++i) {
    if (strcmp("--mode", argv[i]) == 0 || strcmp("-m", argv[i]) == 0) {
      ++i;
      // скипаем тк уже обработали все параметры
      continue;
    }
    if (strcmp("-p", argv[i]) == 0) {
      // скипаем тк уже обработали все параметры
      continue;
    }
    if (!p_flag) {
      if (mkdir(argv[i], cur_mode) == -1) {
        /// TODO: обработать этот слечай?
        exit(1);
      }
    } else {
      if (p_mkdir(argv[i], cur_mode) == -1) {
        /// TODO: обработать этот случай?
      }
    }
  } 

  return 0;
}