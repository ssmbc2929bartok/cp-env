// @snippet Codeforces
// @desc Codeforces用テンプレート (複数テストケース)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, a, b) for (ll i = a; i < b; ++i)
#define rrep(i, a, b) for (ll i = a; i >= b; --i)

// --- 初期設定（入出力の高速化と小数15桁出力） ---
struct Init {
  Init() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
  }
} init;
// ------------------------------------------------

// テストケースを1つ解く
void solve() {
  // @cursor
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
