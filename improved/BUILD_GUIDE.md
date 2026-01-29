# 🚀 ビルドと実行ガイド

## 前提条件

### Windows
- **コンパイラ**: GCC (MinGW), Clang, MSVC
- **ビルドツール**: CMake 3.10以上, Make(オプション)

### Linux/Mac
- **コンパイラ**: GCC, Clang
- **ビルドツール**: CMake 3.10以上, Make

### 最小要件
```
- C99 標準に対応したコンパイラ
- 標準C ライブラリ (libc)
```

## クイックスタート

### 方法1: CMake を使用（推奨）

```bash
# プロジェクトディレクトリに移動
cd improved

# ビルドディレクトリを作成
mkdir build
cd build

# CMake設定
cmake ..

# ビルド
cmake --build . --config Release

# 実行
./microwave          # Unix/Linux/Mac
microwave.exe        # Windows
```

### 方法2: 直接コンパイル

```bash
cd improved

# Unix/Linux/Mac
gcc -o microwave main.c core.c io.c application.c -std=c99 -Wall -Wextra

# 実行
./microwave

# Windows (MinGW)
gcc -o microwave.exe main.c core.c io.c application.c -std=c99 -Wall -Wextra
microwave.exe
```

### 方法3: Make を使用

```bash
cd improved

# ビルド
make

# 実行
make run

# クリーンアップ
make clean
```

## テストの実行

### ユニットテストをコンパイル

```bash
cd improved

# 方法1: 直接コンパイル
gcc -o test_core test_core.c core.c -std=c99 -Wall -Wextra

# テスト実行
./test_core
```

### 期待される出力

```
=== Microwave Core Logic Unit Tests ===

Test: calculate_remaining_time
  ✓ All tests passed
Test: next_power_level
  ✓ All tests passed
Test: next_cooking_time
  ✓ All tests passed
Test: get_magnetron_cycle
  ✓ All tests passed
Test: validate_cooking_config
  ✓ All tests passed
Test: apply_event_start_cooking
  ✓ All tests passed
Test: apply_event_timer_tick
  ✓ All tests passed
Test: apply_event_timer_complete
  ✓ All tests passed
Test: apply_event_pause_resume
  ✓ All tests passed
Test: create_initial_state
  ✓ All tests passed
Test: status_to_display
  ✓ All tests passed

=== All tests passed! ✓ ===
```

## トラブルシューティング

### エラー: "コンパイラが見つかりません"

**Linux/Mac:**
```bash
# GCC をインストール
sudo apt-get install build-essential  # Ubuntu/Debian
brew install gcc                       # macOS
```

