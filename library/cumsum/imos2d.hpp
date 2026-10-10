#pragma once
// @snippet imos2d
// @desc 2次元imos法: 長方形の範囲への加算をまとめて行う
#include "base.hpp"

// 2次元imos法: 「長方形の範囲に x を足す」を何度も行ったあと、各マスの値をまとめて求める
//   Imos2D im(h, w);                     h 行 w 列、最初はすべて 0
//   im.add(i1, j1, i2, j2, x);           行が [i1, i2)、列が [j1, j2) の範囲に x を足す  O(1)
//   vector<vector<ll>> v = im.build();   v[i][j] = マス (i, j) の値  O(HW)
struct Imos2D {
  int h, w;
  vector<vector<ll>> d;  // 差分

  Imos2D(int h, int w)
      : h(h), w(w), d(h + 1, vector<ll>(w + 1, 0)) {}

  void add(int i1, int j1, int i2, int j2, ll x = 1) {
    d[i1][j1] += x;
    d[i1][j2] -= x;
    d[i2][j1] -= x;
    d[i2][j2] += x;
  }

  vector<vector<ll>> build() const {
    vector<vector<ll>> res(h, vector<ll>(w, 0));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        res[i][j] = d[i][j];
        if (i > 0) {
          res[i][j] += res[i - 1][j];
        }
        if (j > 0) {
          res[i][j] += res[i][j - 1];
        }
        if (i > 0 && j > 0) {
          res[i][j] -= res[i - 1][j - 1];
        }
      }
    }
    return res;
  }
};
