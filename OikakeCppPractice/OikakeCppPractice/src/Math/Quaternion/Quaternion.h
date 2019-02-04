#pragma once

class Vector3;
class Matrix4;

/**
 * @file Quaternion.h
 * @brief �N�H�[�^�j�I����`�t�@�C��
 * @author ���]
 * @date Unknown
 */

 /*! @class Quaternion
 *   @brief  �N�H�[�^�j�I��
 */
class Quaternion {
public:	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">x�v�f</param>
	/// <param name="y">y�v�f</param>
	/// <param name="z">z�v�f</param>
	/// <param name="w">w�v�f</param>
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="axis">��]�̊�ɂ��鎲</param>
	/// <param name="angle">��]�p�x�F�x���@</param>
	Quaternion(const Vector3& axis, float angle);	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m">�s��</param>
	explicit Quaternion(const Matrix4& m);	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Quaternion();	
	/// <summary>
	/// ���K������
	/// </summary>
	/// <returns>���K�������N�H�[�^�j�I��</returns>
	Quaternion& Normalize();	
	/// <summary>
	/// ���K������
	/// </summary>
	/// <returns>���K�������N�H�[�^�j�I��</returns>
	Quaternion GetNormal();	
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="q">�N�H�[�^�j�I��</param>
	/// <returns>�X�J���[</returns>
	float Dot(const Quaternion& q);	
	/// <summary>
	/// �������擾
	/// </summary>
	/// <returns>����</returns>
	float Length();	
	/// <summary>
	/// ���ʐ��`��Ԃ�����
	/// </summary>
	/// <param name="q">�N�H�[�^�j�I��</param>
	/// <param name="amount">��</param>
	/// <returns>���ʐ��`��Ԃ������N�H�[�^�j�I��</returns>
	Quaternion Slerp(const Quaternion& q, float amount);	
	/// <summary>
	/// ��]�s����擾����
	/// </summary>
	/// <returns>��]�s��</returns>
	Matrix4 ToRotateMatrix();	
	/// <summary>
	/// ��]�s����N�H�[�^�j�I���ɕϊ�����
	/// </summary>
	/// <param name="m">��]�s��</param>
	/// <returns>�N�H�[�^�j�I��</returns>
	Quaternion CreateFromRotationMatrix(const Matrix4& m);

public:
	Quaternion operator - ();
	Quaternion& operator += (const Quaternion& q);
	Quaternion& operator -= (const Quaternion& q);
	Quaternion& operator *= (float scalar);
	Quaternion& operator *= (const Quaternion& q);
	Quaternion& operator /= (float scalar);
	Quaternion operator + (const Quaternion& q);
	Quaternion operator - (const Quaternion& q);
	Quaternion operator * (const Quaternion& q);
	Quaternion operator * (float scalar);
	Quaternion operator / (float scalar);

private:	
	/// <summary>
	/// �N�H�[�^�j�I�����m�|���Z������
	/// </summary>
	/// <param name="q1">�N�H�[�^�j�I��</param>
	/// <param name="q2">�N�H�[�^�j�I��</param>
	/// <returns>�|���Z�����N�H�[�^�j�I��</returns>
	Quaternion Mul(const Quaternion& q1, const Quaternion& q2);

public:
	//!X�v�f
	float x;
	//!Y�v�f
	float y;
	//!Z�v�f
	float z;
	//!W�v�f
	float w;
};

inline Quaternion operator * (float scalar, const Quaternion& q) {
	return Quaternion(q.x * scalar, q.y * scalar, q.z * scalar, q.w * scalar);
}