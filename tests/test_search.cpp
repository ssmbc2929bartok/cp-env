#include <bits/stdc++.h>
#include "search/bisect.hpp"
#include "search/bit_search.hpp"
#include "search/two_pointers.hpp"
#include "testutil.hpp"

void test_bisect() {
  for (int t = 0; t < 2000; t++) {
    ll lo = rnd(-50, 50);
    ll hi = lo + rnd(1, 60);
    ll border = rnd(lo, hi - 1);  // lo 〜 border が「満たす」側

    // ok が小さい側: x <= border を満たす最大の x
    assert(bisect(lo, hi, [&](ll x) { return x <= border; }) == border);
    // ok が大きい側: x > border を満たす最小の x
    assert(bisect(hi, lo, [&](ll x) { return x > border; }) == border + 1);
  }

  // 昇順の列で「a[i] >= x となる最小の i」。lower_bound と一致する
  for (int t = 0; t < 1000; t++) {
    int n = rnd(0, 15);
    vector<ll> a(n);
    for (auto& v : a) {
      v = rnd(0, 20);
    }
    sort(a.begin(), a.end());
    ll x = rnd(-1, 21);
    ll got = bisect(n, -1, [&](ll i) { return a[i] >= x; });
    assert(got == lower_bound(a.begin(), a.end(), x) - a.begin());
  }

  // 大きな値でも途中で桁あふれしない
  ll big = 4000000000000000000LL;
  assert(bisect(0, big, [&](ll x) { return x <= big - 5; }) == big - 5);
  assert(bisect(-big, big, [&](ll x) { return x <= 123; }) == 123);
}

void test_bisect_real() {
  for (int t = 0; t < 200; t++) {
    double target = rnd(1, 1000000) / 100.0;
    // x * x <= target を満たす最大の x は √target
    double got = bisect_real(0.0, 2000.0, [&](double x) { return x * x <= target; });
    assert(abs(got - sqrt(target)) < 1e-9);
    // ok が大きい側でも使える
    got = bisect_real(2000.0, 0.0, [&](double x) { return x * x >= target; });
    assert(abs(got - sqrt(target)) < 1e-9);
  }
}

void test_bit_search() {
  for (int n = 0; n <= 10; n++) {
    set<vector<int>> seen;
    bit_search(n, [&](const vector<int>& chosen) {
      // 番号は昇順で、範囲内で、重複がない
      for (int i = 0; i < (int)chosen.size(); i++) {
        assert(0 <= chosen[i] && chosen[i] < n);
        if (i > 0) {
          assert(chosen[i - 1] < chosen[i]);
        }
      }
      seen.insert(chosen);
    });
    assert((int)seen.size() == (1 << n));  // 2^n 通りがすべて違う
  }

  // 部分和の個数を、再帰での数え上げと突き合わせる
  for (int t = 0; t < 200; t++) {
    int n = rnd(0, 8);
    vector<int> a(n);
    for (auto& v : a) {
      v = rnd(1, 6);
    }
    int target = rnd(0, 15);
    int cnt = 0;
    bit_search(n, [&](const vector<int>& chosen) {
      int sum = 0;
      for (int i : chosen) {
        sum += a[i];
      }
      cnt += sum == target;
    });
    auto rec = [&](auto self, int i, int rest) -> int {
      if (i == n) {
        return rest == 0;
      }
      return self(self, i + 1, rest) + self(self, i + 1, rest - a[i]);
    };
    assert(cnt == rec(rec, 0, target));
  }
}

void test_two_pointers() {
  for (int t = 0; t < 2000; t++) {
    int n = rnd(0, 12);
    vector<ll> a(n);
    for (auto& v : a) {
      v = rnd(0, 8);
    }
    ll k = rnd(0, 20);

    // 和が k 以下の区間
    ll sum = 0;
    vector<int> res = two_pointers(
        n, [&](int i) { return sum + a[i] <= k; }, [&](int i) { sum += a[i]; },
        [&](int i) { sum -= a[i]; });
    assert((int)res.size() == n);
    for (int l = 0; l < n; l++) {
      // 愚直: l から1つずつ伸ばす
      int r = l;
      ll s = 0;
      while (r < n && s + a[r] <= k) {
        s += a[r];
        r++;
      }
      assert(res[l] == r);
    }
    assert(sum == 0 || n > 0);

    // 同じ値を含まない区間 (種類数を数える形)
    vector<int> cnt(9, 0);
    res = two_pointers(
        n, [&](int i) { return cnt[a[i]] == 0; }, [&](int i) { cnt[a[i]]++; },
        [&](int i) { cnt[a[i]]--; });
    for (int l = 0; l < n; l++) {
      int r = l;
      set<ll> st;
      while (r < n && !st.count(a[r])) {
        st.insert(a[r]);
        r++;
      }
      assert(res[l] == r);
    }
  }
}

int main() {
  test_bisect();
  test_bisect_real();
  test_bit_search();
  test_two_pointers();
  cout << "OK" << endl;
}
