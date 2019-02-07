#pragma once

/**
 * @file Assets.h
 * @brief ゲーム内で使用するアセットの定義ファイル
 * @author 阿曽
 * @date 2017/2/23
 */

 //! Assetsの名前空間
namespace Assets {
	/**
	* @enum Texture
	* 使用するテクスチャの定義
	*/
	enum class Texture {
		// タイル ===================================================

		NormalTile,
		Hole,
		NormalToufuTile,
		MetalToufuTile,
		BlueTile,
		RedTile,

		// ==========================================================

		Background,
		Player,
		Player2,
		Ninja,
		Ninja_Front_Anime,
		Ninja_Back_Anime,
		Ninja_Left_Anime,
		Ninja_Right_Anime,
		Kinniku,
		Kinniku_Front_Anime,
		Kinniku_Back_Anime,
		Kinniku_Left_Anime,
		Kinniku_Right_Anime,
		Yoroi,
		Kakutouka,
		NormalToufu,
		MetalToufu,
		Number,
		Title,

		// タイトル画面 ==============================================

		Title1,
		Title2,
		Title3,
		Title4,
		White,

		// ===========================================================

		// 説明画面 ==================================================

		tutorial1,
		tutorial2,

		//============================================================
		
		// プレイヤー選択画面 =========================================

		choosebase,
		choose1,
		choose2,
		choose3,
		choose4,
		choose1_walk,
		choose2_walk,
		choose3_walk,
		choose4_walk,

		// リザルト =========================================
		
		// 背景
		Result,

		// 歯医者
		Result_Loser1,
		Result_Loser2,
		Result_Loser3,
		Result_Loser4,

		// 勝者
		Result_Winner1,
		Result_Winner2,
		Result_Winner3,
		Result_Winner4,

		// メニュー
		Result_Menu,
		Result_Menu1,
		Result_Menu2,
		Result_Menu3,
		// ==================================================
	
		None,
	};
}