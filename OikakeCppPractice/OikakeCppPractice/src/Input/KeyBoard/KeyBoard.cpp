#include "KeyBoard.h"

KeyBoard::KeyBoard()
{
	//キーが押されたかどうかを格納する配列を初期化
	//押されていない　ニュートラル
	static const int NotPushed = 0;
	curKeys.fill(NotPushed);
	preKeys.fill(NotPushed);
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	//更新する前に　１フレーム前の状態を保存
	preKeys.swap(curKeys);
	//現在のキー情報を更新
	GetHitKeyStateAll(curKeys.data());
}

bool KeyBoard::IsUp(int key) const
{
	return (!curKeys[key] && preKeys[key]);
}

bool KeyBoard::IsDown(int key) const
{
	return (curKeys[key] && !preKeys[key]);
}

bool KeyBoard::IsState(int key) const
{
	static const int HoldPushKey = 1;
	return curKeys[key] == HoldPushKey;
}

bool KeyBoard::IsAnyKeyDown() const
{
	for (int i = 0; i < Max_Key_Num; i++) {
		if (IsDown(i)) return true;
	}
	return false;
}
