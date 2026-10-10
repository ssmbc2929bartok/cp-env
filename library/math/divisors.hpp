#pragma once
// @snippet divisors
// @desc 約数列挙: O(√n)
#include "base.hpp"

// 約数列挙: n の約数を昇順に並べて返す。O(√n)
//   例) divisors(12) → {1, 2, 3, 4, 6, 12}
vector<ll> divisors(ll n) {
  vector<ll> small, large;
  for (ll d = 1; d * d <= n; d++) {
    if (n % d != 0) {
      continue;
    }
    small.push_back(d);
    if (d != n / d) {
      large.push_back(n / d);  // d と対になる約数
    }
  }
  small.insert(small.end(), large.rbegin(), large.rend());
  return small;
}
