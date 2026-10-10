#pragma once
// @snippet factorize
// @desc 素因数分解 (試し割り): O(√n)
#include "base.hpp"

// 素因数分解 (試し割り): n を {(素因数, 指数), ...} に分解する (素因数の昇順)。O(√n)
//   例) factorize(360) → {(2, 3), (3, 2), (5, 1)}
vector<pair<ll, int>> factorize(ll n) {
  vector<pair<ll, int>> res;
  for (ll p = 2; p * p <= n; p++) {
    if (n % p != 0) {
      continue;
    }
    int e = 0;
    while (n % p == 0) {
      n /= p;
      e++;
    }
    res.emplace_back(p, e);
  }
  if (n > 1) {
    res.emplace_back(n, 1);  // 残った数は、√n より大きい素因数
  }
  return res;
}
