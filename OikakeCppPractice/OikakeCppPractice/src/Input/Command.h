#pragma once


/**
 * @file Command.h
 * @brief 入力のゲーム用のボタン定義ヘッダー
 * @author 阿曽
 * @date Unknown
 */

 /**
  * @enum Command
  * ゲーム用のボタン
  */
enum class Command {
	//!ゲームを閉じる
	ShutDown,
	//!剣の攻撃
	SwordSlash,
	//!ステップ
	Step,
	//!走る
	Run,
	//!決定ボタン
	Decide,
	//!戻るボタン
	Cancel,
	//!盾を構える
	Guard,
	//!演出スキップ
	Skip,
	//!ポーズ
	Pause,
	//!すべてのボタントリガー入力
	AnyInputDown,
	//!最大コマンド数
	Max_Of_Num
};

