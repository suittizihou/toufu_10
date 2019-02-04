#include "DecideWinnerAndLoser.h"

Assets::Texture DecideWinnerAndLoser::winner_character_texture = Assets::Texture::Result_Winner1;
Assets::Texture DecideWinnerAndLoser::loser_character_texture = Assets::Texture::Result_Loser4;

void DecideWinnerAndLoser::SetWinnerCharacter(Assets::Texture winner_character)
{
	// 指定されたテクスチャが勝ちキャラクターの画像かチェック
	if (static_cast<int>(Assets::Texture::Result_Winner1) <= static_cast<int>(winner_character) && static_cast<int>(winner_character) <= static_cast<int>(Assets::Texture::Result_Winner1)) {
		// 大丈夫なら入れる
		winner_character_texture = winner_character;
	}
}

void DecideWinnerAndLoser::SetLoserCharacter(Assets::Texture loser_character)
{
	// 歯医者画像かチェック
	if (static_cast<int>(Assets::Texture::Result_Loser1) <= static_cast<int>(loser_character) && static_cast<int>(loser_character) <= static_cast<int>(Assets::Texture::Result_Loser4)) {
		loser_character_texture = loser_character;
	}
}

Assets::Texture DecideWinnerAndLoser::GetWinnerCharacter()
{
	return winner_character_texture;
}

Assets::Texture DecideWinnerAndLoser::GetLoserCharacter()
{
	return loser_character_texture;
}
