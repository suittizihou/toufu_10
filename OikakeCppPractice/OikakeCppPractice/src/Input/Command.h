#pragma once


/**
 * @file Command.h
 * @brief ���͂̃Q�[���p�̃{�^����`�w�b�_�[
 * @author ���]
 * @date Unknown
 */

 /**
  * @enum Command
  * �Q�[���p�̃{�^��
  */
enum class Command {
	//!�Q�[�������
	ShutDown,
	//!���̍U��
	SwordSlash,
	//!�X�e�b�v
	Step,
	//!����
	Run,
	//!����{�^��
	Decide,
	//!�߂�{�^��
	Cancel,
	//!�����\����
	Guard,
	//!���o�X�L�b�v
	Skip,
	//!�|�[�Y
	Pause,
	//!���ׂẴ{�^���g���K�[����
	AnyInputDown,
	//!�ő�R�}���h��
	Max_Of_Num
};

