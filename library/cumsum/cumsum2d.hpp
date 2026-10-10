#pragma once
// @snippet cumsum2d
// @desc 2次元累積和: 長方形の範囲の和を O(1) で求める
#include "base.hpp"

// 2次元累積和: 長方形の範囲の和を O(1) で求める
//   CumSum2D cs(a);            a は h 行 w 列の vector<vector<...>>。前計算 O(HW)
//   cs.sum(i1, j1, i2, j2)     行が [i1, i2)、列が [j1, j2) の範囲の和
struct CumSum2D {
  vector<vector<ll>> s;  // s[i][j] = 行が [0, i)、列が [0, j) の範囲の和

  template <class T>
  CumSum2D(const vector<vector<T>>& a) {
    int h = a.size();
    int w = h == 0 ? 0 : a[0].size();
    s.assign(h + 1, vector<ll>(w + 1, 0));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + a[i][j];
      }
    }
  }

  ll sum(int i1, int j1, int i2, int j2) const {
    return s[i2][j2] - s[i1][j2] - s[i2][j1] + s[i1][j1];
  }
};
