// @snippet generator
// @desc 作問用: 入力を作る generator (testlib)。引数が乱数の種になる
#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);  // 引数ごとに違う乱数列になる (cpe stress は通し番号を渡す)
  // @cursor
  // 例: 1 以上 10 以下の N を1つ出力する
  int n = rnd.next(1, 10);
  cout << n << endl;
  return 0;
}
