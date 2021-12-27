/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-12-27 11:06:01
 */

#ifndef SINGLETON_H_ZJOWZUKC
#define SINGLETON_H_ZJOWZUKC

template<typename C>
class Singleton {
public:
  Singleton () = delete;
  Singleton& operator= (const Singleton& s) = delete;
  Singleton (const Singleton& s) = delete;
  ~Singleton () {}

  static C* GetInstance() {
    static C instance;
    return &instance;
  }

private:
};

#endif /* end of include guard: SINGLETON_H_ZJOWZUKC */
