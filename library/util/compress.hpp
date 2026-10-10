#pragma once
// @snippet compress
// @desc 座標圧縮: 値を「小さい方から何番目か」に置き換える
#include "base.hpp"

// 座標圧縮: 値を「小さい方から何番目か (0始まり)」に置き換える
//   Compress c(a);  a は vector
//   c.size()        値の種類数
//   c.get(x)        x が小さい方から何番目か (= x より小さい値の種類数)
//   c[i]            i 番目に小さい値 (元の値に戻す)
template <class T>
struct Compress {
  vector<T> vals;  // 重複を除いて昇順に並べた値

  Compress(const vector<T>& a)
      : vals(a) {
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
  }

  int size() const {
    return vals.size();
  }

  int get(const T& x) const {
    return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
  }

  const T& operator[](int i) const {
    return vals[i];
  }
};
