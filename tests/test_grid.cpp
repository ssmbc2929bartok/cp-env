#include <bits/stdc++.h>
#include "grid/grid_bfs.hpp"
#include "grid/inside.hpp"
#include "testutil.hpp"
#include "util/dxdy8.hpp"

void test_dxdy8() {
  // 8方向がすべて違い、どれも隣のマス
  set<pair<int, int>> dirs;
  for (int d = 0; d < 8; d++) {
    assert(max(abs(dx[d]), abs(dy[d])) == 1);
    dirs.emplace(dx[d], dy[d]);
  }
  assert(dirs.size() == 8);
}

void test_inside() {
  for (int h = 1; h <= 4; h++) {
    for (int w = 1; w <= 4; w++) {
      int cnt = 0;
      for (int i = -2; i <= h + 1; i++) {
        for (int j = -2; j <= w + 1; j++) {
          bool expected = !(i < 0 || i >= h || j < 0 || j >= w);
          assert(inside(i, j, h, w) == expected);
          cnt += inside(i, j, h, w);
        }
      }
      assert(cnt == h * w);
    }
  }
}

void test_grid_bfs() {
  for (int t = 0; t < 400; t++) {
    int h = rnd(1, 7);
    int w = rnd(1, 7);
    char wall = t % 2 == 0 ? '#' : 'x';
    vector<string> grid(h, string(w, '.'));
    vector<pair<int, int>> cells;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (rnd(0, 3) == 0) {
          grid[i][j] = wall;
        } else {
          cells.emplace_back(i, j);
        }
      }
    }
    vector<pair<int, int>> starts;
    for (auto c : cells) {
      if (rnd(0, 5) == 0) {
        starts.push_back(c);
      }
    }
    if (!starts.empty() && rnd(0, 1) == 0) {
      starts.push_back(starts[0]);  // 同じ始点が2回あってもよい
    }

    auto dist = wall == '#' ? grid_bfs(grid, starts) : grid_bfs(grid, starts, wall);

    // 愚直: 変化がなくなるまで、隣のマスから距離を伝え続ける
    const int INF = 1e9;
    vector<vector<int>> naive(h, vector<int>(w, INF));
    for (auto [i, j] : starts) {
      naive[i][j] = 0;
    }
    for (bool changed = true; changed;) {
      changed = false;
      for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
          if (grid[i][j] == wall) {
            continue;
          }
          for (auto [di, dj] : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            int pi = i + di;
            int pj = j + dj;
            if (inside(pi, pj, h, w) && naive[pi][pj] + 1 < naive[i][j]) {
              naive[i][j] = naive[pi][pj] + 1;
              changed = true;
            }
          }
        }
      }
    }
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        assert(dist[i][j] == (naive[i][j] == INF ? -1 : naive[i][j]));
      }
    }
  }
}

int main() {
  test_dxdy8();
  test_inside();
  test_grid_bfs();
  cout << "OK" << endl;
}
