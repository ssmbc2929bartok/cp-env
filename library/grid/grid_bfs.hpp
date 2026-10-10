#pragma once
// @snippet grid_bfs
// @desc グリッドのBFS (始点は複数可): 各マスへの最短の移動回数
#include "base.hpp"

// グリッド上の幅優先探索 (上下左右に動く。始点は複数でもよい)。
// 各マスについて、いちばん近い始点からの最短の移動回数を返す。届かないマスは -1
//   grid:   各行の文字列。wall の文字のマスには入れない
//   starts: 始点の (行, 列) の一覧
vector<vector<int>> grid_bfs(const vector<string>& grid, const vector<pair<int, int>>& starts,
                             char wall = '#') {
  int h = grid.size();
  int w = grid[0].size();
  const int di[4] = {-1, 1, 0, 0};
  const int dj[4] = {0, 0, -1, 1};

  vector<vector<int>> dist(h, vector<int>(w, -1));
  queue<pair<int, int>> q;
  for (auto [i, j] : starts) {
    if (dist[i][j] == -1) {
      dist[i][j] = 0;
      q.emplace(i, j);
    }
  }

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();
    for (int d = 0; d < 4; d++) {
      int ni = i + di[d];
      int nj = j + dj[d];
      if (ni < 0 || ni >= h || nj < 0 || nj >= w) {
        continue;
      }
      if (grid[ni][nj] == wall || dist[ni][nj] != -1) {
        continue;
      }
      dist[ni][nj] = dist[i][j] + 1;
      q.emplace(ni, nj);
    }
  }
  return dist;
}
