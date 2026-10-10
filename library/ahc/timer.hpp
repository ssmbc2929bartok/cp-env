#pragma once
// @snippet timer
// @desc 経過時間の計測 (AHC の時間管理用)
#include "base.hpp"

// 経過時間の計測: 作った時点からの秒数を返す
//   Timer timer;                    プログラムの最初で作る
//   if (timer.elapsed() > 1.9) ...  1.9 秒を過ぎたら打ち切る、など
struct Timer {
  chrono::steady_clock::time_point start = chrono::steady_clock::now();

  double elapsed() const {
    return chrono::duration<double>(chrono::steady_clock::now() - start).count();
  }
};
