#pragma once
// @snippet cumsum
// @desc 1次元累積和: 区間の和を O(1) で求める
#include "base.hpp"

// 1次元累積和: 区間の和を O(1) で求める
//   CumSum cs(a);    a は vector。前計算 O(N)
//   cs.sum(l, r)     a[l] + ... + a[r-1]  (半開区間 [l, r) の和)
struct CumSum {
  vector<ll> s;  // s[i] = a[0] + ... + a[i-1]

  template <class T>
  CumSum(const vector<T>& a)
      : s(a.size() + 1, 0) {
    for (int i = 0; i < (int)a.size(); i++) {
      s[i + 1] = s[i] + a[i];
    }
  }

  ll sum(int l, int r) const {
    return s[r] - s[l];
  }
};
