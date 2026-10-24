#pragma once
// @snippet angle_sort
// @desc 偏角ソート: 外積で比べる (整数座標なら誤差なし)
#include "base.hpp"

// 偏角ソート: 点 (x, y) を、原点から見た偏角の小さい順に並べる。O(n log n)
//   偏角は x 軸の正の向きを 0 とし、反時計回りに [0, 2π) で数える
//   外積で比べるので、整数座標なら誤差が出ない (座標の絶対値は 10^9 以下)
//   原点 (0, 0) は先頭に置く。偏角が同じ点どうしの順番は決めていない
//   angle_sort(ps);    ps は vector<pair<ll, ll>> など
//   angle_less(a, b)   a の偏角が b より小さいか (添字を並べるときに使う)

// 点がどちら側にあるか: 0 は原点、1 は偏角 [0, π)、2 は偏角 [π, 2π)
template <class T>
int angle_half(const pair<T, T>& p) {
  auto [x, y] = p;
  if (x == 0 && y == 0) {
    return 0;
  }
  return (y > 0 || (y == 0 && x > 0)) ? 1 : 2;
}

template <class T>
bool angle_less(const pair<T, T>& a, const pair<T, T>& b) {
  int ha = angle_half(a), hb = angle_half(b);
  if (ha != hb) {
    return ha < hb;
  }
  // 同じ側にある2点は偏角の差が π 未満なので、外積 a × b が正なら a の方が小さい
  return (ll)a.first * b.second - (ll)a.second * b.first > 0;
}

template <class T>
void angle_sort(vector<pair<T, T>>& ps) {
  sort(ps.begin(), ps.end(), angle_less<T>);
}
