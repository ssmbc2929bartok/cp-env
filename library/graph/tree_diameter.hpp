#pragma once
// @snippet tree_diameter
// @desc 木の直径: いちばん遠い2頂点とその距離
#include "base.hpp"
#include "graph.hpp"

// 木の直径: いちばん遠い2頂点の組を求める。(距離, 端点 u, 端点 v) を返す。
// 重みなしの木 (Graph) では距離は辺の本数、重みつきの木 (WGraph) では重みの和 (重みは 0 以上)
tuple<ll, int, int> tree_diameter(const WGraph& g) {
  // s からいちばん遠い頂点と、そこまでの距離
  auto farthest = [&](int s) {
    vector<ll> dist(g.size(), -1);
    vector<int> st = {s};
    dist[s] = 0;
    while (!st.empty()) {
      int v = st.back();
      st.pop_back();
      for (auto [to, w] : g[v]) {
        if (dist[to] == -1) {
          dist[to] = dist[v] + w;
          st.push_back(to);
        }
      }
    }
    int t = max_element(dist.begin(), dist.end()) - dist.begin();
    return pair<ll, int>(dist[t], t);
  };

  // 適当な頂点からいちばん遠い頂点 u は、直径の端点になる
  int u = farthest(0).second;
  auto [d, v] = farthest(u);
  return {d, u, v};
}

tuple<ll, int, int> tree_diameter(const Graph& g) {
  WGraph wg(g.size());
  for (int v = 0; v < (int)g.size(); v++) {
    for (int to : g[v]) {
      wg[v].emplace_back(to, 1);
    }
  }
  return tree_diameter(wg);
}
