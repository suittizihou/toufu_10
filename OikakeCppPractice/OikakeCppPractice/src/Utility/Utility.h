#pragma once

/**
 * @file Utility.h
 * @brief �ėp�I�Ȋ֐����܂Ƃ߂��N���X
 * @author ���]
 * @date 2016/8/14
 */

#include"Math/Convert/Convert.h"
#include"Math/MathType.h"
#include<string>

 /*! @class Utility
 *   @brief �ėp�I�Ȋ֐����܂Ƃ߂��N���X
 */
class Utility {
public:
	//!�|�b�v�A�b�v����UI�̍��W�̃I�t�Z�b�g�l
	static const Vector2 PopupUIPositionOffset;
	//!�R���g���[���[�̃o�C�u���[�V�����̋���
	static const float VibrationPower;
	//!�R���g���[���[�̃o�C�u���[�V�����̎���
	static const float VibrationTime;
	//!UI�̓_�ł̎��̍ŏ��̃A���t�@�l
	static const float MinAlpha;
	//!UI�̓_�ł̎��̑�����l
	static const float DeltaAlpha;
	//!�e���[�h���S���̗̑�
	static const int Dragon_HitPoint;
	//!�e���[�h���S���̂Ђ�ݒl
	static const int Dragon_StaggerPoint;

public:	
	/// <summary>
	/// ���l�𕶎���ɕϊ�����
	/// </summary>
	/// <param name="value">�ϊ����������l</param>
	/// <returns>�ϊ�����������</returns>
	template<typename T>
	static std::string ToString(const T& value) {
		return std::to_string(value);
	}

	 /// <summary>
	 /// ���[���h���W���X�N���[�����W�ɕϊ�����
	 /// </summary>
	 /// <param name="worldPosition">���[���h���W</param>
	 /// <returns>�X�N���[�����W</returns>
	static Vector2 WorldPosToScreenPos(const Vector3& worldPosition) {
		VECTOR screenPosision = ConvWorldPosToScreenPos(Convert::ToVECTOR(worldPosition));
		return Convert::ToVector2(screenPosision);
	}
	 /// <summary>
	 /// ��ʏ��3�������W��\������@�f�o�b�N�p
	 /// </summary>
	 /// <param name="position">���W</param>
	static void PrintDxVector(const Vector3& position) {
		printfDx("X = %0.2f, Y = %0.2f, Z = %0.2f\n", position.x, position.y, position.z);
	}
	/// <summary>
	/// ������3D��ԏ�ɕ`��
	/// </summary>
	/// <param name="start">�n�_</param>
	/// <param name="end">�I�_</param>
	static void DrawLine(const Vector3& start, const Vector3& end) {
		DrawLine3D(Convert::ToVECTOR(start), Convert::ToVECTOR(end), GetColor(0, 0, 255));
	}
};
