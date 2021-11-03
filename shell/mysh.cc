/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-10-13 15:18:24
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <iomanip>
#include <unordered_map>

using namespace std;

int Launch(char **args);

using BuiltinFun = function<int(const char**)>;

int BuiltinCd(const char** argv) {
  if (argv[1] == nullptr) {
    fprintf(stderr, "wrong args for builtin cd command");
    return 2;
  }

  if (chdir(argv[1]) != 0) {
    perror("fail to change to dir");
  }

  return 1;
}

int BuiltinExit(const char** argv) {
  return 0;
}

static const unordered_map<string, BuiltinFun> kBuiltinFunMap = {
  {"cd", BuiltinCd},
  {"exit", BuiltinExit},
};

char* Readline() {
  char* line = nullptr;
  size_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);
    }
  }

  return line;
}

char** AllocateArgv(char** argv, int* cur_size) {
  static const int kDefaultSize = 64;
  char** res = nullptr;
  *cur_size += kDefaultSize;

  if (argv == nullptr) {
    res = (char**)malloc(kDefaultSize * sizeof(char*));
  } else {
    res = (char**)realloc(argv, *cur_size * sizeof(char*));
  }

  if (res == nullptr) {
    perror("Fail to allocate memory");
    exit(EXIT_FAILURE);
  }

  return res;
}

char** SplitLine(char* line) {
  int bufsize = 0;
  char** argv = AllocateArgv(nullptr, &bufsize);

  static const char* kArgDelim = " \t\r\n";
  int idx = 0;
  char* arg = strtok(line, kArgDelim);
  while (arg != nullptr) {
    argv[idx] = arg;
    idx++;

    if (idx >= bufsize) {
      argv = AllocateArgv(argv, &bufsize);
    }

    arg = strtok(nullptr, kArgDelim);
  }
  argv[idx] = nullptr;

  return argv;
}

int Execute(char** argv) {
  if (argv == nullptr || argv[0] == nullptr) {
    return 1;
  }

  if (kBuiltinFunMap.contains(argv[0])) {
    auto fun = kBuiltinFunMap.at(argv[0]);
    return fun((const char**)argv);
  }

  return Launch(argv);
}

void Loop() {
  int status = 1;
  do {
    std::cout << "> ";
    char* line = Readline();
    char** argv = SplitLine(line);

    status = Execute(argv);

    free(line);
    free(argv);
  } while (status > 0);
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
  // char* cmdline[] = {"echo", "hbliu"};

  Loop();

  return 0;
}
