# 📐 アーキテクチャ設計書

## 全体構成図

```
┌──────────────────────────────────────────────────────────────┐
│                      Application Layer                       │
│  (main.c, application.c)                                     │
│  - イベントループ                                            │
│  - ユーザー入力処理                                          │
│  - UI制御                                                    │
│  - 状態遷移の調整                                            │
└────────────────┬─────────────────────────────────┬───────────┘
                 │                                 │
                 ↓                                 ↓
        ┌─────────────────┐            ┌─────────────────┐
        │  Domain Layer   │            │  I/O Layer      │
        │  (core.c)       │            │  (io.c)         │
        │                 │            │                 │
        │ ビジネスロジック │            │ プラットフォーム│
        │ 純粋関数        │            │ 依存処理        │
        └─────────────────┘            └─────────────────┘
                 ↑                                 ↑
                 └────────────────┬────────────────┘
                                  │
                           ┌─────────────┐
                           │ types.h     │
                           │ データ型定義 │
                           └─────────────┘
```

## データフロー

```
User Input (Key Press)
      ↓
┌─────────────────────────────────┐
│ handle_user_input()             │
│ (Transforms key → Event)        │
└──────────────┬──────────────────┘
               ↓
┌─────────────────────────────────┐
│ apply_event()                   │
│ (Pure state transition)         │
│ Current State + Event → New State│
└──────────────┬──────────────────┘
               ↓
┌─────────────────────────────────┐
│ Hardware Synchronization        │
│ (Side effects)                  │
│ - Set relay state               │
│ - Control magnetron             │
└──────────────┬──────────────────┘
               ↓
┌─────────────────────────────────┐
│ status_to_display()             │
│ (Pure transformation)           │
│ State → Display Data            │
└──────────────┬──────────────────┘
               ↓
            Display
```

## 責務の詳細

### types.h
**責務**: データ型の定義
**特徴**:
- イミュータブルな構造体定義
- エニュメーション定義
- ビジネスルールに関連した型のみ

### core.c
**責務**: 純粋なビジネスロジック
**特徴**:
- 外部依存なし
- 100% テスト可能
- 決定論的
- キャッシュ可能（同じ入力に対して同じ出力）

**関数分類**:
```
状態遷移:     apply_event()
計算:         calculate_remaining_time(), get_magnetron_cycle()
検証:         validate_cooking_config()
ファクトリ:   create_initial_state()
変換:         status_to_display()
ユーティリティ: next_power_level(), next_cooking_time()
```

### io.c
**責務**: プラットフォーム依存の処理
**特徴**:
- 複数の実装を持つインターフェース
- プラットフォーム判定（#ifdef）
- ハードウェア制御
- I/O操作

**インターフェース**:
```c
DisplayInterface     // コンソール、LCD、Web
InputInterface       // キーボード、タッチ、MQTT
HardwareInterface    // リレー、マグネトロン制御
TimerInterface       // システムタイマー
```

### application.c
**責務**: 統合とオーケストレーション
**特徴**:
- イベントループの管理
- 純粋関数と副作用の分離
- ハードウェア同期
- UI更新

## 設計パターン

### 1. Strategy パターン
```c
typedef struct {
    void (*clear_screen)(void);
    void (*print_status)(DisplayData);
} DisplayInterface;

// 複数の実装を切り替え可能
DisplayInterface console = create_console_display();
DisplayInterface lcd = create_lcd_display();
```

### 2. Factory パターン
```c
MicrowaveApp app_create(void);
IOContext create_io_context(void);
```

### 3. Observer パターン（イベントドリブン）
```c
Event event = handle_user_input(key);
apply_state_transition(app, event);
```

### 4. State パターン（有限状態機械）
```c
MicrowaveStatus apply_event(current_state, event);
```

## 制御フロー

### 初期化
```c
MicrowaveApp app = app_create();
├─ IOContext io = create_io_context();
│  ├─ DisplayInterface display = create_console_display();
│  ├─ InputInterface input = create_console_input();
│  ├─ HardwareInterface hw = create_mock_hardware();
│  └─ TimerInterface timer = create_system_timer();
├─ MicrowaveStatus state = create_initial_state();
└─ CookingConfig config = {10, POWER_500W};
```

### メインループ
```
while (app.running) {
    1. タイマーティックを確認
       └─ 1秒経過したら EVENT_TIMER_TICK を生成
    
    2. ユーザー入力を確認
       └─ キー入力 → handle_user_input() → Event
    
    3. イベントを処理
       └─ apply_state_transition(app, event)
    
    4. UI更新
       └─ render_ui(app)
    
    5. CPU休止
       └─ sleep_ms(50)
}
```

### シャットダウン
```c
app_destroy(&app);
├─ hardware.set_relay(RELAY_OFF);
├─ hardware.set_magnetron(MAGNETRON_OFF);
└─ input.non_blocking_mode(false);
```

## 状態遷移図