**Windows:**
- [MinGW](http://www.mingw.org/) をインストール
- または [Visual Studio Community](https://visualstudio.microsoft.com/) をインストール

### エラー: "cmake: コマンドが見つかりません"

```bash
# CMake をインストール
sudo apt-get install cmake             # Ubuntu/Debian
brew install cmake                     # macOS
choco install cmake                    # Windows (Chocolatey)
```

### エラー: "_WIN32 が定義されていない"

これはターゲットプラットフォームが自動検出されずに、Windows固有のコードが有効化されていない可能性があります。

**解決方法:**
```bash
# MinGW を使用する場合
gcc -D_WIN32 -o microwave.exe ...

# または cmake を使用
cmake -G "MinGW Makefiles" ..
```

### エラー: "tcgetattr: 関数が見つかりません" (Linux)

Linux でこのエラーが出る場合は、POSIX API の別バージョンが必要です。

**解決方法:**
```bash
# 標準的な Linux システムではこれで動作します
gcc -o microwave main.c core.c io.c application.c -std=c99 -Wall

# もし問題があれば、POSIX オプション有効化
gcc -D_POSIX_C_SOURCE=200809L -o microwave ...
```

## 実行オプション

### コマンドラインオプション

現在の実装では直接的なコマンドラインオプションはありませんが、以下を検討できます：

```c
// 実装例 (main.c に追加可能)
int main(int argc, char* argv[]) {
    bool use_console = true;
    int log_level = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: microwave [options]\n");
            printf("Options:\n");
            printf("  --help           Show this help\n");
            printf("  --simulate       Use mock hardware\n");
            printf("  --log-level N    Set log level\n");
        }
    }
    
    // ...
}
```

## パフォーマンス計測

### 実行時間の計測

```bash
# Unix/Linux/Mac
time ./microwave

# または
/usr/bin/time -v ./microwave
```

### 予想される性能

| 測定項目 | 値 |
|---------|-----|
| 起動時間 | < 100ms |
| メモリ使用量 | < 1MB |
| イベント遅延 | < 50ms |
| ティック間隔 | 1秒 |
| CPU使用率 | < 1% (idle時) |

## デバッグビルド

より詳細なデバッグ情報でビルドする場合：

```bash
# CMake でデバッグビルド
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# または直接コンパイル
gcc -g -o microwave_debug main.c core.c io.c application.c -std=c99 -Wall -Wextra -O0

# デバッガで実行
gdb ./microwave_debug
```

### GDB での基本的なデバッグ

```gdb
(gdb) break apply_event
(gdb) run
(gdb) next
(gdb) print current_state
(gdb) continue
(gdb) quit
```

## CI/CD 統合例

### GitHub Actions

```yaml
name: Build and Test

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v2
    
    - name: Install dependencies
      run: sudo apt-get install -y build-essential cmake
    
    - name: Build
      run: |
        mkdir build
        cd build
        cmake ..
        cmake --build .
    
    - name: Run tests
      run: |
        cd improved
        gcc -o test_core test_core.c core.c -std=c99
        ./test_core
    
    - name: Run application
      run: cd improved && timeout 5 ./microwave || true
```

## プロファイリング

### メモリプロファイリング（Linux）

```bash
# valgrind をインストール
sudo apt-get install valgrind

# メモリリークをチェック
valgrind --leak-check=full ./microwave
```

### CPU プロファイリング

```bash
# perf をインストール
sudo apt-get install linux-tools-generic

# プロファイリング実行
sudo perf record ./microwave

# レポート表示
sudo perf report
```

## ベンチマーク

### 状態遷移性能

```c
#include <time.h>

void benchmark_apply_event(void) {
    MicrowaveStatus state = create_initial_state();
    Event event = {.type = EVENT_TIMER_TICK};
    
    clock_t start = clock();
    
    for (int i = 0; i < 1000000; i++) {
        state = apply_event(state, event);
    }
    
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("1M transitions in %.3f seconds\n", elapsed);
    printf("%.0f transitions/second\n", 1000000 / elapsed);
}
```

### 予想される性能

```
1M transitions in 0.010 seconds
100,000,000 transitions/second
```

（純粋関数のため非常に高速）

## リリース ビルド

プロダクション用最適化ビルド：

```bash
# CMake
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release

# または GCC で直接
gcc -O3 -DNDEBUG -o microwave_release \
    main.c core.c io.c application.c \
    -std=c99 -Wall -Wextra -s

# ストリップしてサイズ削減
strip microwave_release
```

### ビルドサイズ比較

```
デバッグ:     ~500KB (シンボル含)
リリース:     ~50KB  (ストリップ後)
```

## マルチプラットフォームビルド

### クロスコンパイル（Linux → Windows）

```bash
# MinGW クロスコンパイラをインストール
sudo apt-get install mingw-w64

# ビルド
i686-w64-mingw32-gcc -o microwave.exe \
    main.c core.c io.c application.c \
    -std=c99 -Wall -Wextra
```

## まとめ

| ビルド方法 | 推奨度 | 複雑度 | スピード |
|-----------|--------|--------|---------|
| CMake | ⭐⭐⭐⭐⭐ | 中 | 速い |
| 直接コンパイル | ⭐⭐⭐⭐ | 低 | 最速 |
| Make | ⭐⭐⭐ | 中 | 速い |

**初心者向け**: 直接コンパイル
**中級者向け**: CMake
**複雑なプロジェクト**: CMake + CI/CD
