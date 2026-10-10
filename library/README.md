# ライブラリの使い方

競技プログラミング用の自作ライブラリです。1ファイルに1機能で、`library/<分野>/<名前>.hpp` に置いています。
UnionFind・セグメント木・遅延セグメント木・SCC・フロー・modint は AtCoder Library(ACL)を使うので、ここにはありません。

## 使い方は2通り

### 1. スニペットで貼る(ふだんはこちら)

`.cpp` を開いて名前(下の表の「名前」)を打ち、候補から選ぶと、中身がその場に貼り付けられます。貼ったコードはそのまま提出できます。

- 候補の説明に `[先に貼る: graph]` と出るものは、その名前のスニペットを先に(上に)貼ってください。
- 貼る場所は、`using ll = long long;` より下、`main` より上です。
- スニペットは `cpe vscode` で各作業フォルダに配ります。ライブラリを直したあとは、もう一度 `cpe vscode` を実行してください。
- 配ったのに候補に出ないときは、VS Code のウィンドウを再読み込みします(F1 →「ウィンドウの再読み込み」)。VS Code は、あとから増えたスニペットのファイルに気づかないことがあります。

### 2. `#include` で読み込む

```cpp
#include <bits/stdc++.h>
#include "graph/dijkstra.hpp"
using namespace std;
```

- `cpe test` や `cpe run` は、このまま動きます。
- 提出先には自作ライブラリが無いので、提出の前に `cpe bundle` で1ファイルに展開し、`submit/` にできたファイルを提出します(AtCoder でも必要です)。
- `#include <bits/stdc++.h>` は、必ず最初の `#include` にしてください(コンパイルを速くする仕組みが、最初の1つにしか効かないため)。

## 共通の決まり

- 頂点番号・添字は **0 始まり**です。1 始まりの入力は、読み込むときに 1 を引きます(`read_graph` は既定で 1 を引きます)。
- 区間は **半開区間 `[l, r)`** です(`l` を含み、`r` を含まない)。
- 最短距離で「届かない」ときは **-1** を返します。
- `ll` は `long long` です。テンプレートの先頭(`#include <bits/stdc++.h>`、`using namespace std;`、`using ll = long long;`)がある前提で書いています。

## 一覧

### 小物(`util/`)

| 名前 | 内容 | 使い方 |
|---|---|---|
| `dxdy4` | 4方向(上下左右)の移動量 | `for (int d = 0; d < 4; d++) { int ni = i + dx[d], nj = j + dy[d]; }` |
| `dxdy8` | 8方向の移動量 | `dxdy4` と同じ形で、`d < 8` |
| `chminmax` | 小さい方・大きい方に更新する。更新したら `true` | `chmin(ans, x);` `if (chmax(best, x)) { ... }` |
| `compress` | 座標圧縮 | `Compress c(a);` `c.get(x)`(x が小さい方から何番目か) `c[i]`(元の値) `c.size()` |
| `rle` | ランレングス圧縮 | `for (auto [ch, cnt] : rle(s)) { ... }` |
| `print128` | `__int128` の出力 | `lll x = ...;` `print128(x);` 文字列が欲しいときは `str128(x)` |
| `debug` | デバッグ出力(手元でだけ動く) | `debug(x, v, mp);` → `[L12] x, v, mp = 5, [1, 2], [(1, 2)]` |
| `ordered_set` | k 番目の要素を取れる set | `ordered_set<int> s;` `*s.find_by_order(k)` `s.order_of_key(x)` |

### グリッド(`grid/`)

| 名前 | 内容 | 使い方 |
|---|---|---|
| `inside` | マスがグリッドの中にあるか | `if (!inside(ni, nj, h, w)) { continue; }` |
| `grid_bfs` | グリッドの最短移動回数(始点は複数可) | `auto dist = grid_bfs(grid, {{si, sj}});` 壁の文字を変えるときは第3引数 |

### グラフ(`graph/`)

`graph` 以外は、先に `graph` が必要です。