```
STANDBY (初期状態)
    │ event: EVENT_START_COOKING
    ├─ remaining_time > 0?
    │  ├─ YES → COOKING ──────┐
    │  └─ NO  → STANDBY       │
    │                         │
    │ event: EVENT_CONFIG_     │
    │        CHANGED          │
    ├─ UPDATE time & power    │
    └─ STAY STANDBY           │
                              │
COOKING                       │
    ├─ event: EVENT_PAUSE    │
    │  └─ PAUSED            │
    ├─ event: EVENT_TIMER_TICK
    │  ├─ remaining_time > 0?
    │  │  ├─ YES → COOKING
    │  │  └─ NO  → COMPLETED
    │  │            ├─ magnetron_state = OFF
    │  │            └─ relay_state = OFF
    │  
PAUSED
    ├─ event: EVENT_RESUME
    │  └─ COOKING ◄──────────┤
    ├─ event: EVENT_STOP
    │  └─ STANDBY ◄──────────┤

COMPLETED
    ├─ event: EVENT_STOP
    │  └─ STANDBY

ANY STATE
    └─ event: EVENT_STOP
       └─ STANDBY (always allow emergency stop)
```

## テスト戦略

### ユニットテスト
```c
// core.c の純粋関数はテストが容易
void test_apply_event_start_cooking() {
    MicrowaveStatus initial = create_initial_state();
    Event event = {.type = EVENT_START_COOKING};
    
    MicrowaveStatus result = apply_event(initial, event);
    
    assert(result.state == STATE_COOKING);
    // 外部依存なし、完全に予測可能
}
```

**メリット**:
- 実行が高速
- 再現性が高い
- CI/CD統合が容易
- デバッグが簡単

### インテグレーションテスト
```c
// application層を含めたテスト
void test_complete_cooking_cycle() {
    MicrowaveApp app = app_create();
    
    // 調理開始
    apply_state_transition(&app, {EVENT_START_COOKING});
    assert(app.current_state.state == STATE_COOKING);
    
    // タイマーティック × n
    // ハードウェア状態確認
    // UI状態確認
}
```

### E2E テスト
```c
// 全体的な動作確認
// キーボード入力 → 表示確認 → ハードウェア動作確認
```

## 拡張のシナリオ

### シナリオ1: 新しい表示バックエンド（LCD）
```
変更範囲: io.c のみ
1. create_lcd_display() を実装
2. lcd_clear_screen() を実装
3. lcd_print_status() を実装
その他のファイルは変更不要
```

### シナリオ2: 新しいイベント型（自動調理）
```
変更範囲: types.h, core.c
1. types.h に EVENT_AUTO_COOK を追加
2. core.c の apply_event() を拡張
既存のイベント処理は影響を受けない
```

### シナリオ3: プラットフォーム追加（リアルタイムOS）
```
変更範囲: io.c のみ
1. create_rtos_display() を実装
2. create_rtos_input() を実装
3. create_rtos_timer() を実装
ビジネスロジックは変更不要
```

### シナリオ4: 自動テスト框架の統合
```
変更: CMakeLists.txt に test_core.c を追加
既存の実装コードは変更不要
```

## パフォーマンス考慮事項

### メモリ効率
- イミュータブル構造体を返すため、コピーコストあり
- **最適化**: 大規模状態では値型ではなく参照を検討

### CPU効率
- イベントループで 50ms のスリープ
- 実装依存だが、調整可能
- **最適化**: より小さな粒度に変更可能

### 遅延
- ユーザー入力から画面表示まで: 最大 50ms + 1秒のティック
- **最適化**: タイマーティック周期を短縮

## セキュリティ考慮事項

### 入力検証
```c
// すべての設定値は validate_cooking_config() でチェック
Result result = validate_cooking_config(config);
if (!result.success) {
    // エラー処理
}
```

### バッファオーバーフロー
- イミュータブル設計により、メモリ破損リスクが低い
- DisplayData の文字列は const char* で固定

### リソースリーク
- app_destroy() で安全にシャットダウン
- ハードウェアを安全な状態にリセット

## ドキュメント戦略

### コード内ドキュメント
- 各関数に目的と副作用を明記
- 複雑なロジックに説明コメント

### 型システムとしてのドキュメント
```c
// 型の名前が機能を説明
MicrowaveStatus  // 現在の状態
CookingConfig    // 設定値（イミュータブル）
DisplayData      // 表示用データ
```

### テストとしてのドキュメント
- テストコードが使用パターンを示す
- test_core.c が api の使用例

## 今後の改善提案

1. **非同期イベントの大幅な改善**: キューイング機構の実装
2. **ロギング機構**: トレーシング用のイベントログ
3. **パラメータ最適化**: マグネトロンサイクルを調整可能に
4. **マルチスレッド対応**: タイマー処理をスレッド化
5. **ネットワーク対応**: MQTT/REST API の追加
6. **設定永続化**: 設定値をファイルに保存
7. **エラー恢復**: グレースフルなエラーハンドリング
