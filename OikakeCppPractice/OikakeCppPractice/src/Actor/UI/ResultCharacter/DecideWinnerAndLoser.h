#pragma once
#include "Utility/Assets.h"

class DecideWinnerAndLoser {
public:
	// 勝ったキャラクターのテクスチャをセットする
	static void SetWinnerCharacter(Assets::Texture winner_character);

	// 負けたキャラクターのテクスチャをセットする
	static void SetLoserCharacter(Assets::Texture loser_character);

	// 勝ったキャラクターのテクスチャを返す
	static Assets::Texture GetWinnerCharacter();

	// 負けたキャラクターのテクスチャを返す
	static Assets::Texture GetLoserCharacter();

private:
	static Assets::Texture winner_character_texture;	// 勝ったキャラクターのテクスチャ
	static Assets::Texture loser_character_texture;		// 負けたキャラクーのテクスチャ
};