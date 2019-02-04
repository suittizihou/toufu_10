#pragma once

#include<DxLib.h>
#include<array>

class KeyBoard {
public:
	KeyBoard();
	~KeyBoard();

	void Update();

	/// <summary>
	/// �L�[�{�[�h �̃L�[�������ꂽ���ǂ�������
	/// </summary>
	/// <param name="key">�L�[�{�[�h �̃L�[</param>
	/// <returns>
	/// �����ꂽ�ꍇ�͐^
	/// </returns>
	bool IsUp(int key) const;
	/// <summary>
	/// �L�[�{�[�h �̃L�[�������ꂽ���ǂ�������
	/// </summary>
	/// <param name="key">�L�[�{�[�h �̃L�[</param>
	/// <returns>
	/// �����ꂽ�ꍇ�͐^
	/// </returns>
	bool IsDown(int key)const;
	/// <summary>
	/// �L�[�{�[�h �̃L�[�������ꑱ���Ă���ǂ�������
	/// </summary>
	/// <param name="key">�L�[�{�[�h �̃L�[</param>
	/// <returns>
	/// �����ꑱ���Ă����ꍇ�͐^
	/// </returns>
	bool IsState(int key)const;

	bool IsAnyKeyDown() const;

private:

	//!�ő�L�[��
	static const int Max_Key_Num = 256;

	//!�L�[�������ꂽ�����i�[����z��
	using Keys = std::array<char, Max_Key_Num>;

	//!�L�[�̌��݂̉����󋵕ۑ�
	Keys curKeys;
	//!�L�[��1�t���[���O�̉����󋵕ۑ�
	Keys preKeys;

};