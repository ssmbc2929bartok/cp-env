#pragma once
// @snippet debug
// @desc デバッグ出力 debug(x, v): 手元でだけ、変数名と中身を標準エラーに出す
#include "base.hpp"

// デバッグ出力: debug(x, v, mp); と書くと、行番号・変数名・中身を標準エラーに出す。
// 手元 (-DLOCAL) でだけ動き、提出先では何もしない。
// vector・set・map・pair・tuple と、その入れ子、ACL の modint に対応
#ifdef LOCAL
template <class T>
void debug_print(const T& x) {
  if constexpr (is_convertible_v<T, string_view>) {
    cerr << '"' << x << '"';
  } else if constexpr (is_same_v<T, bool>) {
    cerr << (x ? "true" : "false");
  } else if constexpr (requires { cerr << x; }) {
    cerr << x;
  } else if constexpr (requires { x.val(); }) {
    cerr << x.val();
  } else if constexpr (requires { begin(x); }) {
    cerr << "[";
    bool first = true;
    for (const auto& e : x) {
      cerr << (first ? "" : ", ");
      first = false;
      debug_print(e);
    }
    cerr << "]";
  } else if constexpr (requires { tuple_size<T>::value; }) {
    cerr << "(";
    bool first = true;
    apply(
        [&](const auto&... es) {
          ((cerr << (first ? "" : ", "), first = false, debug_print(es)), ...);
        },
        x);
    cerr << ")";
  } else {
    cerr << "?";
  }
}

template <class... Ts>
void debug_all(int line, const char* names, const Ts&... xs) {
  cerr << "[L" << line << "] " << names << " = ";
  [[maybe_unused]] bool first = true;
  ((cerr << (first ? "" : ", "), first = false, debug_print(xs)), ...);
  cerr << endl;
}
#define debug(...) debug_all(__LINE__, #__VA_ARGS__ __VA_OPT__(, ) __VA_ARGS__)
#else
#define debug(...) (void)0
#endif
