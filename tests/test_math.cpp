#include <bits/stdc++.h>
#include <atcoder/modint>
#include "math/binomial.hpp"
#include "math/divisors.hpp"
#include "math/factorize.hpp"
#include "math/matrix.hpp"
#include "math/sieve.hpp"
#include "testutil.hpp"

// 愚直な素数判定 (試し割り)
bool is_prime_naive(ll x) {
  if (x < 2) {
    return false;
  }
  for (ll d = 2; d * d <= x; d++) {
    if (x % d == 0) {
      return false;
    }
  }
  return true;
}

void test_matrix() {
  for (int t = 0; t < 300; t++) {
    int n = rnd(1, 5);
    auto random_matrix = [&]() {
      Matrix m(n, vector<ll>(n));
      for (auto& row : m) {
        for (auto& x : row) {
          x = rnd(0, MOD - 1);
        }
      }
      return m;
    };
    Matrix a = random_matrix();
    Matrix b = random_matrix();

    // 行列積: 定義どおりの計算 (__int128 で余りを取る) と一致する
    Matrix c = a * b;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        __int128_t s = 0;
        for (int k = 0; k < n; k++) {
          s += (__int128_t)a[i][k] * b[k][j];
        }
        assert(c[i][j] == (ll)(s % MOD));
      }
    }

    // スカラー倍
    ll k = rnd(0, MOD - 1);
    Matrix d = a * k;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        assert(d[i][j] == (ll)((__int128_t)a[i][j] * k % MOD));
      }
    }

    // 累乗: 1回ずつ掛けた結果と一致する。0 乗は単位行列
    Matrix p(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
      p[i][i] = 1;
    }
    for (int e = 0; e <= 12; e++) {
      assert(matpow(a, e) == p);
      p = p * a;
    }
  }

  // フィボナッチ数列: {{1,1},{1,0}} の n 乗の右上が F(n)
  Matrix f = {{1, 1}, {1, 0}};
  assert(matpow(f, 10)[0][1] == 55);
  assert(matpow(f, 90)[0][1] == 2880067194370816120LL % MOD);
  // 大きな指数でも動く (2 の 10^18 乗を、繰り返し二乗法と突き合わせる)
  ll e = 1000000000000000000LL;
  ll expected = 1;
  ll base = 2;
  for (ll r = e; r > 0; r >>= 1) {
    if (r & 1) {
      expected = expected * base % MOD;
    }
    base = base * base % MOD;
  }
  assert(matpow(Matrix{{2}}, e)[0][0] == expected);
}

void test_sieve() {
  int n = 3000;
  Sieve sv(n);
  vector<int> primes;
  for (int x = 0; x <= n; x++) {
    assert(sv.is_prime(x) == is_prime_naive(x));
    if (is_prime_naive(x)) {
      primes.push_back(x);
    }
    if (x >= 1) {
      // 素因数分解: 掛け合わせると x に戻り、素因数は昇順の素数
      ll prod = 1;
      int prev = 0;
      for (auto [p, e] : sv.factorize(x)) {
        assert(is_prime_naive(p) && p > prev && e >= 1);
        prev = p;
        for (int i = 0; i < e; i++) {
          prod *= p;
        }
      }
      assert(prod == x);
    }
  }
  assert(sv.primes == primes);
  assert(sv.is_prime(-5) == false);

  // 小さい n でも範囲外に触らない
  for (int m = 0; m <= 30; m++) {
    Sieve small(m);
    for (int x = 0; x <= m; x++) {
      assert(small.is_prime(x) == is_prime_naive(x));
    }
  }
}

void test_factorize() {
  auto check = [&](ll n) {
    ll prod = 1;
    ll prev = 0;
    for (auto [p, e] : factorize(n)) {
      assert(is_prime_naive(p) && p > prev && e >= 1);
      prev = p;
      for (int i = 0; i < e; i++) {
        prod *= p;
      }
    }
    assert(prod == n);
  };
  assert(factorize(1).empty());
  assert((factorize(360) == vector<pair<ll, int>>{{2, 3}, {3, 2}, {5, 1}}));
  for (ll n = 1; n <= 3000; n++) {
    check(n);
  }
  for (int t = 0; t < 100; t++) {
    check(rnd(1, 1000000000000LL));
  }
  check(999983LL * 1000003LL);  // 大きな素数2つの積
  check(999999999989LL);        // 10^12 に近い素数
  check(1LL << 62);
}

void test_divisors() {
  assert((divisors(12) == vector<ll>{1, 2, 3, 4, 6, 12}));
  assert((divisors(1) == vector<ll>{1}));
  for (ll n = 1; n <= 2000; n++) {
    vector<ll> naive;
    for (ll d = 1; d <= n; d++) {
      if (n % d == 0) {
        naive.push_back(d);
      }
    }
    assert(divisors(n) == naive);
  }
  // 大きな値: 昇順で、どれも割り切り、個数は素因数分解から求めた値と一致する
  for (int t = 0; t < 50; t++) {
    ll n = rnd(1, 1000000000000LL);
    vector<ll> ds = divisors(n);
    ll cnt = 1;
    for (auto [p, e] : factorize(n)) {
      cnt *= e + 1;
    }
    assert((ll)ds.size() == cnt);
    for (int i = 0; i < (int)ds.size(); i++) {
      assert(n % ds[i] == 0);
      if (i > 0) {
        assert(ds[i - 1] < ds[i]);
      }
    }
  }
}

template <class mint>
void test_binomial_with() {
  int n = 60;
  // 愚直: パスカルの三角形
  vector<vector<mint>> pascal(n + 1, vector<mint>(n + 1, 0));
  for (int i = 0; i <= n; i++) {
    pascal[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      pascal[i][j] = pascal[i - 1][j - 1] + (j <= i - 1 ? pascal[i - 1][j] : 0);
    }
  }
  Binomial<mint> bc(2 * n);
  mint fact = 1;
  for (int i = 0; i <= n; i++) {
    if (i > 0) {
      fact *= i;
    }
    assert(bc.fact[i] == fact);
    assert(bc.fact[i] * bc.inv_fact[i] == 1);
    for (int r = -2; r <= n + 2; r++) {
      mint c = (0 <= r && r <= i) ? pascal[i][r] : 0;
      assert(bc.C(i, r) == c);
      // nPr = nCr × r!
      mint p = c;
      for (int k = 1; k <= r; k++) {
        p *= k;
      }
      assert(bc.P(i, r) == p);
    }
  }
  // nHr: n 種類から重複を許して r 個選ぶ = C(n + r - 1, r)。n = 0 は r = 0 のときだけ 1 通り
  assert(bc.H(0, 0) == 1 && bc.H(0, 3) == 0);
  for (int k = 1; k <= 20; k++) {
    for (int r = 0; r <= 20; r++) {
      assert(bc.H(k, r) == pascal[k + r - 1][r]);
    }
  }
  assert(bc.H(3, 2) == 6);
}

void test_binomial() {
  test_binomial_with<atcoder::modint998244353>();
  test_binomial_with<atcoder::modint1000000007>();
}

int main() {
  test_matrix();
  test_sieve();
  test_factorize();
  test_divisors();
  test_binomial();
  cout << "OK" << endl;
}
