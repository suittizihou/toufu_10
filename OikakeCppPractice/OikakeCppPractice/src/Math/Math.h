#pragma once

#include<cmath>

/**
 * @file Math.h
 * @brief �W�����C�u�����̐��w�֐������b�s���O�����N���X��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

/*! @class Math
 *   @brief  �W�����C�u�����̐��w�֐������b�s���O�����N���X
 */
class Math {
public:
	/// <summary>
	/// ��捪�i���[�g�j�����߂�
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns>���[�g�̒l</returns>
	static float SquareRoot(float value);

	/// <summary>�������l�����߂�</summary>
	/// <param name="value1">�l</param>
	/// <param name="value2">�l</param>
	/// <returns>�ŏ��̒l</returns>
	template<typename T = float>
	static T Min(T value1, T value2) {
		return (T)std::fminf(value1, value2);
	}

	/// <summary>�傫���l�����߂�@</summary>
	/// <param name="value1">�l</param>
	/// <param name="value2">�l</param>
	/// <returns>�ő�̒l</returns>
	template<typename T = float>
	static T Max(T value1, T value2) {
		return (T)std::fmaxf(value1, value2);
	}

	/// <summary>�l��͈͓��Ɏ��߂�@</summary>
	/// <param name="value">�l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�͈͓��̒l</returns>
	template<typename T = float>
	static T Clamp(T value, T min, T max) {
		return (T)std::fmaxf(min, (T)std::fminf(value, max));
	}

	/// <summary> �O�p�֐��̃T�C�������߂�@</summary>
	/// <param name="angle">�p�x(�x)</param>
	/// <returns>�T�C���l(-1.0f�`1.0f)</returns>
	static float Sin(float angle);

	/// <summary>�O�p�֐��̃R�T�C�������߂�@</summary>
	/// <param name="angle">�p�x(�x)</param>
	/// <returns>�R�T�C���l(-1.0f�`1.0f)</returns>
	static float Cos(float angle);

	/// <summary> �O�p�֐��̃^���W�F���g�����߂�@</summary>
	/// <param name="angle">�p�x(�x)</param>
	/// <returns>�^���W�F���g�l(-1.0f�`1.0f)</returns>
	static float Tan(float angle);

	/// <summary>�O�p�֐��̃A�[�N�T�C�������߂�@</summary>
	/// <param name="sin">�T�C���l(-1.0f�`1.0f)</param>
	/// <returns>�p�x(�x)</returns>
	static float ArcSin(float sin);

	/// <summary> �O�p�֐��̃A�[�N�R�T�C�������߂�@</summary>
	/// <param name="cos">�R�T�C���l(-1.0f�`1.0f)</param>
	/// <returns>�p�x(�x)</returns>
	static float ArcCos(float cos);

	/// <summary> �O�p�֐��̃A�[�N�^���W�F���g�����߂�@</summary>
	/// <param name="tan">�^���W�F���g�l(-1.0f�`1.0f)</param>
	/// <returns>�p�x(�x)</returns>
	static float ArcTan(float y, float x);
	/// <summary> �O�p�֐��̃A�[�N�^���W�F���g�����߂�@</summary>
	/// <param name="tan">�^���W�F���g�l(-1.0f�`1.0f)</param>
	/// <returns>�p�x(�x)</returns>
	static float ArcTan(float tan);

	/// <summary>
	/// ��Βl���擾
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns>��Βl</returns>
	template<typename T = float>
	static T Abs(T value) {
		return (T)abs(value);
	}

	
	/// <summary>
	/// �l���Ԃ���
	/// </summary>
	/// <param name="value1">value1</param>
	/// <param name="value2">value2</param>
	/// <param name="amount">��Ԓl</param>
	/// <returns>amount�ŕ�Ԃ��ꂽ�l</returns>
	template<typename T = float>
	static T Lerp(T value1, T value2, float amount) {
		return (value1 * (1.0f - amount)) + (value2 * amount);
	}

	/// <summary>
	/// �l�̕������擾����
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns>�����i1 or -1�j</returns>
	template<typename T = float>
	static int Sign(T value) {
		return static_cast<int>((value / Math::Abs<float>(value)));
	}

public:
	//!�~����(��)
	static const float PI;
	//!�x���@�ɕϊ�
	static const float toDegree;
	//!���W�A���p�ɕϊ�
	static const float toRadian;
	//!臒l
	static const float Epsilon;
};
