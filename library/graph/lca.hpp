#pragma once
// @snippet lca
// @desc 最小共通祖先 (LCA) と、木の上の2頂点の距離
#include "base.hpp"
#include "graph.hpp"

// 最小共通祖先 (LCA): 根つき木で、2頂点の共通の祖先のうち、いちばん深いものを求める
//   LCA lca(g, root);    前計算 O(N log N)。root を省略すると頂点 0
//   lca.query(u, v)      u と v の LCA  O(log N)
//   lca.dist(u, v)       u と v の距離 (辺の本数)
//   lca.depth[v]         根から v までの距離
struct LCA {
  int lg;                      // 2^lg >= 頂点数
  vector<int> depth;           // 根からの距離
  vector<vector<int>> parent;  // parent[k][v] = v から親を 2^k 回たどった頂点 (根より上は根)

  LCA(const Graph& g, int root = 0) {
    int n = g.size();
    lg = 1;
    while ((1 << lg) < n) {
      lg++;
    }
    depth.assign(n, -1);
    parent.assign(lg, vector<int>(n, root));

    queue<int> q;
    depth[root] = 0;
    q.push(root);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int to : g[v]) {
        if (depth[to] == -1) {
          depth[to] = depth[v] + 1;
          parent[0][to] = v;
          q.push(to);
        }
      }
    }
    for (int k = 0; k + 1 < lg; k++) {
      for (int v = 0; v < n; v++) {
        parent[k + 1][v] = parent[k][parent[k][v]];
      }
    }
  }

  int query(int u, int v) const {
    if (depth[u] < depth[v]) {
      swap(u, v);
    }
    // 深い方の u を、v と同じ深さまで上げる
    int diff = depth[u] - depth[v];
    for (int k = 0; k < lg; k++) {
      if (diff >> k & 1) {
        u = parent[k][u];
      }
    }
    if (u == v) {
      return u;
    }
    // 2頂点が一致する直前まで、同時に上げる
    for (int k = lg - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }

  int dist(int u, int v) const {
    return depth[u] + depth[v] - 2 * depth[query(u, v)];
  }
};
