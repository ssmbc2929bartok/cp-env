#include <bits/stdc++.h>
#include "cumsum/cumsum.hpp"
#include "cumsum/cumsum2d.hpp"
#include "cumsum/imos.hpp"
#include "cumsum/imos2d.hpp"
#include "testutil.hpp"

void test_cumsum() {
  for (int t = 0; t < 1000; t++) {
    int n = rnd(0, 15);
    vector<int> a(n);  // int の列でも、和は long long で持つ
    for (auto& x : a) {
      x = rnd(-2000000000, 2000000000);
    }
    CumSum cs(a);
    for (int l = 0; l <= n; l++) {
      ll s = 0;
      for (int r = l; r <= n; r++) {
        assert(cs.sum(l, r) == s);
        if (r < n) {
          s += a[r];
        }
      }
    }
  }
}

void test_cumsum2d() {
  // 空のグリッドでも作れる
  assert(CumSum2D(vector<vector<int>>()).sum(0, 0, 0, 0) == 0);

  for (int t = 0; t < 300; t++) {
    int h = rnd(1, 6);
    int w = rnd(1, 6);
    vector<vector<ll>> a(h, vector<ll>(w));
    for (auto& row : a) {
      for (auto& x : row) {
        x = rnd(-1000000000000LL, 1000000000000LL);
      }
    }
    CumSum2D cs(a);
    for (int i1 = 0; i1 <= h; i1++) {
      for (int i2 = i1; i2 <= h; i2++) {
        for (int j1 = 0; j1 <= w; j1++) {
          for (int j2 = j1; j2 <= w; j2++) {
            ll s = 0;
            for (int i = i1; i < i2; i++) {
              for (int j = j1; j < j2; j++) {
                s += a[i][j];
              }
            }
            assert(cs.sum(i1, j1, i2, j2) == s);
          }
        }
      }
    }
  }
}

void test_imos() {
  for (int t = 0; t < 1000; t++) {
    int n = rnd(0, 15);
    Imos im(n);
    vector<ll> naive(n, 0);
    int q = rnd(0, 10);
    for (int i = 0; i < q; i++) {
      int l = rnd(0, n);
      int r = rnd(l, n);
      if (rnd(0, 1) == 0) {
        im.add(l, r);  // x を省略すると 1
        for (int k = l; k < r; k++) {
          naive[k] += 1;
        }
      } else {
        ll x = rnd(-1000000000000LL, 1000000000000LL);
        im.add(l, r, x);
        for (int k = l; k < r; k++) {
          naive[k] += x;
        }
      }
    }
    assert(im.build() == naive);
  }
}

void test_imos2d() {
  for (int t = 0; t < 500; t++) {
    int h = rnd(0, 6);
    int w = rnd(0, 6);
    Imos2D im(h, w);
    vector<vector<ll>> naive(h, vector<ll>(w, 0));
    int q = rnd(0, 8);
    for (int i = 0; i < q; i++) {
      int i1 = rnd(0, h);
      int i2 = rnd(i1, h);
      int j1 = rnd(0, w);
      int j2 = rnd(j1, w);
      ll x = rnd(0, 3) == 0 ? 1 : rnd(-1000000000000LL, 1000000000000LL);
      if (x == 1) {
        im.add(i1, j1, i2, j2);
      } else {
        im.add(i1, j1, i2, j2, x);
      }
      for (int a = i1; a < i2; a++) {
        for (int b = j1; b < j2; b++) {
          naive[a][b] += x;
        }
      }
    }
    assert(im.build() == naive);
  }
}

int main() {
  test_cumsum();
  test_cumsum2d();
  test_imos();
  test_imos2d();
  cout << "OK" << endl;
}
