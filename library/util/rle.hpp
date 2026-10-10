#pragma once
// @snippet rle
// @desc ランレングス圧縮: 連続する同じ値を (値, 個数) にまとめる
#include "base.hpp"

// ランレングス圧縮: 同じ値が続く部分を (値, 個数) にまとめる。string にも vector にも使える
//   s = "aaabcc" のとき rle(s) → {('a', 3), ('b', 1), ('c', 2)}
template <class C>
vector<pair<typename C::value_type, int>> rle(const C& s) {
  vector<pair<typename C::value_type, int>> res;
  for (const auto& x : s) {
    if (!res.empty() && res.back().first == x) {
      res.back().second++;
    } else {
      res.emplace_back(x, 1);
    }
  }
  return res;
}
