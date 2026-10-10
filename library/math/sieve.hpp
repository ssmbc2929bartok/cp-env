#pragma once
// @snippet sieve
// @desc エラトステネスの篩: 素数判定・素数の列挙・高速な素因数分解
#include "base.hpp"

// エラトステネスの篩: n 以下の数について、素数判定と素因数分解を高速に行う
//   Sieve sv(n);        前計算 O(N log log N)。n は 10^7 くらいまで
//   sv.is_prime(x)      x が素数か  O(1)
//   sv.primes           n 以下の素数の一覧 (昇順)
//   sv.factorize(x)     x の素因数分解 {(素因数, 指数), ...} (素因数の昇順)  O(log x)
struct Sieve {
  vector<int> min_factor;  // min_factor[x] = x の最小の素因数 (x >= 2)
  vector<int> primes;

  Sieve(int n)
      : min_factor(n + 1, 0) {
    for (int i = 2; i <= n; i++) {
      if (min_factor[i] != 0) {
        continue;  // i は合成数
      }
      min_factor[i] = i;
      primes.push_back(i);
      for (ll j = (ll)i * i; j <= n; j += i) {
        if (min_factor[j] == 0) {
          min_factor[j] = i;
        }
      }
    }
  }

  bool is_prime(int x) const {
    return x >= 2 && min_factor[x] == x;
  }

  vector<pair<int, int>> factorize(int x) const {
    vector<pair<int, int>> res;
    while (x > 1) {
      int p = min_factor[x];
      int e = 0;
      while (x % p == 0) {
        x /= p;
        e++;
      }
      res.emplace_back(p, e);
    }
    return res;
  }
};
