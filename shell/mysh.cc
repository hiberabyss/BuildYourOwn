/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-10-13 15:18:24
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <ranges>
#include <iomanip>

using namespace std;

char* readline() {
  char* line = nullptr;
  size_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);
    }
  }

  return line;
}

void Loop() {
  int status = 1;
  do {
    std::cout << "> ";
    char* line = readline();
    printf("%s", line);
    // getline(cin, line);

    free(line);
  } while (status);
}

int Launch(char **args) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fail to fork command");
    return 1;
  }

  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("fail to exec command");
    }
    exit(EXIT_SUCCESS);
  } else {
    // Parent process
    int status;
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int main(int argc, char *argv[]) {
  char* cmdline[] = {"echo", "hbliu"};

  Loop();
  // Launch(cmdline);
  // std::cout << "Hello" << std::endl;
  return 0;
}
