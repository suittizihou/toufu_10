#pragma once

/**
 * @file GamePad.h
 * @brief ゲームパッドの定義ヘッダー
 * @author 阿曽
 * @date 2017/2/5
 */

#include<DxLib.h>
//!Xboxコントローラーの最大ボタン数
static const int MaxXboxButtonNum = 16;

/**
 * @enum GamePad
 * ゲームパッドの識別の定義
 */
enum class GamePad {
	//!１Pコン
	Player1 = DX_INPUT_PAD1,
	//!２Pコン
	Player2 = DX_INPUT_PAD2,
	//!３Pコン
	Player3 = DX_INPUT_PAD3,
	//!４Pコン
	Player4 = DX_INPUT_PAD4
};

/**
 * @enum XboxGamePad
 * Xbox360のボタン
 */
enum class XboxGamePad {
	//!デジタル方向ボタン上
	Dpad_Up = XINPUT_BUTTON_DPAD_UP,
	//!デジタル方向ボタン下
	Dpad_Down = XINPUT_BUTTON_DPAD_DOWN,
	//!デジタル方向ボタン左
	Dpad_Left = XINPUT_BUTTON_DPAD_LEFT,
	//!デジタル方向ボタン右
	Dpad_Right = XINPUT_BUTTON_DPAD_RIGHT,
	//!STARTボタン
	Start = XINPUT_BUTTON_START,
	//!BACKボタン
	Back = XINPUT_BUTTON_BACK,
	//!左スティック押し込み
	Left_Thumb = XINPUT_BUTTON_LEFT_THUMB,
	//!右スティック押し込み
	Right_Thumb = XINPUT_BUTTON_RIGHT_THUMB,
	//!LBボタン
	Left_Shoulder = XINPUT_BUTTON_LEFT_SHOULDER,
	//!RBボタン
	Right_Shoulder = XINPUT_BUTTON_RIGHT_SHOULDER,
	//!Aボタン
	A = XINPUT_BUTTON_A,
	//!Bボタン
	B = XINPUT_BUTTON_B,
	//!Xボタン
	X = XINPUT_BUTTON_X,
	//!Yボタン
	Y = XINPUT_BUTTON_Y,

	// 入力数
	Max_Of_Num
};