| 名前 | 内容 | 使い方 |
|---|---|---|
| `graph` | グラフ型と辺の読み込み | `Graph g = read_graph(n, m);` `WGraph g = read_wgraph(n, m);` |
| `bfs` | 最短距離(辺の本数) | `vector<int> dist = bfs(g, s);` |
| `dijkstra` | 最短距離(重みは 0 以上) | `vector<ll> dist = dijkstra(g, s);` |
| `bfs01` | 最短距離(重みが 0 か 1) | `vector<ll> dist = bfs01(g, s);` |
| `topological_sort` | トポロジカルソート | `vector<int> order = topological_sort(g);` 長さが `n` 未満なら閉路あり |
| `tree_diameter` | 木の直径 | `auto [d, u, v] = tree_diameter(g);` |
| `lca` | 最小共通祖先と、木の上の距離 | `LCA lca(g, root);` `lca.query(u, v)` `lca.dist(u, v)` |

`read_graph(n, m, directed, offset)` の後ろ2つは省略できます。

- `directed`:`true` で有向グラフ。省略すると無向グラフ。
- `offset`:入力の頂点番号から引く数。省略すると 1(1 始まりの入力)。0 始まりの入力なら 0。

### 探索(`search/`)

| 名前 | 内容 | 使い方 |
|---|---|---|
| `bisect` | めぐる式二分探索 | `ll x = bisect(ok, ng, [&](ll mid) { return 条件; });` 小数は `bisect_real` |
| `bit_search` | bit全探索 | `bit_search(n, [&](const vector<int>& chosen) { ... });` |
| `two_pointers` | 尺取り法 | 下の例を参照 |

`bisect` は「条件を満たす値のうち、いちばん `ng` に近いもの」を返します。`ok` と `ng` は、どちらが大きくても構いません。

```cpp
// a が昇順のとき、a[i] >= x となる最小の i (無ければ n)
ll i = bisect(n, -1, [&](ll mid) { return a[mid] >= x; });
```

`two_pointers` は、各左端 `l` について、区間 `[l, r)` が条件を満たす最大の `r` を返します。

```cpp
// 和が k 以下の区間 (a の要素は 0 以上)
ll sum = 0;
vector<int> right = two_pointers(
    n, [&](int i) { return sum + a[i] <= k; },  // i 番目を足しても条件を満たすか
    [&](int i) { sum += a[i]; },                // i 番目を足す
    [&](int i) { sum -= a[i]; });               // i 番目を外す
// 条件を満たす区間の個数は、right[l] - l の合計
```

### 累積和(`cumsum/`)

| 名前 | 内容 | 使い方 |
|---|---|---|
| `cumsum` | 1次元累積和 | `CumSum cs(a);` `cs.sum(l, r)`(`[l, r)` の和) |
| `cumsum2d` | 2次元累積和 | `CumSum2D cs(a);` `cs.sum(i1, j1, i2, j2)`(行 `[i1, i2)`、列 `[j1, j2)` の和) |
| `imos` | 1次元imos法 | `Imos im(n);` `im.add(l, r, x);` `vector<ll> v = im.build();` |
| `imos2d` | 2次元imos法 | `Imos2D im(h, w);` `im.add(i1, j1, i2, j2, x);` `auto v = im.build();` |

`add` の `x` を省略すると 1 を足します。

### 数学(`math/`)

| 名前 | 内容 | 使い方 |
|---|---|---|
| `sieve` | エラトステネスの篩 | `Sieve sv(n);` `sv.is_prime(x)` `sv.primes` `sv.factorize(x)` |
| `factorize` | 素因数分解(O(√n)) | `for (auto [p, e] : factorize(n)) { ... }` |
| `divisors` | 約数列挙(昇順) | `for (ll d : divisors(n)) { ... }` |
| `binomial` | 二項係数(mod つき) | `Binomial<mint> bc(n);` `bc.C(n, r)` `bc.P(n, r)` `bc.H(n, r)` |
| `matrix` | 行列の積・累乗(mod つき) | `Matrix a(n, vector<ll>(n, 0));` `a * b` `matpow(a, k)` |

- `binomial` の `mint` は ACL の modint です(`using mint = atcoder::modint998244353;`)。
- `matrix` の mod は、貼ったコードの中の `MOD` を書き換えます。
- 素因数分解を何度も行うときは `sieve`、大きな数を1回だけなら `factorize` が向いています。

