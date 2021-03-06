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
		//忍者
		Ninja,
		Ninja_Back,
		Ninja_Front_Anime,
		Ninja_Back_Anime,
		Ninja_Left_Anime,
		Ninja_Right_Anime,
		Ninja_Icon,
		Ninja_Icon_Cry,
		Ninja_Icon2,
		Ninja_Icon_Cry2,
		Ninja_point,
		//筋肉
		Kinniku,
		Kinniku_Back,
		Kinniku_Front_Anime,
		Kinniku_Back_Anime,
		Kinniku_Left_Anime,
		Kinniku_Right_Anime,
		Kinniku_Icon,
		Kinniku_Icon_Cry,
		Kinniku_Icon2,
		Kinniku_Icon_Cry2,
		Kinniku_point,

		//鎧
		Yoroi,
		Yoroi_Back,
		Yoroi_Front_Anime,
		Yoroi_Back_Anime,
		Yoroi_Left_Anime,
		Yoroi_Right_Anime,
		Yoroi_Icon,
		Yoroi_Icon_Cry,
		Yoroi_Icon2,
		Yoroi_Icon_Cry2,
		Yoroi_point,


		//格闘家
		Kakutouka,
		Kakutouka_Back,
		Kakutouka_Front_Anime,
		Kakutouka_Back_Anime,
		Kakutouka_Left_Anime,
		Kakutouka_Right_Anime,
		Kakutouka_Icon,
		Kakutouka_Icon_Cry,
		Kakutouka_Icon2,
		Kakutouka_Icon_Cry2,
		Kakutouka_point,

		NormalToufu,
		NormalToufu_kake1,
		NormalToufu_kake2,
		NormalToufu_kake3,
		MetalToufu,
		Kage,
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