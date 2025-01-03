# 論文検討 - TDD編 - 

## 論文のテーマ
テスト駆動開発

## 論文で説明したいこと
- 新製品開発では1st、2nd、3rd...というように小さな機能から少しずつ改良して完成させていく開発が行われる
　アジャイルに近い開発スタイルになること
- 派生開発においても前機種の設計を改修するという開発が行われる
- テストファーストで開発することで変化に柔軟で、かつ品質の高いソフト開発ができること
- アジャイル開発や派生開発には、変化に強いテストファーストが向いていること
- テストファーストな設計技法として「テスト駆動開発」という開発技法があること
- テストファーストを行うことで、ソースコードの結合度が下がり凝集度が上がる、コード自体の品質も上がるという副産物もあること
- 疎結合、高凝集なソフトの設計技法として「オブジェクト指向」設計があること
- オブジェクト指向で設計することで、自動テストを行いやすいコードを書くことができ、結果としてソフトの品質が上がること

## 論文の構成
### 基本構成
大きく以下の２つの章で構成する
1. 単体テストのためのソフトウェア設計  
- この章では、ソフトウェア設計について記載する  
TDDでは単体テストによって開発を回していくが、単体テストを行うためには、まずテストをしやすいソフトウェア設計が必要  
ソフトウェアの結合度を下げて、モジュールの独立性を高める設計が求められる  
その方法を記載する  

2. TDDの実践
- この章では、TDDの手法について記載する
自動テスト→テストファースト→テスト駆動開発という3ステップで説明してもよい

### その他言いたいこと
- 想定する適用範囲としては、新たにソフト構造を設計する規開発を想定する。派生開発やカーネル開発のようなソフト構造が決まっているものは適用外。
- ソフトウェア設計方法の例として「オブジェクト指向」を挙げたが、結合度の低いソフトを設計する一例なので、必ずしもオブジェクト指向である必要はない
- テスト駆動開発をいきなり実施するのはコストが掛かるので、まずは自動テスト、テストファーストから始めるのもあり

### 詳細な構成
- はじめに
    この論文は何を目的として書くのかを定義する
- 概要
    この論文の概要をまとめる
    - 現状の課題
    - 解決策
        - 低結合なソフト設計
        - 自動テスト
        - テストファーストの考え
        - テスト駆動開発
- 主題
    - 現状の課題
        デバッグ型プログラミングの課題
        実際に開発現場で見た課題
    - 解決策
        課題を解決するために何が必要か
        テスト駆動開発を導入する理由やメリットを記載する
        なぜテスト駆動開発をすると課題が解決されるのか
        テスト駆動開発をすることによって、どうしたいのか
        - 低結合なソフト設計
            自動テストを通すために必要なこと
            低結合で高凝集なソフトを書くための考え方、方法について記載する
        - 自動テスト
            自動テストとは
            自動テストの方法、メリットなどを記載する
        - テストファースト
            テストファーストとは
            テストファーストの方法、メリットなどを記載する
        - テスト駆動開発
            テスト駆動開発とは
            テスト駆動開発の方法、メリットなどを記載する
    - 結論
        - 現場で実施するために
            現場の実情に即した実践方法を記載する
            テスト駆動開発のデメリットも考慮して、現場で実践するのに最適な方法を検討する
        - 発展
            テスト駆動開発を始めることで、その後どう発展させていくか
            アジャイル開発との融合
            継続的インテグレーション
            生成AIでのコード生成におけるテスト駆動開発の応用

## 参考サイト
### 動画
・TDD Boot Campの講演<br>
<https://www.youtube.com/watch?v=Q-FJ3XmFlT8>

### テスト駆動開発の概要
- テストコードは必要か？（自動テスト・テスト駆動開発<TDD>について考える）
https://zenn.dev/yuulab/articles/45dc33feaada62

- t-wadaのブログ【翻訳】テスト駆動開発の定義
https://t-wada.hatenablog.jp/entry/canon-tdd-by-kent-beck

- 和田卓人 保守しやすく変化に強いソフトウェアを支える柱　自動テストとテスト駆動開発⁠⁠、その全体像
https://gihyo.jp/article/2024/01/automated-test-and-tdd

- テスト駆動開発（TDD）とは何か。コードで実践方法を解説します
https://panda-program.com/posts/test-driven-development

### AI * TDD
- コード生成時代のテスト駆動開発
https://www.docswell.com/s/tyonekubo/KWWX1D-tdd-with-generative-ai

## 書籍
参考図書：<br>
- C言語によるオブジェクト指向プログラミング入門（翔泳社）
- モダンC言語プログラミング（ASCII DWANGO）
- SoftwareDesign 2022年3月号
- テスト駆動開発による組み込みプログラミング（オイラリー・ジャパン）
- ソフトウェア品質を高める開発者テスト（翔泳社）