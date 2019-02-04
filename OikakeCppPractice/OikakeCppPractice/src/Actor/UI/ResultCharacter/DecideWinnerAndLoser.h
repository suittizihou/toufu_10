#pragma once
#include "Utility/Assets.h"

class DecideWinnerAndLoser {
public:
	// �������L�����N�^�[�̃e�N�X�`�����Z�b�g����
	static void SetWinnerCharacter(Assets::Texture winner_character);

	// �������L�����N�^�[�̃e�N�X�`�����Z�b�g����
	static void SetLoserCharacter(Assets::Texture loser_character);

	// �������L�����N�^�[�̃e�N�X�`����Ԃ�
	static Assets::Texture GetWinnerCharacter();

	// �������L�����N�^�[�̃e�N�X�`����Ԃ�
	static Assets::Texture GetLoserCharacter();

private:
	static Assets::Texture winner_character_texture;	// �������L�����N�^�[�̃e�N�X�`��
	static Assets::Texture loser_character_texture;		// �������L�����N�[�̃e�N�X�`��
};