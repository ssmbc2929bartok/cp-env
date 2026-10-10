// @snippet interactive
// @desc インタラクティブ問題用テンプレート (出力は endl で送り出す)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, a, b) for (ll i = a; i < b; ++i)
#define rrep(i, a, b) for (ll i = a; i >= b; --i)

// --- 初期設定（小数15桁出力） ---
// インタラクティブ問題では、出力をすぐ相手に届ける必要がある。
// cin.tie(nullptr) は書かず、出力の最後は必ず endl にする ("\n" では届かないことがある)
struct Init {
  Init() {
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
  }
} init;
// ------------------------------------------------

int main() {
  // @cursor
  return 0;
}
