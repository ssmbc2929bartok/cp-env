#pragma once
// @snippet annealing
// @desc 焼きなまし法の雛形 (スコアを最大化する)
#include "base.hpp"
#include "timer.hpp"
#include "xorshift.hpp"

// 焼きなまし法 (スコアを最大化する)。問題ごとに State を書き、次の4つを用意して使う
//   double score;                      今のスコア
//   auto random_move(XorShift& rng);   近傍 (小さな変更) を1つ選んで返す。型は自由
//   double diff(const auto& mv);       その変更をしたときに、スコアが増える量 (減るなら負)
//   void apply(const auto& mv);        その変更を実際に行う (score の更新は anneal がする)
//
//   state:      最初の状態
//   time_limit: 使う時間 [秒]
//   temp_start, temp_end: 最初と最後の温度。高いほど、スコアが下がる変更を受け入れやすい
// 戻り値: 見つかった中でスコアが最大の状態
template <class State>
State anneal(State state, double time_limit, double temp_start, double temp_end) {
  Timer timer;
  XorShift rng;
  State best = state;
  double temp = temp_start;
  for (ll iter = 0;; iter++) {
    if (iter % 128 == 0) {                      // 時刻を調べるのは遅いので、ときどきだけにする
      double t = timer.elapsed() / time_limit;  // 進み具合 (0 から 1)
      if (t >= 1.0) {
        break;
      }
      temp = temp_start * pow(temp_end / temp_start, t);  // 温度を少しずつ下げる
    }

    auto mv = state.random_move(rng);
    double d = state.diff(mv);
    // 良くなる変更は必ず、悪くなる変更は確率 exp(d / temp) で受け入れる
    if (d >= 0 || rng.next_double() < exp(d / temp)) {
      state.apply(mv);
      state.score += d;
      if (state.score > best.score) {
        best = state;
      }
    }
  }
  return best;
}
