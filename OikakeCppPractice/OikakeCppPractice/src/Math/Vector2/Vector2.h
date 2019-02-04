#pragma once

/**
 * @file Vector2.h
 * @brief 2�����x�N�g����`�t�@�C��
 * @author ���]
 * @date 2015/10/22
 */

 /*! @class Vector2
 *   @brief  2�����x�N�g��
 */
class Vector2 {
public:	
	/// <summary>
	/// �f�t�H���g�R���X�g���N�^
	/// </summary>
	Vector2();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	Vector2(float x, float y);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="vector">�Q�����x�N�g��</param>
	Vector2(const Vector2& vector);	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Vector2();

	/// <summary>
	/// �x�N�g���̒������擾
	/// </summary>
	/// <returns>
	/// �x�N�g���̒���
	/// </returns>
	float Length() const;

	/// <summary>
	/// �x�N�g����2��̒������擾
	/// </summary>
	/// <returns>
	/// �x�N�g����2��̒���
	/// </returns>
	float SquareLength() const;

	/// <summary>
	/// �x�N�g���𐳋K��(�����P��)����
	/// </summary>
	void Normalize();

	/// <summary>
	/// ���K��(�����P��)�����x�N�g�����擾
	/// </summary>
	/// <returns>
	/// ���K�����ꂽ�x�N�g��
	/// </returns>
	Vector2 GetNormal() const;

	/// <summary>
	/// X��Y�̗v�f���R���\�[����ʂɕ\��
	/// </summary>
	void Print() const;

public:
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="vector">�x�N�g��</param>
	/// <returns>�X�J���[</returns>
	float Dot(const Vector2& vector);

	/// <summary>
	/// �O��
	/// </summary>
	/// <param name="vector">�x�N�g��</param>
	/// <returns>�X�J���[</returns>
	float Cross(const Vector2& vector);

	/// <summary>
	/// �Q�_�Ԃ̋��������߂�
	/// </summary>
	/// <param name="vector">�x�N�g��</param>
	/// <returns>2�_�Ԃ̋���</returns>
	float Distance(const Vector2& vector);

	/// <summary>
	/// �x�N�g����͈͓��Ɏ��߂�
	/// </summary>
	/// <param name="min">���߂�͈͂̍ŏ��̃x�N�g��</param>
	/// <param name="max">���߂�͈͂̍ő�̃x�N�g��</param>
	bool Clamp(const Vector2& min, const Vector2& max);

	/// <summary>
	/// 2�̃x�N�g���̊p�x�����߂�
	/// </summary>
	/// <param name="vec">vec</param>
	/// <returns>
	/// 2�̃x�N�g���̊p�x(�x)
	/// </returns>
	float Angle(const Vector2& vector);

	/// <summary>
	/// 2�̃x�N�g���̐��`���
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="lerpTime">�l(0.0f�`1.0f)</param>
	/// <returns>
	/// ��Ԃ��ꂽ�x�N�g��
	/// </returns>
	Vector2 Lerp(const Vector2& vector, float lerpTime);

	/// <summary>
	/// ���_�𒆐S�ɉ�]����x�N�g�������߂�
	/// </summary>
	/// <param name="angle">�p�x�F�x���@</param>
	/// <returns>���_�𒆐S�ɉ�]�����x�N�g��</returns>
	Vector2 Rotate(float angle);

public:
	//!X�v�f
	float x;
	//!Y�v�f
	float y;

public:
	Vector2 operator + ();
	Vector2 operator - ();
	Vector2 operator + (const Vector2& vector) const;
	Vector2 operator - (const Vector2& vector) const;
	Vector2 operator * (float scalar) const;
	Vector2 operator / (float scalar) const;
	Vector2& operator += (const Vector2& vector);
	Vector2& operator -= (const Vector2& vector);
	Vector2& operator *= (float scalar);
	Vector2& operator /= (float scalar);

public:
	//! Vector2( 0,  1)
	static const Vector2 Up;			
	//! Vector2( 0, -1)
	static const Vector2 Down;			
	//! Vector2(-1,  0)
	static const Vector2 Left;			
	//! Vector2( 1,  0)
	static const Vector2 Right;			
	//! Vector2( 1,  0)
	static const Vector2 UnitX;			
	//! Vector2( 0,  1)
	static const Vector2 UnitY;			
	//! Vector2( 1,  1)
	static const Vector2 One;			
	//! Vector2( 0,  0)
	static const Vector2 Zero;			
};
