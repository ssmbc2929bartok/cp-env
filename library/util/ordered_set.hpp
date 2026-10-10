#pragma once
// @snippet ordered_set
// @desc 順序つき集合 (pb_ds): k 番目の要素、x より小さい要素の個数
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "base.hpp"

// 順序つき集合: set の機能に加えて、次の2つを O(log N) で求められる
//   *s.find_by_order(k)   k 番目 (0始まり) に小さい要素
//   s.order_of_key(x)     x より小さい要素の個数
// insert・erase・size・lower_bound などは set と同じ。
// 同じ値を複数入れたいときは、pair<値, 通し番号> を入れる
template <class T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;
