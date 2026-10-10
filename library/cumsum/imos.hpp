#pragma once
// @snippet imos
// @desc 1次元imos法: 区間への加算をまとめて行う
#include "base.hpp"

// 1次元imos法: 「区間に x を足す」を何度も行ったあと、各位置の値をまとめて求める
//   Imos im(n);                 長さ n、最初はすべて 0
//   im.add(l, r, x);            区間 [l, r) に x を足す (x を省略すると 1)  O(1)
//   vector<ll> v = im.build();  v[i] = 位置 i の値  O(N)
struct Imos {
  vector<ll> d;  // 差分 (区間の始まりで +x、終わりの次で -x)

  Imos(int n)
      : d(n + 1, 0) {}

  void add(int l, int r, ll x = 1) {
    d[l] += x;
    d[r] -= x;
  }

  vector<ll> build() const {
    vector<ll> res(d.begin(), d.end() - 1);
    for (int i = 1; i < (int)res.size(); i++) {
      res[i] += res[i - 1];
    }
    return res;
  }
};
