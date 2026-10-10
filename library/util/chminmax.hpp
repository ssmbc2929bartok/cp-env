#pragma once
// @snippet chminmax
// @desc chmin / chmax: 小さい方・大きい方に更新する
#include "base.hpp"

// a を「a と b の小さい方」に更新する。更新したら true を返す
template <class T, class U>
bool chmin(T& a, const U& b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

// a を「a と b の大きい方」に更新する。更新したら true を返す
template <class T, class U>
bool chmax(T& a, const U& b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
