#pragma once

#include<DxLib.h>
#include<array>

class KeyBoard {
public:
	KeyBoard();
	~KeyBoard();

	void Update();

	/// <summary>
	/// キーボード のキーが離されたかどうか判定
	/// </summary>
	/// <param name="key">キーボード のキー</param>
	/// <returns>
	/// 離された場合は真
	/// </returns>
	bool IsUp(int key) const;
	/// <summary>
	/// キーボード のキーが押されたかどうか判定
	/// </summary>
	/// <param name="key">キーボード のキー</param>
	/// <returns>
	/// 押された場合は真
	/// </returns>
	bool IsDown(int key)const;
	/// <summary>
	/// キーボード のキーが押され続けているどうか判定
	/// </summary>
	/// <param name="key">キーボード のキー</param>
	/// <returns>
	/// 押され続けていた場合は真
	/// </returns>
	bool IsState(int key)const;

	bool IsAnyKeyDown() const;

private:

	//!最大キー数
	static const int Max_Key_Num = 256;

	//!キーが押されたかを格納する配列
	using Keys = std::array<char, Max_Key_Num>;

	//!キーの現在の押下状況保存
	Keys curKeys;
	//!キーの1フレーム前の押下状況保存
	Keys preKeys;

};