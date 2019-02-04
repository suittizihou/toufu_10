#include "XBoxController.h"
#include "Math/Math.h"
#include<iostream>

XBoxController::XBoxController()
	: curXinput()
	, curXinput2()
	, preXinput()
	, preXinput2()
	, prevInput()
	, curInput()
{
}

XBoxController::~XBoxController()
{
}

void XBoxController::Update()
{
	//更新する前に　１フレーム前の状態を保存
	std::memcpy(preXinput.Buttons, curXinput.Buttons, sizeof(char) * MaxXboxButtonNum);
	std::memcpy(preXinput2.Buttons, curXinput2.Buttons, sizeof(char) * MaxXboxButtonNum);

	//TODO:ここ１Pコン固定　対戦ゲームならここ改良すべき
	GetJoypadXInputState(DX_INPUT_PAD1, &curXinput);
	GetJoypadXInputState(DX_INPUT_PAD2, &curXinput2);
}

bool XBoxController::IsConnect() const
{
	//1台以上接続されていたらtrue
	return (GetJoypadNum() != 0);
}

bool XBoxController::IsButtonUp(XboxGamePad button) const
{
	int index = static_cast<int>(button);
	return (!curXinput.Buttons[index] && preXinput.Buttons[index]);
}

bool XBoxController::IsButtonDown(XboxGamePad button) const
{
	int index = static_cast<int>(button);
	return (curXinput.Buttons[index] && !preXinput.Buttons[index]);
}
bool XBoxController::IsButtonDown2(XboxGamePad button) const
{
	int index = static_cast<int>(button);
	return (curXinput2.Buttons[index] && !preXinput2.Buttons[index]);
}

bool XBoxController::IsButtonState(XboxGamePad button) const
{
	static const int HoldPushButton = 1;
	int index = static_cast<int>(button);
	return curXinput.Buttons[index] == HoldPushButton;
}
bool XBoxController::IsButtonState2(XboxGamePad button) const
{
	static const int HoldPushButton = 1;
	int index = static_cast<int>(button);
	return curXinput2.Buttons[index] == HoldPushButton;
}

float XBoxController::GetLeftTrigger() const
{
	return static_cast<float>(curXinput.LeftTrigger) / 255.0f;
}

float XBoxController::GetRightTrigger() const
{
	return static_cast<float>(curXinput.RightTrigger) / 255.0f;
}

Vector2 XBoxController::GetLeftStick() const
{
	//TODO:見直し
	float x = curXinput.ThumbLX / 10000.0f;
	float y = curXinput.ThumbLY / 10000.0f;
	float x_ = x / 3.28f;
	float y_ = y / 3.28f;

	x = (Math::Abs(x_) < 0.3f) ? 0.0f : x_;
	y = (Math::Abs(y_) < 0.3f) ? 0.0f : y_;

	return Vector2(x, y);
}

Vector2 XBoxController::GetRightStick() const
{
	float x = curXinput.ThumbRX / 10000.0f;
	float y = curXinput.ThumbRY / 10000.0f;
	float x_ = x / 3.28f;
	float y_ = y / 3.28f;

	x = (Math::Abs(x_) < 0.3f) ? 0.0f : x_;
	y = (Math::Abs(y_) < 0.3f) ? 0.0f : y_;
	return Vector2(x, y);
}

void XBoxController::VibrationStart(GamePad player, int vibrationPower, int vibrationTime)
{
	StartJoypadVibration(static_cast<int>(player), vibrationPower, vibrationTime);
}

void XBoxController::VibrationStop(GamePad player)
{
	StopJoypadVibration(static_cast<int>(player));
}

Vector2 XBoxController::GetDPadValue() const
{
	Vector2 value;
	if (IsButtonState(XboxGamePad::Dpad_Up)) {
		value.y = 1.0f;
	}
	if (IsButtonState(XboxGamePad::Dpad_Down)) {
		value.y = -1.0f;
	}
	if (IsButtonState(XboxGamePad::Dpad_Left)) {
		value.x = -1.0f;
	}
	if (IsButtonState(XboxGamePad::Dpad_Right)) {
		value.x = 1.0f;
	}
	return value;
}

Vector2 XBoxController::GetVelocity() const
{
	Vector2 stick = GetLeftStick();
	if (stick.SquareLength() <= 0.1f) {
		return GetDPadValue();
	}
	return stick;
}

bool XBoxController::IsAnyButtonDown() const
{
	for (int i = 0; i < static_cast<int>(XboxGamePad::Max_Of_Num); i++) {
		if (IsButtonDown(static_cast<XboxGamePad>(i))) return true;
	}
	return false;
}

