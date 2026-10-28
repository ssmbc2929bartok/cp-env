#include <bits/stdc++.h>
#include "geometry/angle_sort.hpp"
#include "testutil.hpp"

// 愚直: 偏角を atan2 で求めて [0, 2π) に直す。原点は -1 (先頭)
double naive_angle(pair<ll, ll> p) {
  if (p == pair<ll, ll>{0, 0}) {
    return -1;
  }
  double t = atan2((double)p.second, (double)p.first);
  return t < 0 ? t + 2 * M_PI : t;
}

// 愚直な比較。向きが同じか (x / g, y / g が一致するか) は整数で判定し、違う向きは atan2 の値で比べる。
// 座標の絶対値が 10 以下なら、違う向きの偏角は 0.005 以上離れているので、誤差で順番が入れ替わらない
bool naive_less(pair<ll, ll> a, pair<ll, ll> b) {
  auto dir = [](pair<ll, ll> p) {
    ll g = gcd(abs(p.first), abs(p.second));
    return g == 0 ? p : pair<ll, ll>{p.first / g, p.second / g};
  };
  if (dir(a) == dir(b)) {
    return false;
  }
  return naive_angle(a) < naive_angle(b);
}

void test_angle_sort_fixed() {
  // 原点、x 軸の正の向きから反時計回りに8方向
  vector<pair<ll, ll>> expected = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
  for (int t = 0; t < 100; t++) {
    auto ps = expected;
    shuffle(ps.begin(), ps.end(), test_rng);
    angle_sort(ps);
    assert(ps == expected);
  }
}

void test_angle_sort_random() {
  for (int t = 0; t < 300; t++) {
    int n = rnd(0, 30);
    ll r = rnd(1, 10);  // 範囲が狭いと、重なる点・同じ向きの点・原点が多く出る
    vector<pair<ll, ll>> ps(n);
    for (auto& [x, y] : ps) {
      x = rnd(-r, r);
      y = rnd(-r, r);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        assert(angle_less(ps[i], ps[j]) == naive_less(ps[i], ps[j]));
      }
    }

    // 並べ替えたあとも同じ点の集まりで、偏角の順になっている
    auto sorted = ps;
    angle_sort(sorted);
    auto a = ps, b = sorted;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    assert(a == b);
    for (int i = 0; i + 1 < n; i++) {
      assert(!naive_less(sorted[i + 1], sorted[i]));
    }

    // 添字を並べる使い方
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) { return angle_less(ps[i], ps[j]); });
    for (int i = 0; i + 1 < n; i++) {
      assert(!naive_less(ps[idx[i + 1]], ps[idx[i]]));
    }
  }
}

void test_angle_sort_large() {
  // 座標が 10^9 でも、外積を long long で計算するので int の点で正しく比べられる。
  // a と b の偏角の差は約 10^-18 で、atan2 (double) では区別できない
  const int m = 1000000000;
  pair<int, int> a = {m, m - 1}, b = {m - 1, m - 2};
  assert(angle_less(b, a) && !angle_less(a, b));
  pair<int, int> na = {-a.first, -a.second}, nb = {-b.first, -b.second};
  assert(angle_less(nb, na) && !angle_less(na, nb));
  // 同じ向きは、どちらも小さくない
  assert(!angle_less(pair<int, int>{m, m}, pair<int, int>{1, 1}));
  assert(!angle_less(pair<int, int>{1, 1}, pair<int, int>{m, m}));
  // 正反対の向き
  assert(angle_less(pair<int, int>{m, m}, pair<int, int>{-m, -m}));
  assert(angle_less(pair<int, int>{-m, m}, pair<int, int>{m, -m}));

  vector<pair<int, int>> expected = {{0, 0}, {m, 0}, b, a, {0, m}, {-m, 0}, {0, -m}, {m, -1}};
  for (int t = 0; t < 100; t++) {
    auto ps = expected;
    shuffle(ps.begin(), ps.end(), test_rng);
    angle_sort(ps);
    assert(ps == expected);
  }
}

int main() {
  test_angle_sort_fixed();
  test_angle_sort_random();
  test_angle_sort_large();
  cout << "OK" << endl;
}
