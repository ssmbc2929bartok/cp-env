#include <bits/stdc++.h>
#include "graph/bfs.hpp"
#include "graph/bfs01.hpp"
#include "graph/dijkstra.hpp"
#include "graph/graph.hpp"
#include "graph/lca.hpp"
#include "graph/topological_sort.hpp"
#include "graph/tree_diameter.hpp"
#include "testutil.hpp"

const ll INF = 4e18;

// 愚直: ワーシャルフロイド法で全頂点間の最短距離を求める (届かないときは INF)
vector<vector<ll>> floyd(const WGraph& g) {
  int n = g.size();
  vector<vector<ll>> d(n, vector<ll>(n, INF));
  for (int v = 0; v < n; v++) {
    d[v][v] = 0;
    for (auto [to, w] : g[v]) {
      d[v][to] = min(d[v][to], w);
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (d[i][k] < INF && d[k][j] < INF) {
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
  }
  return d;
}

// 頂点数 n、辺数 m のランダムなグラフ (多重辺・自己ループあり)。重みは 0 以上 max_w 以下
WGraph random_wgraph(int n, int m, bool directed, ll max_w) {
  WGraph g(n);
  for (int i = 0; i < m; i++) {
    int a = rnd(0, n - 1);
    int b = rnd(0, n - 1);
    ll w = rnd(0, max_w);
    g[a].emplace_back(b, w);
    if (!directed) {
      g[b].emplace_back(a, w);
    }
  }
  return g;
}

Graph drop_weight(const WGraph& wg) {
  Graph g(wg.size());
  for (int v = 0; v < (int)wg.size(); v++) {
    for (auto [to, w] : wg[v]) {
      g[v].push_back(to);
    }
  }
  return g;
}

void test_read() {
  // 1始まりの無向グラフ (既定)
  istringstream in1("1 2\n2 3\n");
  streambuf* old = cin.rdbuf(in1.rdbuf());
  Graph g1 = read_graph(3, 2);
  assert((g1 == Graph{{1}, {0, 2}, {1}}));

  // 0始まりの有向グラフ
  istringstream in2("0 1\n0 2\n2 1\n");
  cin.rdbuf(in2.rdbuf());
  Graph g2 = read_graph(3, 3, true, 0);
  assert((g2 == Graph{{1, 2}, {}, {1}}));

  // 重みつき: 1始まりの無向グラフ、0始まりの有向グラフ
  istringstream in3("1 2 10\n3 1 5000000000\n");
  cin.rdbuf(in3.rdbuf());
  WGraph g3 = read_wgraph(3, 2);
  assert((g3 == WGraph{{{1, 10}, {2, 5000000000LL}}, {{0, 10}}, {{0, 5000000000LL}}}));

  istringstream in4("2 0 7\n");
  cin.rdbuf(in4.rdbuf());
  WGraph g4 = read_wgraph(3, 1, true, 0);
  assert((g4 == WGraph{{}, {}, {{0, 7}}}));
  cin.rdbuf(old);
}

void test_shortest_paths() {
  for (int t = 0; t < 600; t++) {
    int n = rnd(1, 9);
    int m = rnd(0, 14);
    bool directed = rnd(0, 1);
    // 3回に1回ずつ: 重み 1 だけ (bfs)、重み 0 か 1 (bfs01)、大きな重み (dijkstra)
    ll max_w = t % 3 == 2 ? 1000000000000LL : 1;
    WGraph wg = random_wgraph(n, m, directed, max_w);
    if (t % 3 == 0) {
      for (auto& es : wg) {
        for (auto& e : es) {
          e.second = 1;
        }
      }
    }
    auto d = floyd(wg);
    for (int s = 0; s < n; s++) {
      vector<ll> dj = dijkstra(wg, s);
      for (int v = 0; v < n; v++) {
        assert(dj[v] == (d[s][v] == INF ? -1 : d[s][v]));
      }
      if (t % 3 == 0) {
        vector<int> db = bfs(drop_weight(wg), s);
        for (int v = 0; v < n; v++) {
          assert(db[v] == (d[s][v] == INF ? -1 : d[s][v]));
        }
      }
      if (t % 3 != 2) {
        assert(bfs01(wg, s) == dj);
      }
    }
  }
}

void test_topological_sort() {
  for (int t = 0; t < 500; t++) {
    int n = rnd(1, 9);
    // 閉路のないグラフ: 隠した順番 p の「前 → 後ろ」にだけ辺を張る
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end(), test_rng);
    Graph g(n);
    int m = n >= 2 ? rnd(0, 12) : 0;
    for (int i = 0; i < m; i++) {
      int a = rnd(0, n - 2);
      int b = rnd(a + 1, n - 1);
      g[p[a]].push_back(p[b]);
    }
    vector<int> order = topological_sort(g);
    assert((int)order.size() == n);
    vector<int> pos(n, -1);
    for (int i = 0; i < n; i++) {
      assert(pos[order[i]] == -1);  // 同じ頂点は1回だけ
      pos[order[i]] = i;
    }
    for (int v = 0; v < n; v++) {
      for (int to : g[v]) {
        assert(pos[v] < pos[to]);
      }
    }

    // 逆向きの辺を1本足して閉路を作ると、全頂点は並べられない
    if (m > 0) {
      int v = rnd(0, n - 1);
      while (g[v].empty()) {
        v = rnd(0, n - 1);
      }
      g[g[v][0]].push_back(v);
      assert((int)topological_sort(g).size() < n);
    }
  }
  // 自己ループも閉路
  assert(topological_sort(Graph{{0}}).empty());
}

void test_tree() {
  for (int t = 0; t < 500; t++) {
    int n = rnd(1, 20);
    bool weighted = rnd(0, 1);
    WGraph wg(n);
    Graph g(n);
    for (auto [a, b] : random_tree_edges(n)) {
      ll w = weighted ? rnd(0, 1000000000000LL) : 1;
      wg[a].emplace_back(b, w);
      wg[b].emplace_back(a, w);
      g[a].push_back(b);
      g[b].push_back(a);
    }
    auto d = floyd(wg);

    // 直径: 全頂点間の距離の最大値と一致し、返った2頂点の距離がその値になる
    ll best = 0;
    for (int i = 0; i < n; i++) {
      best = max(best, *max_element(d[i].begin(), d[i].end()));
    }
    auto [len, u, v] = tree_diameter(wg);
    assert(len == best && d[u][v] == best);
    if (!weighted) {
      auto [len2, u2, v2] = tree_diameter(g);
      assert(len2 == best && d[u2][v2] == best);
    }

    // LCA: 親を1つずつたどる愚直な方法と突き合わせる
    int root = rnd(0, n - 1);
    vector<int> depth = bfs(g, root);
    vector<int> par(n, -1);
    for (int x = 0; x < n; x++) {
      for (int to : g[x]) {
        if (depth[to] == depth[x] - 1) {
          par[x] = to;
        }
      }
    }
    LCA lca = root == 0 && rnd(0, 1) ? LCA(g) : LCA(g, root);
    assert(lca.depth == depth);
    for (int a = 0; a < n; a++) {
      for (int b = 0; b < n; b++) {
        int x = a;
        int y = b;
        while (x != y) {
          if (depth[x] < depth[y]) {
            swap(x, y);
          }
          x = par[x];
        }
        assert(lca.query(a, b) == x);
        assert(lca.dist(a, b) == depth[a] + depth[b] - 2 * depth[x]);
      }
    }
  }
}

int main() {
  test_read();
  test_shortest_paths();
  test_topological_sort();
  test_tree();
  cout << "OK" << endl;
}
