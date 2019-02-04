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
	/// �Q�[���p�b�h�̃{�^���������ꂽ���H
	/// </summary>
	/// <param name="button">�Q�[���p�b�h�̃{�^��</param>
	/// <returns>
	/// �����ꂽ�ꍇ�͐^
	/// </returns>
	bool IsButtonUp(XboxGamePad button)const;
	/// <summary>
	/// �Q�[���p�b�h�̃{�^���������ꂽ���H
	/// </summary>
	/// <param name="button">�Q�[���p�b�h�̃{�^��</param>
	/// <returns>
	/// �����ꂽ�ꍇ�͐^
	/// </returns>
	bool IsButtonDown(XboxGamePad button)const;
	bool IsButtonDown2(XboxGamePad button)const;
	/// <summary>
	/// �Q�[���p�b�h�̃{�^���������ꑱ���Ă��邩�H
	/// </summary>
	/// <param name="button">�Q�[���p�b�h�̃{�^��</param>
	/// <returns>
	/// �����ꑱ���Ă���ꍇ�͐^
	/// </returns>
	bool IsButtonState(XboxGamePad button)const;
	bool IsButtonState2(XboxGamePad button)const;

	/// <summary>
	/// ���g���K�[�̉��������擾(0�`1.0f)
	/// </summary>
	/// <returns>������</returns>
	float GetLeftTrigger()const;
	/// <summary>
	/// �E�g���K�[�̉��������擾(0�`1.0f)
	/// </summary>
	/// <returns>������</returns>
	float GetRightTrigger()const;
	/// <summary>
	/// ���X�e�B�b�N�̓��͒l���擾����
	/// </summary>
	/// <returns>���X�e�B�b�N�̓��͒l</returns>
	Vector2 GetLeftStick()const;
	/// <summary>
	/// �E�X�e�B�b�N�̓��͒l���擾����
	/// </summary>
	/// <returns>�E�X�e�B�b�N�̓��͒l</returns>
	Vector2 GetRightStick()const;
	/// <summary>
	/// �Q�[���p�b�h�̐U�����J�n����
	/// </summary>
	/// <param name="player">�U������Q�[���p�b�h</param>
	/// <param name="vibrationPower">�U���̋���(0�`1000)</param>
	/// <param name="vibrationTime">�U�������鎞��(�~���b)�@-1�Ȃ��~����܂ŐU������</param>
	void VibrationStart(GamePad player, int vibrationPower, int vibrationTime = -1);
	/// <summary>
	/// �Q�[���p�b�h�̐U�����~����
	/// </summary>
	/// <param name="player">�U�����~����Q�[���p�b�h</param>
	void VibrationStop(GamePad player);
	/// <summary>
	/// DPad�̓��͒l���擾����
	/// </summary>
	/// <returns>DPad�̓��͒l</returns>
	Vector2 GetDPadValue() const;

	Vector2 GetVelocity() const;

	bool IsAnyButtonDown() const;

private:
	//!�Q�[���p�b�h�̌��݂̓��͏󋵂�ۑ�
	XINPUT_STATE curXinput;
	XINPUT_STATE curXinput2;
	//!�Q�[���p�b�h�̂P�t���[���̓��͏󋵂�ۑ�
	XINPUT_STATE preXinput;
	XINPUT_STATE preXinput2;
	//!1�t���[���O�̃R���g���[���[�̃X�e�B�b�N����
	Vector2 prevInput;
	//!���݂̃R���g���[���[�̃X�e�B�b�N����
	Vector2 curInput;
};