#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { MAX_ARGS_COUNT = 256, MAX_CHAIN_LINKS_COUNT = 256 };

typedef struct {
  char *command;
  uint64_t argc;
  char *argv[MAX_ARGS_COUNT];
} chain_link_t;

typedef struct {
  uint64_t chain_links_count;
  chain_link_t chain_links[MAX_CHAIN_LINKS_COUNT];
} chain_t;

void create_chain(char *command, chain_t *chain) {
  unsigned index = 0;
  char *token = strtok(command, "|");
  while (token != NULL) {
    chain->chain_links[index++].command = token;
    token = strtok(NULL, "|");
  }
  chain->chain_links_count = index;
}

void run_command(char *command) {
  char **args = (char **)malloc(MAX_ARGS_COUNT * sizeof(char *));
  if (args == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  char *token = strtok(command, " ");
  for (unsigned i = 0; token != NULL || (args[i] = NULL); ++i) {
    args[i] = token;
    token = strtok(NULL, " ");
  }
  execvp(args[0], args);
  free(args);
}

void run_chain(chain_t *chain) {
  int cur_pipe[2];
  int keeped_pipe[2];

  for (unsigned i = 0; i < chain->chain_links_count; ++i) {
    if (i < chain->chain_links_count - 1 && pipe(cur_pipe)) {
      exit(1);
    }
    pid_t pid = fork();
    if (pid == 0) {
      if (i > 0) {
        dup2(keeped_pipe[0], STDIN_FILENO);
        close(keeped_pipe[0]);
        close(keeped_pipe[1]);
      }
      if (i < chain->chain_links_count - 1) {
        dup2(cur_pipe[1], STDOUT_FILENO);
        close(cur_pipe[0]);
        close(cur_pipe[1]);
      }
      run_command(chain->chain_links[i].command);
      exit(1);
    }
    if (i > 0) {
      close(keeped_pipe[0]);
      close(keeped_pipe[1]);
    }
    if (i < chain->chain_links_count - 1) {
      keeped_pipe[0] = cur_pipe[0];
      keeped_pipe[1] = cur_pipe[1];
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    perror("argc != 2");
    exit(EXIT_FAILURE);
  }
  chain_t chain;
  create_chain(argv[1], &chain);
  run_chain(&chain);
  return 0;
}
