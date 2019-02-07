#pragma once

/**
 * @file Scene.h
 * @brief ゲーム内で使用するシーンの定義ファイル
 * @author 阿曽
 * @date Unknown
 */

/**
 * @enum Scene
 * ゲーム内で使用するシーンの定義
 */
enum class Scene {
	//!デフォルト　＆　何のシーンでもない
	None,
	//!タイトル
	Title,
	// 動画再生シーン
	Movie,
	// キャラクターセレクト
	CharacterSelect,
	// 説明画面
	Description,
	//!ゲームメイン
	GameMain,
	//!リザルト
	Result,
	// 終了
	GameEnd
};
