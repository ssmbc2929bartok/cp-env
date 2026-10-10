#pragma once
// @snippet graph
// @desc グラフ型 (Graph / WGraph) と辺の読み込み。頂点は0始まり
#include "base.hpp"

// グラフ型 (隣接リスト)。頂点番号は 0 始まり
//   Graph:  g[v] = v から辺で行ける頂点の一覧
//   WGraph: g[v] = (行き先, 辺の重み) の一覧
using Graph = vector<vector<int>>;
using WGraph = vector<vector<pair<int, ll>>>;

// 辺 (a b) を m 本読み込んで、頂点数 n のグラフを作る
//   directed: true なら有向グラフ (a → b だけを張る)
//   offset:   入力の頂点番号から引く数。1始まりの入力なら 1、0始まりなら 0
Graph read_graph(int n, int m, bool directed = false, int offset = 1) {
  Graph g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a -= offset;
    b -= offset;
    g[a].push_back(b);
    if (!directed) {
      g[b].push_back(a);
    }
  }
  return g;
}

// 重みつきの辺 (a b c) を m 本読み込んで、頂点数 n のグラフを作る
WGraph read_wgraph(int n, int m, bool directed = false, int offset = 1) {
  WGraph g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    a -= offset;
    b -= offset;
    g[a].emplace_back(b, c);
    if (!directed) {
      g[b].emplace_back(a, c);
    }
  }
  return g;
}
