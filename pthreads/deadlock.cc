/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-11-22 10:34:04
 */

#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* arg) {
  pthread_mutex_lock(&mtx1);
  std::cout << "Get mtx1" << std::endl;
  sleep(2);
  pthread_mutex_lock(&mtx2);

  pthread_mutex_unlock(&mtx2);
  pthread_mutex_unlock(&mtx1);

  std::cout << "Thread1 finished" << std::endl;
}

void* thread2(void* arg) {
  pthread_mutex_lock(&mtx2);
  std::cout << "Get mtx2" << std::endl;
  sleep(2);
  pthread_mutex_lock(&mtx1);

  pthread_mutex_unlock(&mtx1);
  pthread_mutex_unlock(&mtx2);

  std::cout << "Thred2 finished" << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "PID: " << getpid() << std::endl;
  pthread_t tid[2];
  if (pthread_create(&tid[0], nullptr, thread1, nullptr) != 0) {
    cerr << "Fail to create thread1";
    return 1;
  }

  if (pthread_create(&tid[1], nullptr, thread2, nullptr) != 0) {
    cerr << "Fail to create thread2";
    return 1;
  }

  for (size_t i = 0; i < sizeof(tid); ++i) {
    pthread_join(tid[i], nullptr);
  }

  pthread_mutex_destroy(&mtx1);
  pthread_mutex_destroy(&mtx2);
  return 0;
}
