#pragma once
// @snippet xorshift
// @desc xorshift 乱数 (AHC 用の速い乱数)
#include "base.hpp"

// xorshift 乱数: mt19937 より速い乱数。焼きなまし法など、乱数を大量に使うとき用
//   XorShift rng;
//   rng.next_int(n)       0 以上 n 未満の整数
//   rng.next_int(l, r)    l 以上 r 未満の整数
//   rng.next_double()     0 以上 1 未満の小数
struct XorShift {
  uint64_t x = 88172645463325252ULL;

  uint64_t next() {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
  }

  int next_int(int n) {
    return next() % n;
  }

  int next_int(int l, int r) {
    return l + next_int(r - l);
  }

  double next_double() {
    return (next() >> 11) * (1.0 / (1ULL << 53));
  }
};
