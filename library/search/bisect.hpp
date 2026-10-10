#pragma once
// @snippet bisect
// @desc めぐる式二分探索: 条件を満たす・満たさないの境目を求める
#include "base.hpp"

// めぐる式二分探索: 条件を満たす値と満たさない値の境目を求める
//   ok:    条件を満たすと分かっている値
//   ng:    条件を満たさないと分かっている値 (ok より大きくても小さくてもよい)
//   check: 値を1つ受け取り、条件を満たすなら true を返す関数
// 戻り値: 条件を満たす値のうち、いちばん ng に近いもの
//   例) a が昇順のとき、a[i] >= x となる最小の i (無ければ n が返る):
//       bisect(n, -1, [&](ll i) { return a[i] >= x; })
template <class F>
ll bisect(ll ok, ll ng, F check) {
  while (abs(ok - ng) > 1) {
    ll mid = ok + (ng - ok) / 2;
    if (check(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  return ok;
}

// 小数版: 境目を 100 回絞り込む
template <class F>
double bisect_real(double ok, double ng, F check) {
  for (int i = 0; i < 100; i++) {
    double mid = (ok + ng) / 2;
    if (check(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  return ok;
}
