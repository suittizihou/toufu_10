#pragma once

/**
 * @file GamePad.h
 * @brief �Q�[���p�b�h�̒�`�w�b�_�[
 * @author ���]
 * @date 2017/2/5
 */

#include<DxLib.h>
//!Xbox�R���g���[���[�̍ő�{�^����
static const int MaxXboxButtonNum = 16;

/**
 * @enum GamePad
 * �Q�[���p�b�h�̎��ʂ̒�`
 */
enum class GamePad {
	//!�PP�R��
	Player1 = DX_INPUT_PAD1,
	//!�QP�R��
	Player2 = DX_INPUT_PAD2,
	//!�RP�R��
	Player3 = DX_INPUT_PAD3,
	//!�SP�R��
	Player4 = DX_INPUT_PAD4
};

/**
 * @enum XboxGamePad
 * Xbox360�̃{�^��
 */
enum class XboxGamePad {
	//!�f�W�^�������{�^����
	Dpad_Up = XINPUT_BUTTON_DPAD_UP,
	//!�f�W�^�������{�^����
	Dpad_Down = XINPUT_BUTTON_DPAD_DOWN,
	//!�f�W�^�������{�^����
	Dpad_Left = XINPUT_BUTTON_DPAD_LEFT,
	//!�f�W�^�������{�^���E
	Dpad_Right = XINPUT_BUTTON_DPAD_RIGHT,
	//!START�{�^��
	Start = XINPUT_BUTTON_START,
	//!BACK�{�^��
	Back = XINPUT_BUTTON_BACK,
	//!���X�e�B�b�N��������
	Left_Thumb = XINPUT_BUTTON_LEFT_THUMB,
	//!�E�X�e�B�b�N��������
	Right_Thumb = XINPUT_BUTTON_RIGHT_THUMB,
	//!LB�{�^��
	Left_Shoulder = XINPUT_BUTTON_LEFT_SHOULDER,
	//!RB�{�^��
	Right_Shoulder = XINPUT_BUTTON_RIGHT_SHOULDER,
	//!A�{�^��
	A = XINPUT_BUTTON_A,
	//!B�{�^��
	B = XINPUT_BUTTON_B,
	//!X�{�^��
	X = XINPUT_BUTTON_X,
	//!Y�{�^��
	Y = XINPUT_BUTTON_Y,

	// ���͐�
	Max_Of_Num
};

