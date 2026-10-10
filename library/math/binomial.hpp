#pragma once
// @snippet binomial
// @desc 二項係数 nCr (mod つき、階乗を前計算)
#include "base.hpp"

// 二項係数 (mod つき): 階乗とその逆元を前計算して、nCr などを O(1) で求める。
// T には ACL の modint (atcoder::modint998244353 など) を指定する
//   Binomial<mint> bc(n);   n までの階乗を前計算  O(N)
//   bc.C(n, r)   nCr: n 個から r 個を選ぶ方法の数
//   bc.P(n, r)   nPr: n 個から r 個を選んで並べる方法の数
//   bc.H(n, r)   nHr: n 種類から重複を許して r 個を選ぶ方法の数 (n + r - 1 までの前計算が必要)
//   bc.fact[i]   i の階乗
template <class T>
struct Binomial {
  vector<T> fact, inv_fact;  // 階乗、階乗の逆元

  Binomial(int n)
      : fact(n + 1), inv_fact(n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
      fact[i] = fact[i - 1] * i;
    }
    inv_fact[n] = fact[n].inv();
    for (int i = n; i >= 1; i--) {
      inv_fact[i - 1] = inv_fact[i] * i;
    }
  }

  T C(int n, int r) const {
    if (r < 0 || r > n) {
      return 0;
    }
    return fact[n] * inv_fact[r] * inv_fact[n - r];
  }

  T P(int n, int r) const {
    if (r < 0 || r > n) {
      return 0;
    }
    return fact[n] * inv_fact[n - r];
  }

  T H(int n, int r) const {
    if (n == 0) {
      return r == 0 ? 1 : 0;
    }
    return C(n + r - 1, r);
  }
};
