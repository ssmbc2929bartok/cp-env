#pragma once
// テスト用の小道具。乱数の種を固定しているので、何度実行しても同じ入力になる
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 test_rng(20261011);

// l 以上 r 以下の整数
ll rnd(ll l, ll r) {
  return l + (ll)(test_rng() % (unsigned long long)(r - l + 1));
}

// 頂点数 n のランダムな木の辺 (親 → 子)。頂点番号は混ぜてある。
// 形は3種類から選ぶ: 親を全体から選ぶ (浅い木)、直前の3頂点から選ぶ (深い木)、一直線
vector<pair<int, int>> random_tree_edges(int n) {
  vector<int> id(n);
  iota(id.begin(), id.end(), 0);
  shuffle(id.begin(), id.end(), test_rng);
  int shape = rnd(0, 2);
  vector<pair<int, int>> edges;
  for (int i = 1; i < n; i++) {
    int lo = shape == 0 ? 0 : (shape == 1 ? max(0, i - 3) : i - 1);
    edges.emplace_back(id[rnd(lo, i - 1)], id[i]);
  }
  return edges;
}
