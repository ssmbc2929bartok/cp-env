#include <bits/stdc++.h>
#include "ahc/annealing.hpp"
#include "ahc/timer.hpp"
#include "ahc/xorshift.hpp"
#include "testutil.hpp"

void test_xorshift() {
  XorShift rng;
  // 同じ値がすぐには繰り返されない
  set<uint64_t> seen;
  for (int i = 0; i < 10000; i++) {
    seen.insert(rng.next());
  }
  assert(seen.size() == 10000);

  // next_int(n): 0 以上 n 未満で、すべての値が出る
  for (int n : {1, 2, 3, 10, 1000}) {
    vector<int> cnt(n, 0);
    for (int i = 0; i < 50 * n + 100; i++) {
      int x = rng.next_int(n);
      assert(0 <= x && x < n);
      cnt[x]++;
    }
    assert(*min_element(cnt.begin(), cnt.end()) > 0);
  }

  // next_int(l, r): l 以上 r 未満で、両端の値が出る
  set<int> vals;
  for (int i = 0; i < 2000; i++) {
    int x = rng.next_int(-3, 4);
    assert(-3 <= x && x < 4);
    vals.insert(x);
  }
  assert(vals.size() == 7);

  // next_double(): 0 以上 1 未満で、平均がほぼ 0.5、10等分したどの区間にも偏りなく入る
  double sum = 0;
  vector<int> bucket(10, 0);
  int trials = 200000;
  for (int i = 0; i < trials; i++) {
    double x = rng.next_double();
    assert(0.0 <= x && x < 1.0);
    sum += x;
    bucket[(int)(x * 10)]++;
  }
  assert(abs(sum / trials - 0.5) < 0.01);
  for (int c : bucket) {
    assert(abs(c - trials / 10) < trials / 100);
  }

  // 作り直すと同じ列になる (再現できる)
  XorShift a, b;
  for (int i = 0; i < 100; i++) {
    assert(a.next() == b.next());
  }
}

void test_timer() {
  Timer timer;
  double prev = timer.elapsed();
  assert(0.0 <= prev && prev < 1.0);
  for (int i = 0; i < 1000; i++) {
    double now = timer.elapsed();
    assert(now >= prev);  // 戻らない
    prev = now;
  }
  this_thread::sleep_for(chrono::milliseconds(50));
  double after = timer.elapsed();
  assert(0.045 <= after && after < 5.0);
}

// 焼きなましの確認用の問題: 0/1 の列を、隠した正解の列に近づける。スコア = 一致している個数
struct BitState {
  vector<int> x, target;
  double score = 0;

  int random_move(XorShift& rng) {
    return rng.next_int(x.size());  // 反転する位置
  }
  double diff(int i) const {
    return x[i] == target[i] ? -1 : 1;
  }
  void apply(int i) {
    x[i] ^= 1;
  }
};

// 近傍が (位置, 値) の組になる例: 数列の各要素を 0〜9 の正解の値に近づける。スコア = -Σ|差|
struct ArrayState {
  vector<int> x, target;
  double score = 0;

  pair<int, int> random_move(XorShift& rng) {
    return {rng.next_int(x.size()), rng.next_int(0, 10)};
  }
  double diff(const pair<int, int>& mv) const {
    auto [i, v] = mv;
    return abs(x[i] - target[i]) - abs(v - target[i]);
  }
  void apply(const pair<int, int>& mv) {
    x[mv.first] = mv.second;
  }
};

void test_annealing() {
  int n = 40;
  BitState s;
  s.x.assign(n, 0);
  s.target.resize(n);
  for (auto& t : s.target) {
    t = rnd(0, 1);
  }
  for (int i = 0; i < n; i++) {
    s.score += s.x[i] == s.target[i];
  }
  Timer timer;
  BitState best = anneal(s, 0.2, 2.0, 0.01);
  double used = timer.elapsed();
  assert(0.2 <= used && used < 2.0);  // 指定した時間だけ動いて止まる
  assert(best.x == best.target);      // 最適解に届く
  assert(best.score == n);            // score が実際の値とずれていない

  ArrayState a;
  a.x.assign(n, 0);
  a.target.resize(n);
  for (auto& t : a.target) {
    t = rnd(0, 9);
  }
  for (int i = 0; i < n; i++) {
    a.score -= abs(a.x[i] - a.target[i]);
  }
  ArrayState best2 = anneal(a, 0.2, 3.0, 0.01);
  assert(best2.x == best2.target);
  assert(best2.score == 0);
}

int main() {
  test_xorshift();
  test_timer();
  test_annealing();
  cout << "OK" << endl;
}
