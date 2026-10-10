#pragma once
// @snippet bit_search
// @desc bit全探索: 2^n 通りの選び方をすべて試す
#include "base.hpp"

// bit全探索: 0 から n-1 のそれぞれを「選ぶ / 選ばない」の 2^n 通りすべてについて、
// f(選んだ番号の一覧) を呼ぶ。n は 20 くらいまで
//   例) bit_search(n, [&](const vector<int>& chosen) { ... });
template <class F>
void bit_search(int n, F f) {
  for (int bit = 0; bit < (1 << n); bit++) {
    vector<int> chosen;
    for (int i = 0; i < n; i++) {
      if (bit >> i & 1) {  // bit の i 桁目が 1 なら、i 番目を選ぶ
        chosen.push_back(i);
      }
    }
    f(chosen);
  }
}
