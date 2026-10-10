#pragma once
// @snippet bfs01
// @desc 0-1 BFS: 重みが 0 か 1 の最短距離
#include "base.hpp"
#include "graph.hpp"

// 0-1 BFS: 辺の重みが 0 か 1 だけのグラフで、頂点 s から各頂点への最短距離を返す。
// 届かない頂点は -1
vector<ll> bfs01(const WGraph& g, int s) {
  vector<ll> dist(g.size(), -1);
  deque<int> dq;
  dist[s] = 0;
  dq.push_back(s);
  while (!dq.empty()) {
    int v = dq.front();
    dq.pop_front();
    for (auto [to, w] : g[v]) {
      ll nd = dist[v] + w;
      if (dist[to] == -1 || dist[to] > nd) {
        dist[to] = nd;
        // 重み 0 の辺の先は、今と同じ距離なので先頭に入れる
        if (w == 0) {
          dq.push_front(to);
        } else {
          dq.push_back(to);
        }
      }
    }
  }
  return dist;
}
