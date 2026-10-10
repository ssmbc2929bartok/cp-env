# ばるとーく式競技プログラミング環境

Docker と VS Code Dev Containers で作る、C++ の競技プログラミング環境です。
コンテナの中に AtCoder と同じ GCC 15.2.0 と AtCoder Library(ACL)を入れ、`cpe` というコマンド1つで、サンプルのテストから提出用ファイルの作成までを行います。

対象:AtCoder(アルゴリズム・ヒューリスティック)、Codeforces、yukicoder、ICPC国内予選、作問(yukicoder)

## できること

- ブラウザ拡張 [Competitive Companion](https://github.com/jmerle/competitive-companion) から問題を受け取り、ソースとサンプルを自動で用意する
- サンプルを全部流して AC / WA / RE / TLE を表示する(`cpe test`。VS Code では Ctrl+Shift+B)
- 配列外参照や符号付きオーバーフローをデバッグ用フラグで検出し、原因の行を要約して表示する(`cpe test -d`)
- 愚直解と突き合わせて、出力が食い違う入力を乱数で探す(`cpe stress`)
- `#include` を展開して、提出用の1ファイルを作る(`cpe bundle`)
- ジャッジごとのコンパイル設定を、フォルダ名から自動で選ぶ
- 生成AIの扱いが違う2つのコンテナ(アルゴリズム用・ヒューリスティック用)を使い分ける

提出はブラウザから行います(コマンドからの提出機能はありません)。

## 必要なもの

- [Docker Desktop](https://www.docker.com/products/docker-desktop/)
- [VS Code](https://code.visualstudio.com/) と拡張「Dev Containers」
- ブラウザ拡張 Competitive Companion

## セットアップ

1. このリポジトリを clone します。

   ```bash
   git clone https://github.com/ssmbc2929bartok/cp-env.git
   ```

2. 2つのフォルダの場所を、環境変数に登録します。どちらかが未設定だと、コンテナが起動しません。

   | 環境変数 | 内容 |
   |---|---|
   | `CP_CONTEST_DIR` | コンテストのソースを置くフォルダ(Dropbox などで同期しているフォルダでも可) |
   | `CP_PROBLEMS_DIR` | 作問用のフォルダ(作問をしない場合は、空のフォルダで構いません) |

   Windows(PowerShell):

   ```powershell
   setx CP_CONTEST_DIR  "C:\path\to\contest"
   setx CP_PROBLEMS_DIR "C:\path\to\problems"
   ```

   macOS(`~/.zshenv`):

   ```bash
   export CP_CONTEST_DIR="$HOME/path/to/contest"
   export CP_PROBLEMS_DIR="$HOME/path/to/problems"
   ```

   登録したあとは、VS Code を完全に終了して開き直します。

3. VS Code で `cp-env` フォルダを開き、コマンドパレットから「Dev Containers: コンテナーで再度開く」を実行して、使うコンテナを選びます。初回はイメージのビルドに時間がかかります(yuki-tool をソースからビルドするため)。

   | コンテナ | 用途 | 最初に開くフォルダ | ポート |
   |---|---|---|---|
   | `cp-env` | アルゴリズム(ABC・Codeforces・ICPC・作問など) | `contest/` | 10043 |
   | `cp-env for AHC` | ヒューリスティック(AHC) | `contest/AtCoder/AHC/` | 10044 |

4. コンテナ内のターミナルで、次の2つを実行します。

   ```bash
   cpe vscode
   ```

   ```bash
   cpe warmup
   ```

   - `cpe vscode`:VS Code のタスクを、各作業フォルダの `.vscode/` に書き出します。
   - `cpe warmup`:`<bits/stdc++.h>` を先にコンパイルしておきます(以後のコンパイルが速くなります)。

5. Competitive Companion の設定で、カスタムポートに `10044` を足します(`10043` は最初から入っています)。

## 使い方

### 1問を解く流れ

1. ブラウザで問題のページを開き、Competitive Companion のボタンを押します。ソース(テンプレートから作成)とサンプルが保存されます。
2. ソースを書きます。保存すると `.clang-format` に従って自動で整形されます。
3. Ctrl+Shift+B でサンプルを流します(ターミナルからは `cpe test C.cpp`)。
4. 自作ライブラリや ACL の展開が必要なジャッジでは、`cpe bundle C.cpp` で提出用のファイルを作ります。
5. ブラウザから提出します。

サンプルの受信(`cpe listen`)は、コンテナの起動時に自動で始まります。ログは `/tmp/cpe-listen.log` です。動いていないときは、ターミナルで `cpe listen` を実行してください。

### コマンド

| コマンド | 内容 |
|---|---|
| `cpe test [ソース]` | `tests/<ソース名>/` のケースを全部流して判定する。`-d` デバッグ用フラグ、`-c` ケースを絞る、`-e` 小数の許容誤差(既定 1e-6)、`-t` 時間制限 |
| `cpe run [ソース]` | コンパイルして実行し、標準入力をそのまま渡す。`-i` で入力ファイルかケース名(`sample-1` など)を指定 |
| `cpe add [ソース]` | 自作の入力 `custom-N.in` を足す(ターミナルに貼り付けて Ctrl+D)。`-o` で期待する出力も足す |
| `cpe new <ファイル>...` | テンプレートからソースを作る。`-t` でテンプレート名を指定 |
| `cpe stress <解> <愚直解> <生成器>` | 生成器に通し番号を渡して入力を作り、2つの出力が食い違うまで回す。見つけた入力は `stress-N.in` / `.out` に保存する |
| `cpe bundle [ソース]` | `#include "..."` を展開して `submit/<ソース名>.cpp` を作り、提出先と同じ条件でコンパイルできるかを確かめる |
| `cpe build [ソース]` | コンパイルだけする |
| `cpe warmup` | `<bits/stdc++.h>` を全設定分、先にコンパイルしておく |
| `cpe listen` | Competitive Companion からサンプルを受け取って保存する |
| `cpe vscode` | `vscode/` の原本を、各作業フォルダの `.vscode/` に書き出す |

- `[ソース]` を省略すると、今いるフォルダで最後に保存した `.cpp` を使います。拡張子 `.cpp` も省略できます(`cpe test C`)。
- `cpe b`・`cpe t`・`cpe r` は、それぞれ `build`・`test`・`run` の短い書き方です。
- ソースと読み込んだファイルが前回から変わっていなければ、コンパイルを省略します(`-f` で強制)。
- 実行ファイルは `~/.cache/cpe/` に置くので、コンテスト用のフォルダには入りません。
- 期待する出力(`.out`)が無いケースは、判定せずに出力だけを表示します。

VS Code のタスク(「タスクの実行」から選ぶ):`cpe: test`(Ctrl+Shift+B)、`cpe: test (debug)`、`cpe: build`、`cpe: bundle`、`cpe: run`、`cpe: add`

### フォルダの並び

ソースはコンテストごとのフォルダに並べ、テストケースは同じフォルダの `tests/<ソース名>/` に置きます。

```
contest/AtCoder/ABC/478/
├─ C.cpp
├─ submit/C.cpp          cpe bundle が作る提出用ファイル
└─ tests/C/
    ├─ sample-1.in, sample-1.out
    ├─ custom-1.in       自作の入力
    └─ problem.json      時間制限・URL・インタラクティブかどうか
```

受信した問題の保存先は、URL から決まります。

| サイト | ソースの保存先 |
|---|---|
| AtCoder(`abc478` など「英字3文字+数字」のコンテスト) | `AtCoder/ABC/478/C.cpp` |
| AtCoder(それ以外。`typical90` など) | `AtCoder/Others/typical90/AB.cpp` |
| Codeforces | `Codeforces/2100/A.cpp` |
| yukicoder | `yukicoder/3000.cpp` |
| その他 | `Others/<サイト>/<問題名>.cpp` |

2つのコンテナを同時に開いているときは、AHC の問題はヒューリスティック用、それ以外はアルゴリズム用のコンテナが保存します。

## 設定を変える

| 変えたいもの | 場所 |
|---|---|
| ジャッジ別のコンパイル設定 | `profiles.toml` |
| ソースを新しく作るときのテンプレート | `templates/<設定名>.cpp`(無ければ `templates/default.cpp`。インタラクティブ問題の受信時は `templates/interactive.cpp` を優先) |
| 整形のルール | `.clang-format` |
| VS Code のタスク | `vscode/tasks.json`(変更後に `cpe vscode`) |
| コンテナの設定 | `.devcontainer/devcontainer.json` と `.devcontainer/ahc/devcontainer.json` の両方 |
| イメージに入れるもの | `Dockerfile` |

コンパイル設定は、ソースのパスに含まれるフォルダ名で決まります(`-p 設定名` で指定もできます)。すべて `-std=gnu++23 -Wall -Wextra -DLOCAL` を付けます。

| 設定 | フォルダ名 | 追加のフラグ | `cpe bundle` での ACL |
|---|---|---|---|
| `ahc` | `AHC` | `-O2 -march=native -ftrivial-auto-var-init=zero` | そのまま |
| `atcoder` | `AtCoder` | 上と同じ + `-fconstexpr-*`(AtCoder 本番と同じ値) | そのまま |
| `codeforces` | `Codeforces` | `-O2` | 展開する |
| `yukicoder` | `yukicoder` | `-O2` | そのまま |
| `icpc` | `ICPC` | `-O2` | 展開する |
| `setter` | `problems` | `-O2` | 展開する |

`-d` を付けると、追加のフラグの代わりにデバッグ用フラグ(`-g -O0 -fsanitize=address,undefined -D_GLIBCXX_DEBUG` など)を使います。

## 生成AIの扱い

コンテストのルールに合わせて、エディタ内の生成AIをコンテナごとに切り替えています。

| コンテナ | 設定 |
|---|---|
| `cp-env`(アルゴリズム用) | エディタのAI機能をすべて無効 |
| `cp-env for AHC`(ヒューリスティック用) | GitHub Copilot の補完と Next Edit Suggestions だけ有効(C++ のみ)。エージェントは無効。見分けやすいよう、ステータスバーがオレンジ色になります |

- ヒューリスティック用の設定は、短期AHCのルール(指定された補完機能だけ可)に合わせています。
- ルールは更新されます。コンテストの前に、[AtCoder生成AI対策ルール](https://info.atcoder.jp/entry/llm-rules-ja)・[短期AHCのルール](https://info.atcoder.jp/entry/short-ahc-llm-rules-ja)・[長期AHCのルール](https://info.atcoder.jp/entry/ahc-llm-rules-ja) の最新版を確認してください。
- このリポジトリには、生成AI(Claude)を使って書いたコードが含まれます(`tools/cpe` など)。

## 入っているもの

| 部品 | 版 |
|---|---|
| GCC | 15.2.0(公式イメージ `gcc:15.2.0`) |
| AtCoder Library | v1.6 |
| testlib | 取得時点の最新 |
| yuki-tool | v0.5.0 |
| そのほか | Python 3、gdb、clang-format、git |

ACL・testlib・yuki-tool は、イメージのビルド時に取得します。このリポジトリには含めていません。

## 動作確認した環境

- Windows 11 + Docker Desktop(WSL 2)+ VS Code の Dev Containers 拡張
- macOS(Apple Silicon)は未確認です。ARM では `-march=native` の結果などが AtCoder 本番(x86-64)と変わるため、実行速度は参考程度にしてください。

自作ライブラリ(`library/`)と、AHC のローカルテストは準備中です。

## ライセンス

[CC0 1.0 Universal](LICENSE)。表示の義務はないので、提出コードにそのまま貼り付けて使えます。
