#pragma once
// @snippet matrix
// @desc 行列用: 行列積・スカラー倍・行列累乗 (mod つき)
#include "base.hpp"

// 行列エイリアス
//   Matrix P(N, vector<ll>(N, 0));  // N×N の零行列
using Matrix = vector<vector<ll>>;

const ll MOD = 998244353;  // mod (問題に合わせて書き換える)

// 行列積の演算子オーバーロード (正方行列どうし)
Matrix operator*(const Matrix& A, const Matrix& B) {
  int n = A.size();
  Matrix C(n, vector<ll>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      for (int j = 0; j < n; j++) {
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
      }
    }
  }
  return C;
}

// 行列のスカラー倍
Matrix operator*(const Matrix& A, ll k) {
  Matrix C = A;
  for (auto& row : C) {
    for (auto& x : row) {
      x = x * k % MOD;
    }
  }
  return C;
}

// 行列累乗
Matrix matpow(Matrix A, ll n) {
  int sz = A.size();
  Matrix res(sz, vector<ll>(sz, 0));
  for (int i = 0; i < sz; i++) {
    res[i][i] = 1;  // 単位行列
  }
  while (n > 0) {
    if (n & 1) {
      res = res * A;
    }
    A = A * A;
    n >>= 1;
  }
  return res;
}
