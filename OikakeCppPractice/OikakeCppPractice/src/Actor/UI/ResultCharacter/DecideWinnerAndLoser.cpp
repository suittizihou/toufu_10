#include "DecideWinnerAndLoser.h"

Assets::Texture DecideWinnerAndLoser::winner_character_texture = Assets::Texture::Result_Winner1;
Assets::Texture DecideWinnerAndLoser::loser_character_texture = Assets::Texture::Result_Loser4;

void DecideWinnerAndLoser::SetWinnerCharacter(Assets::Texture winner_character)
{
	// �w�肳�ꂽ�e�N�X�`���������L�����N�^�[�̉摜���`�F�b�N
	if (static_cast<int>(Assets::Texture::Result_Winner1) <= static_cast<int>(winner_character) && static_cast<int>(winner_character) <= static_cast<int>(Assets::Texture::Result_Winner1)) {
		// ���v�Ȃ�����
		winner_character_texture = winner_character;
	}
}

void DecideWinnerAndLoser::SetLoserCharacter(Assets::Texture loser_character)
{
	// ����҉摜���`�F�b�N
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