### AHC(`ahc/`)

| 名前 | 内容 | 使い方 |
|---|---|---|
| `xorshift` | 速い乱数 | `XorShift rng;` `rng.next_int(n)`(0 以上 n 未満) `rng.next_double()`(0 以上 1 未満) |
| `timer` | 経過時間 [秒] | `Timer timer;` `if (timer.elapsed() > 1.9) { break; }` |
| `annealing` | 焼きなまし法の雛形(先に `timer` と `xorshift`) | 下の例を参照 |

`annealing` は、問題ごとに「状態」を表す構造体を書いて渡します。用意するのは、スコアと3つの関数です。

```cpp
struct State {
  vector<int> x;     // 解の中身 (問題に合わせる)
  double score = 0;  // 今のスコア (最初の状態のスコアを入れておく)

  // 近傍 (小さな変更) を1つ選んで返す。型は自由 (int、pair、構造体など)
  int random_move(XorShift& rng) {
    return rng.next_int(x.size());
  }
  // その変更をしたら、スコアがいくつ増えるか (減るなら負の数)
  double diff(int i) const {
    return x[i] == 0 ? 1 : -1;
  }
  // その変更を実際に行う (score は anneal が更新するので、ここでは触らない)
  void apply(int i) {
    x[i] ^= 1;
  }
};

// 1.8 秒間、温度を 2.0 から 0.01 まで下げながら探す。スコアが最大だった状態が返る
State best = anneal(state, 1.8, 2.0, 0.01);
```

スコアを最小化したい問題では、符号を反転したものを `score` にします。

## 使用例:最短距離を求める

頂点数 `n`、辺数 `m` の重みつき無向グラフ(1 始まり)で、頂点 1 から頂点 `n` への最短距離を出力します。

```cpp
#include <bits/stdc++.h>
#include "graph/dijkstra.hpp"
using namespace std;
using ll = long long;

int main() {
  int n, m;
  cin >> n >> m;
  WGraph g = read_wgraph(n, m);     // 頂点番号から 1 を引いて読み込む
  vector<ll> dist = dijkstra(g, 0); // 頂点 1 は、0 始まりでは 0
  cout << dist[n - 1] << endl;      // 届かないときは -1
  return 0;
}
```

スニペットを使う場合は、`#include "graph/dijkstra.hpp"` の代わりに、`graph`、`dijkstra` の順に貼ります。

## テスト

各機能は、小さなランダム入力を作って、単純で確実な解き方と突き合わせる方法でテストしています(例:Dijkstra法 ↔ ワーシャルフロイド法、篩 ↔ 試し割り、二項係数 ↔ パスカルの三角形)。テストは `tests/test_<分野>.cpp` にあります。

```bash
cpe libtest
```

- 既定では、デバッグ用フラグ(配列外参照やオーバーフローを検出する設定)で実行します。`-r` を付けると通常のフラグで実行します。
- `cpe libtest graph` のように、名前の一部で対象を絞れます。
- テストの前に、各ヘッダが単体で読み込めること(ほかのヘッダを先に読んでいることに頼っていないこと)も確かめます。

## ライブラリを足す・直すとき

1. `library/<分野>/<名前>.hpp` を書きます。先頭は次の形にします。

   ```cpp
   #pragma once
   // @snippet 名前
   // @desc 候補に表示する説明
   #include "base.hpp"
   ```

   - `// @snippet` の行が無いファイルは、スニペットになりません(`base.hpp` がその例です)。
   - ほかのライブラリを使うときは `#include "graph.hpp"` のように書きます。スニペットにするときは、この行が取り除かれ、説明に `[先に貼る: graph]` が付きます。
   - `base.hpp` は、ライブラリを単体でコンパイルするための前置き(`bits/stdc++.h`、`using namespace std;`、`using ll`)です。スニペットではありません。
2. `tests/test_<分野>.cpp` にテストを足します。
3. `cpe libtest` で確かめます。
4. `cpe vscode` でスニペットを配り直します。

テンプレート(`templates/*.cpp`)も同じ仕組みでスニペットになります。`// @cursor` と書いた行が、貼り付けたあとのカーソル位置になります。
