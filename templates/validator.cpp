// @snippet validator
// @desc 作問用: 入力が制約どおりかを確かめる validator (testlib)
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  // @cursor
  // 例: 1行目に N (1 以上 200000 以下) だけがある入力
  inf.readInt(1, 200000, "N");
  inf.readEoln();
  inf.readEof();
  return 0;
}
