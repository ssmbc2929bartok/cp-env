#pragma once
// @snippet dijkstra
// @desc Dijkstra法: 非負重みの最短距離
#include "base.hpp"
#include "graph.hpp"

// Dijkstra法: 頂点 s から各頂点への最短距離を返す (辺の重みは 0 以上)。届かない頂点は -1
vector<ll> dijkstra(const WGraph& g, int s) {
  vector<ll> dist(g.size(), -1);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
  dist[s] = 0;
  pq.emplace(0, s);
  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (d > dist[v]) {
      continue;  // もっと短い距離で処理済み
    }
    for (auto [to, w] : g[v]) {
      if (dist[to] == -1 || dist[to] > d + w) {
        dist[to] = d + w;
        pq.emplace(dist[to], to);
      }
    }
  }
  return dist;
}
