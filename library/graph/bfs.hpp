#pragma once
// @snippet bfs
// @desc 幅優先探索: 始点からの最短距離 (辺の本数)
#include "base.hpp"
#include "graph.hpp"

// 幅優先探索: 頂点 s から各頂点への最短距離 (辺の本数) を返す。届かない頂点は -1
vector<int> bfs(const Graph& g, int s) {
  vector<int> dist(g.size(), -1);
  queue<int> q;
  dist[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int to : g[v]) {
      if (dist[to] == -1) {
        dist[to] = dist[v] + 1;
        q.push(to);
      }
    }
  }
  return dist;
}
