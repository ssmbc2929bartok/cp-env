#pragma once
// @snippet topological_sort
// @desc トポロジカルソート (閉路の検出もできる)
#include "base.hpp"
#include "graph.hpp"

// トポロジカルソート: 有向グラフの頂点を、どの辺も「前 → 後ろ」の向きになる順に並べて返す。
// 閉路があると全頂点を並べられないので、返る列の長さが頂点数より短くなる
vector<int> topological_sort(const Graph& g) {
  int n = g.size();
  vector<int> indeg(n, 0);  // 入ってくる辺の本数
  for (int v = 0; v < n; v++) {
    for (int to : g[v]) {
      indeg[to]++;
    }
  }

  queue<int> q;
  for (int v = 0; v < n; v++) {
    if (indeg[v] == 0) {
      q.push(v);
    }
  }

  vector<int> order;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    order.push_back(v);
    for (int to : g[v]) {
      if (--indeg[to] == 0) {
        q.push(to);
      }
    }
  }
  return order;
}
