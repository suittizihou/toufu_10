#pragma once

/**
 * @file Assets.h
 * @brief �Q�[�����Ŏg�p����A�Z�b�g�̒�`�t�@�C��
 * @author ���]
 * @date 2017/2/23
 */

 //! Assets�̖��O���
namespace Assets {
	/**
	* @enum Texture
	* �g�p����e�N�X�`���̒�`
	*/
	enum class Texture {
		// �^�C�� ===================================================

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
		Yoroi,
		Kakutouka,
		NormalToufu,
		MetalToufu,
		Number,
		Title,

		// �^�C�g����� ==============================================

		Title1,
		Title2,
		Title3,
		Title4,
		White,

		// ===========================================================

		// ������� ==================================================

		tutorial1,
		tutorial2,

		//============================================================
		
		// �v���C���[�I����� =========================================

		choosebase,
		choose1,
		choose2,
		choose3,
		choose4,
		choose1_walk,
		choose2_walk,
		choose3_walk,
		choose4_walk,

		// ���U���g =========================================
		
		// �w�i
		Result,

		// �����
		Result_Loser1,
		Result_Loser2,
		Result_Loser3,
		Result_Loser4,

		// ����
		Result_Winner1,
		Result_Winner2,
		Result_Winner3,
		Result_Winner4,

		// ���j���[
		Result_Menu,
		Result_Menu1,
		Result_Menu2,
		Result_Menu3,
		// ==================================================
	
		None,
	};
}