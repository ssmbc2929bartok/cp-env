#include <bits/stdc++.h>
#include <atcoder/modint>
#include "testutil.hpp"
#include "util/chminmax.hpp"
#include "util/compress.hpp"
#include "util/debug.hpp"
#include "util/dxdy4.hpp"
#include "util/ordered_set.hpp"
#include "util/print128.hpp"
#include "util/rle.hpp"

void test_dxdy4() {
  // 4方向がすべて違い、どれも距離 1
  set<pair<int, int>> dirs;
  for (int d = 0; d < 4; d++) {
    assert(abs(dx[d]) + abs(dy[d]) == 1);
    dirs.emplace(dx[d], dy[d]);
  }
  assert(dirs.size() == 4);
}

void test_print128() {
  assert(str128(0) == "0");
  assert(str128(7) == "7");
  assert(str128(-7) == "-7");
  // long long に収まる範囲では to_string と一致する
  for (int t = 0; t < 2000; t++) {
    ll x = (ll)test_rng();
    assert(str128(x) == to_string(x));
  }
  assert(str128(LLONG_MIN) == to_string(LLONG_MIN));
  // long long を超える値: 10^30 と、その符号違い
  lll big = 1;
  for (int i = 0; i < 30; i++) {
    big *= 10;
  }
  assert(str128(big) == "1" + string(30, '0'));
  assert(str128(-big) == "-1" + string(30, '0'));
  assert(str128(big - 1) == string(30, '9'));
  // __int128 の最小値 (符号を反転できない値) でも正しい
  lll mn = (lll)1 << 126;
  mn = -mn - mn;
  assert(str128(mn) == "-170141183460469231731687303715884105728");
  assert(str128(-(mn + 1)) == "170141183460469231731687303715884105727");

  // print128 は cout に同じ文字列を出す
  ostringstream oss;
  streambuf* old = cout.rdbuf(oss.rdbuf());
  print128(-big);
  cout.rdbuf(old);
  assert(oss.str() == str128(-big));
}

void test_chminmax() {
  for (int t = 0; t < 1000; t++) {
    ll a = rnd(-50, 50);
    int b = rnd(-50, 50);  // 型が違っても使える
    ll x = a;
    assert(chmin(x, b) == (b < a));
    assert(x == min<ll>(a, b));
    x = a;
    assert(chmax(x, b) == (b > a));
    assert(x == max<ll>(a, b));
  }
  double d = 1.5;
  assert(chmin(d, 1) && d == 1.0);
}

void test_compress() {
  for (int t = 0; t < 500; t++) {
    int n = rnd(0, 20);
    vector<ll> a(n);
    for (auto& x : a) {
      x = rnd(-10, 10) * 1000000007LL;
    }
    Compress c(a);
    set<ll> st(a.begin(), a.end());
    assert(c.size() == (int)st.size());
    for (int i = 0; i < n; i++) {
      // 愚直: a[i] より小さい値の種類数
      int rank = distance(st.begin(), st.find(a[i]));
      assert(c.get(a[i]) == rank);
      assert(c[c.get(a[i])] == a[i]);
    }
    for (int i = 0; i + 1 < c.size(); i++) {
      assert(c[i] < c[i + 1]);
    }
  }
}

void test_rle() {
  string s = "aaabcc";
  auto r = rle(s);
  assert((r == vector<pair<char, int>>{{'a', 3}, {'b', 1}, {'c', 2}}));
  assert(rle(string()).empty());
  for (int t = 0; t < 500; t++) {
    int n = rnd(0, 30);
    vector<int> a(n);
    for (auto& x : a) {
      x = rnd(0, 2);
    }
    auto runs = rle(a);
    // 復元すると元に戻り、隣り合う組の値は違い、個数は 1 以上
    vector<int> back;
    for (int i = 0; i < (int)runs.size(); i++) {
      assert(runs[i].second >= 1);
      if (i > 0) {
        assert(runs[i - 1].first != runs[i].first);
      }
      back.insert(back.end(), runs[i].second, runs[i].first);
    }
    assert(back == a);
  }
}

void test_debug() {
  // 標準エラーを一時的に差し替えて、出力の形を確かめる
  ostringstream oss;
  streambuf* old = cerr.rdbuf(oss.rdbuf());
  int x = 5;
  vector<int> v = {1, 2, 3};
  string s = "ab";
  map<int, pair<char, bool>> mp = {{1, {'z', true}}};
  tuple<int, double, string> tp = {1, 2.5, "t"};
  vector<vector<bool>> vb = {{true, false}, {}};
  atcoder::modint998244353 m = -1;
  // clang-format off
  debug(x, v, s); int line = __LINE__;
  // clang-format on
  debug(mp);
  debug(tp, vb, m);
  debug("lit", 'c', 3.5);
  debug();
  cerr.rdbuf(old);

  string expected = "[L" + to_string(line) + "] x, v, s = 5, [1, 2, 3], \"ab\"\n";
  expected += "[L" + to_string(line + 2) + "] mp = [(1, (z, true))]\n";
  expected += "[L" + to_string(line + 3) + "] tp, vb, m = (1, 2.5, \"t\"), [[true, false], []], 998244352\n";
  expected += "[L" + to_string(line + 4) + "] \"lit\", 'c', 3.5 = \"lit\", c, 3.5\n";
  expected += "[L" + to_string(line + 5) + "]  = \n";
  if (oss.str() != expected) {
    cerr << "--- 期待 ---\n"
         << expected << "--- 実際 ---\n"
         << oss.str();
    assert(false);
  }
}

void test_ordered_set() {
  for (int t = 0; t < 50; t++) {
    ordered_set<int> os;
    set<int> naive;
    for (int q = 0; q < 60; q++) {
      int x = rnd(0, 30);
      if (rnd(0, 2) == 0) {
        os.erase(x);
        naive.erase(x);
      } else {
        os.insert(x);
        naive.insert(x);
      }
      assert(os.size() == naive.size());
      vector<int> sorted(naive.begin(), naive.end());
      for (int k = 0; k < (int)sorted.size(); k++) {
        assert(*os.find_by_order(k) == sorted[k]);
      }
      int y = rnd(-1, 31);
      int less_cnt = lower_bound(sorted.begin(), sorted.end(), y) - sorted.begin();
      assert((int)os.order_of_key(y) == less_cnt);
    }
  }
}

int main() {
  test_dxdy4();
  test_print128();
  test_chminmax();
  test_compress();
  test_rle();
  test_debug();
  test_ordered_set();
  cout << "OK" << endl;
}
