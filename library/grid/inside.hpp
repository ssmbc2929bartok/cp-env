#pragma once
// @snippet inside
// @desc グリッドの範囲内判定

// (i, j) が h 行 w 列のグリッドの中にあるか
bool inside(int i, int j, int h, int w) {
  return 0 <= i && i < h && 0 <= j && j < w;
}
