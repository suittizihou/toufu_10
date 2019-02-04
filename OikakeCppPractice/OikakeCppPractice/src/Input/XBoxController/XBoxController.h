#pragma once

#include"../GamePad.h"
#include"Math/Vector2/Vector2.h"
#include<vector>
#include<DxLib.h>
class Vector3;

class XBoxController {
public:
	XBoxController();
	~XBoxController();

	void Update();

	bool IsConnect() const;
	/// <summary>
	/// ゲームパッドのボタンが離されたか？
	/// </summary>
	/// <param name="button">ゲームパッドのボタン</param>
	/// <returns>
	/// 離された場合は真
	/// </returns>
	bool IsButtonUp(XboxGamePad button)const;
	/// <summary>
	/// ゲームパッドのボタンが押されたか？
	/// </summary>
	/// <param name="button">ゲームパッドのボタン</param>
	/// <returns>
	/// 押された場合は真
	/// </returns>
	bool IsButtonDown(XboxGamePad button)const;
	bool IsButtonDown2(XboxGamePad button)const;
	/// <summary>
	/// ゲームパッドのボタンが押され続けているか？
	/// </summary>
	/// <param name="button">ゲームパッドのボタン</param>
	/// <returns>
	/// 押され続けている場合は真
	/// </returns>
	bool IsButtonState(XboxGamePad button)const;
	bool IsButtonState2(XboxGamePad button)const;

	/// <summary>
	/// 左トリガーの押され具合を取得(0～1.0f)
	/// </summary>
	/// <returns>押され具合</returns>
	float GetLeftTrigger()const;
	/// <summary>
	/// 右トリガーの押され具合を取得(0～1.0f)
	/// </summary>
	/// <returns>押され具合</returns>
	float GetRightTrigger()const;
	/// <summary>
	/// 左スティックの入力値を取得する
	/// </summary>
	/// <returns>左スティックの入力値</returns>
	Vector2 GetLeftStick()const;
	/// <summary>
	/// 右スティックの入力値を取得する
	/// </summary>
	/// <returns>右スティックの入力値</returns>
	Vector2 GetRightStick()const;
	/// <summary>
	/// ゲームパッドの振動を開始する
	/// </summary>
	/// <param name="player">振動するゲームパッド</param>
	/// <param name="vibrationPower">振動の強さ(0～1000)</param>
	/// <param name="vibrationTime">振動させる時間(ミリ秒)　-1なら停止するまで振動する</param>
	void VibrationStart(GamePad player, int vibrationPower, int vibrationTime = -1);
	/// <summary>
	/// ゲームパッドの振動を停止する
	/// </summary>
	/// <param name="player">振動を停止するゲームパッド</param>
	void VibrationStop(GamePad player);
	/// <summary>
	/// DPadの入力値を取得する
	/// </summary>
	/// <returns>DPadの入力値</returns>
	Vector2 GetDPadValue() const;

	Vector2 GetVelocity() const;

	bool IsAnyButtonDown() const;

private:
	//!ゲームパッドの現在の入力状況を保存
	XINPUT_STATE curXinput;
	XINPUT_STATE curXinput2;
	//!ゲームパッドの１フレームの入力状況を保存
	XINPUT_STATE preXinput;
	XINPUT_STATE preXinput2;
	//!1フレーム前のコントローラーのスティック入力
	Vector2 prevInput;
	//!現在のコントローラーのスティック入力
	Vector2 curInput;
};