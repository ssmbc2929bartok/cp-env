#pragma once
// @snippet print128
// @desc __int128 を出力する (負の数にも対応)
#include "base.hpp"

using lll = __int128_t;

// __int128 を10進数の文字列にする
string str128(lll x) {
  if (x == 0) {
    return "0";
  }
  bool neg = x < 0;
  string s;
  while (x != 0) {
    int d = (int)(x % 10);  // x が負のときは 0 以下になる
    s += char('0' + (neg ? -d : d));
    x /= 10;
  }
  if (neg) {
    s += '-';
  }
  reverse(s.begin(), s.end());
  return s;
}

// __int128 を出力する (cout は __int128 をそのままでは出力できない)
void print128(lll x) {
  cout << str128(x);
}
