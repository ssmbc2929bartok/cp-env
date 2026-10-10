#pragma once
// @snippet two_pointers
// @desc 尺取り法: 各左端について、条件を満たす最大の右端を求める
#include "base.hpp"

// 尺取り法: 長さ n の列の各左端 l について、区間 [l, r) が条件を満たす最大の r を求める。
// 「区間を縮めても条件を満たしたまま」という性質がある条件に使える
//   can_add(i): 今の区間の右に i 番目を足しても、条件を満たすか
//   add(i):     i 番目を区間に足す
//   remove(i):  i 番目を区間から外す
// 戻り値: res[l] = 左端が l のときの最大の r
//   例) 和が k 以下の区間 (a の要素は 0 以上)。sum は区間の和を持つ変数:
//       two_pointers(
//           n, [&](int i) { return sum + a[i] <= k; }, [&](int i) { sum += a[i]; },
//           [&](int i) { sum -= a[i]; });
template <class CanAdd, class Add, class Remove>
vector<int> two_pointers(int n, CanAdd can_add, Add add, Remove remove) {
  vector<int> res(n);
  int r = 0;
  for (int l = 0; l < n; l++) {
    while (r < n && can_add(r)) {
      add(r);
      r++;
    }
    res[l] = r;
    if (r == l) {
      r++;  // l 番目だけでも条件を満たさない。区間は空のまま次へ進む
    } else {
      remove(l);
    }
  }
  return res;
}
