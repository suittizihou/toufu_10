#pragma once

class Matrix4;

/**
 * @file Vector3.h
 * @brief �R�����x�N�g����`�t�@�C��
 * @author ���]
 * @date Unknown
 */

/*! @class Vector3
 *   @brief  �R�����x�N�g��
 */
class Vector3 {
public:	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <param name="z">z���W</param>
	Vector3(float x, float y, float z);	
	/// <summary>
	///�R���X�g���N�^
	/// </summary>
	/// <param name="vector">3�����x�N�g��</param>
	Vector3(const Vector3& vector);	
	/// <summary>
	/// �f�t�H���g�R���X�g���N�^
	/// </summary>
	Vector3();	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Vector3();

	/// <summary>
	/// ���K��
	/// </summary>
	void Normalize();
	/// <summary>
	/// �@���x�N�g�����擾
	/// </summary>
	/// <returns>�@���x�N�g��</returns>
	Vector3 GetNormal() const;
	/// <summary>
	/// �x�N�g���̒������擾
	/// </summary>
	/// <returns>�x�N�g���̒���</returns>
	float Length()const;
	/// <summary>
	/// �x�N�g���̒�����2��̒l���擾
	/// </summary>
	/// <returns>�x�N�g���̒�����2��̒l</returns>
	float SquareLength() const;
	/// <summary>
	/// �R���\�[����ʂɏo��
	/// </summary>
	void Print();


	/// <summary>
	/// �x�N�g����͈͓��Ɏ��߂�
	/// </summary>
	/// <param name="min">���߂�͈͂̍ŏ��̃x�N�g��</param>
	/// <param name="max">���߂�͈͂̍ő�̃x�N�g��</param>
	void Clamp(const Vector3& min, const Vector3& max);

	/// <summary>
	/// �Q�_�Ԃ̋��������߂�
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <returns>
	/// �Q�_�Ԃ̋���
	/// </returns>
	float Distance(const Vector3& vec) const;
	
	/// <summary>
	/// �Q�_�Ԃ̋����́@���@�����߂�
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <returns>
	/// �Q�_�Ԃ̋����́@���
	/// </returns>
	float DistanceSquare(const Vector3& vec) const;

	/// <summary>
	/// 2�̃x�N�g���̊p�x�����߂�
	/// </summary>
	/// <param name="vec">vec</param>
	/// <returns>
	/// 2�̃x�N�g���̊p�x(�x)
	/// </returns>
	float Angle(const Vector3& vec) const;

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <returns>
	/// �X�J���[
	/// </returns>
	float Dot(const Vector3& vec) const;
	/// <summary>
	/// �O��
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <returns>
	/// �x�N�g��
	/// </returns>
	Vector3 Cross(const Vector3& vec);

	/// <summary>
	/// 2�̃x�N�g���̐��`���
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="lerpTime">�l(0.0f�`1.0f)</param>
	/// <returns>
	/// ��Ԃ��ꂽ�x�N�g��
	/// </returns>
	Vector3 Lerp(const Vector3& vec, float lerpTime);

	
	/// <summary>
	/// ���W�ϊ�
	/// </summary>
	/// <param name="matrix">���W�ϊ�������s��</param>
	/// <returns>
	/// ���W�ϊ������x�N�g��
	/// </returns>
	Vector3 Transform(const Matrix4& matrix);
	/// <summary>
	/// ��]�s��ŕϊ�����
	/// </summary>
	/// <param name="matrix">�ϊ�������s��</param>
	/// <returns>
	/// ��]�s��ŕϊ������x�N�g��
	/// </returns>
	Vector3 TransformNormal(const Matrix4& matrix) const;
	/// <summary>
	/// ���[�E�s�b�`����x�N�g�����쐬
	/// </summary>
	/// <param name="yaw">���[(Z����])�F�x���@</param>
	/// <param name="pitch">�s�b�`(Y����])�F�x���@</param>
	/// <returns>
	/// ���[�E�s�b�`������ꂽ�x�N�g��
	/// </returns>
	static Vector3 CreateFromYawPitch(float yaw, float pitch);
	
	/// <summary>
	/// �x�N�g������s�b�`���擾�iY����]�j
	/// </summary>
	/// <returns>
	/// Y���̉�]�p�x�F�x���@
	/// </returns>
	float Pitch()const;

	/// <summary>
	/// �x�N�g�����烈�[���擾�iZ����]�j
	/// </summary>
	/// <returns>
	/// Z���̉�]�p�x�F�x���@
	/// </returns>
	float Yaw() const;

public:
	//!X���W
	float x;
	//!Y���W
	float y;
	//!Z���W
	float z;

public:	
	Vector3 operator + ();
	Vector3 operator - ();
	Vector3 operator + (const Vector3& vector) const;
	Vector3 operator - (const Vector3& vector) const;
	Vector3 operator * (float scalar) const;
	Vector3 operator / (float scalar) const;
	Vector3& operator += (const Vector3& vector);
	Vector3& operator -= (const Vector3& vector);
	Vector3& operator *= (float scalar);
	Vector3& operator /= (float scalar);

public:
	//! Vector3( 0,  1,  0)
	static const Vector3 Up;			
	//! Vector3( 0, -1,  0)
	static const Vector3 Down;			
	//! Vector3(-1,  0,  0)
	static const Vector3 Left;			
	//! Vector3( 1,  0,  0)
	static const Vector3 Right;		
	//! Vector3( 0,  0, -1)
	static const Vector3 Backward;		
	//! Vector3( 0,  0,  1)
	static const Vector3 Forward;		
	//! Vector3( 1,  0,  0)
	static const Vector3 UnitX;		
	//! Vector3( 0,  1,  0)
	static const Vector3 UnitY;			
	//! Vector3( 0,  1,  1)
	static const Vector3 UnitZ;		
	//! Vector3( 1,  1,  1)
	static const Vector3 One;			
	//! Vector3( 0,  0,  0)
	static const Vector3 Zero;			
};
// scalar * vector ���`
inline Vector3 operator*(float scalar, const Vector3 & vector)
{
	return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}
