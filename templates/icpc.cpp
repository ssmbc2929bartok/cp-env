// @snippet ICPC
// @desc ICPC国内予選用テンプレート (データセットを終わりまで繰り返す)
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

// データセットを1つ解く。入力の終わりなら false を返す
bool solve() {
  int n;
  cin >> n;
  if (n == 0) {
    return false;  // 終わりの条件は問題に合わせる
  }
  // @cursor
  return true;
}

int main() {
  while (solve()) {
  }
  return 0;
}
