#pragma once

#include<array>
#include"Math/Vector3/Vector3.h"
#include"Math/Vector2/Vector2.h"
class Quaternion;

/**
 * @file Matrix4.h
 * @brief 4x4�̍s���`�t�@�C��
 * @author ���]
 * @date Unknown
 */

 /*! @class Matrix4
 *   @brief  4x4�̍s��
 */
class Matrix4 {
public:	
	/// <summary>
	/// �f�t�H���g�R���X�g���N�^
	/// </summary>
	Matrix4();	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Matrix4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	explicit Matrix4(const Quaternion& q);	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Matrix4();	
	/// <summary>
	/// �g��k���݂̂̍s��𐶐�
	/// </summary>
	/// <param name="x">x���W�̑傫��</param>
	/// <param name="y">y���W�̑傫��</param>
	/// <param name="z">z���W�̑傫��</param>
	/// <returns>�g��k���݂̂̍s��</returns>
	static Matrix4 Scale(float x, float y, float z);	
	/// <summary>
	/// �g��k���݂̂̍s��𐶐�
	/// </summary>
	/// <param name="scale">�傫���̃x�N�g��</param>
	/// <returns>�g��k���݂̂̍s��</returns>
	static Matrix4 Scale(const Vector3& scale);	
	/// <summary>
	/// ���̍s��ɑ傫����ݒ肷��
	/// </summary>
	/// <param name="x">x���W�̑傫��</param>
	/// <param name="y">y���W�̑傫��</param>
	/// <param name="z">z���W�̑傫��</param>
	/// <returns>�傫����ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetScale(float x, float y, float z);	
	/// <summary>
	/// ���̍s��ɑ傫����ݒ肷��
	/// </summary>
	/// <param name="scale">�傫��</param>
	/// <returns>�傫����ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetScale(const Vector3& scale);	
	/// <summary>
	/// ���̍s��̑傫�����擾
	/// </summary>
	/// <returns>�傫��</returns>
	Vector3 GetScale() const;	
	/// <summary>
	/// ���s�ړ��݂̂̍s��𐶐�
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <param name="z">z���W</param>
	/// <returns>���s�ړ��݂̂̍s��</returns>
	static Matrix4 Translate(float x, float y, float z);	
	/// <summary>
	/// ���s�ړ��݂̂̍s��𐶐�
	/// </summary>
	/// <param name="translate">�ړ���</param>
	/// <returns>���s�ړ��݂̂̍s��</returns>
	static Matrix4 Translate(const Vector3& translate);	
	/// <summary>
	/// ���̍s��ɍ��W��ݒ肷��
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <param name="z">z���W</param>
	/// <returns>���W��ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetPosition(float x, float y, float z);	
	/// <summary>
	/// ���̍s��ɍ��W��ݒ肷��
	/// </summary>
	/// <param name="position">���W</param>
	/// <returns>���W��ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetPosition(const Vector3& position);	
	/// <summary>
	/// ���̍s��̍��W���擾
	/// </summary>
	/// <returns>���̍s��̍��W</returns>
	Vector3 GetPosition() const;	
	/// <summary>
	/// X����]�݂̂̍s��𐶐�
	/// </summary>
	/// <param name="angle">��]�p�x�F�x���@</param>
	/// <returns>X����]�݂̂̍s��</returns>
	static Matrix4 RotateX(float angle);
	/// <summary>
	/// Y����]�݂̂̍s��𐶐�
	/// </summary>
	/// <param name="angle">��]�p�x�F�x���@</param>
	/// <returns>Y����]�݂̂̍s��</returns>
	static Matrix4 RotateY(float angle);
	/// <summary>
	/// Z����]�݂̂̍s��𐶐�
	/// </summary>
	/// <param name="angle">��]�p�x�F�x���@</param>
	/// <returns>Z����]�݂̂̍s��</returns>
	static Matrix4 RotateZ(float angle);	
	/// <summary>
	/// ���̍s���X����]�̊p�x��ݒ肷��
	/// </summary>
	/// <param name="angle">�p�x�F�x���@</param>
	/// <returns>X����]�̊p�x��ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetRotateX(float angle);
	/// <summary>
	/// ���̍s���Y����]�̊p�x��ݒ肷��
	/// </summary>
	/// <param name="angle">�p�x�F�x���@</param>
	/// <returns>Y����]�̊p�x��ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetRotateY(float angle);
	/// <summary>
	/// ���̍s���Z����]�̊p�x��ݒ肷��
	/// </summary>
	/// <param name="angle">�p�x�F�x���@</param>
	/// <returns>Z����]�̊p�x��ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetRotateZ(float angle);	
	/// <summary>
	/// ���̍s�񂩂�N�H�[�^�j�I���𐶐�����
	/// </summary>
	/// <returns>�N�H�[�^�j�I��</returns>
	Quaternion GetRotation() const;	
	/// <summary>
	/// ���̍s�񂩂��]�s����擾����
	/// </summary>
	/// <returns>��]�s��</returns>
	Matrix4 GetRotationMatrix() const;	
	/// <summary>
	/// XYZ���̉�]�ʂ����W�A���p�Ŏ擾����
	/// </summary>
	/// <returns>XYZ���̉�]��</returns>
	Vector3 GetRotateAngle_Radian() const;
	/// <summary>
	/// XYZ���̉�]�ʂ�x���@�Ŏ擾����
	/// </summary>
	/// <returns>XYZ���̉�]��</returns>
	Vector3 GetRotateAngle_Degree() const;	
	/// <summary>
	/// �p���s��𐶐�����
	/// </summary>
	/// <param name="scale">�傫��</param>
	/// <param name="rotate">��]</param>
	/// <param name="translate">���s�ړ�</param>
	/// <returns>�p���s��</returns>
	static Matrix4 CreateWorld(const Vector3& scale, const Quaternion& rotate, const Vector3& translate);
	/// <summary>
	/// �p���s��𐶐�����
	/// </summary>
	/// <param name="scale">�傫��</param>
	/// <param name="rotate">��]</param>
	/// <param name="translate">���s�ړ�</param>
	/// <returns>�p���s��</returns>
	static Matrix4 CreateWorld(const Vector3& scale, const Matrix4& rotate, const Vector3& translate);
	/// <summary>�ݒ肳�ꂽ�O�����������s����쐬</summary>
	/// <param name="position">���W</param>
	/// <param name="forward">�O����</param>
	/// <param name="up">�����</param>
	static Matrix4 CreateLookAt(const Vector3& position, const Vector3& forward, const Vector3& up);	
	/// <summary>
	/// �������e�s��𐶐�
	/// </summary>
	/// <param name="fov">����p</param>
	/// <param name="aspect">�A�X�y�N�g��</param>
	/// <param name="near_">�߃N���b�v</param>
	/// <param name="far_">���N���b�v</param>
	/// <returns>�������e�s��</returns>
	static Matrix4 CreatePerspective(float fov, float aspect, float near_, float far_);	
	/// <summary>
	/// �J�����s��𐶐�
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="target">�����_</param>
	/// <param name="up">�J�����̏����</param>
	/// <returns>�J�����s��</returns>
	static Matrix4 CreateView(const Vector3& position, const Vector3& target, const Vector3& up);	
	/// <summary>
	/// ��]�s��𐶐�����
	/// </summary>
	/// <param name="axis">��]���鎲</param>
	/// <param name="angle">�p�x�F�x���@</param>
	/// <returns>��]�s��</returns>
	static Matrix4 CreateFromAxisAngle(const Vector3& axis, float angle);	
	/// <summary>
	/// ��]�s��𐶐�����
	/// </summary>
	/// <param name="rotate">�N�H�[�^�j�I��</param>
	/// <returns>��]�s��</returns>
	static Matrix4 CreateFromQuaternion(const Quaternion& rotate);	
	/// <summary>
	/// ��]�s��𐶐�����
	/// </summary>
	/// <param name="yaw">���[Y����]�F�x���@</param>
	/// <param name="pitch">�s�b�`X����]�F�x���@</param>
	/// <param name="roll">���[��Z����]�F�x���@</param>
	/// <returns>��]�s��</returns>
	static Matrix4 CreateFromYawPitchRoll(float yaw, float pitch, float roll);	

	static Vector3 CreateProjection(const Vector3& position, const Matrix4& screen, const Matrix4& perspective, const Matrix4& view, const Matrix4& world = IdentityMatrix);
	static Vector3 CreateUnProjection(const Vector3& position, const Matrix4& screen, const Matrix4& perspective, const Matrix4& view, const Matrix4& world = IdentityMatrix);	
	/// <summary>
	/// DirectX�̃X�N���[���s��𐶐�
	/// </summary>
	/// <param name="position">�X�N���[�����W</param>
	/// <param name="width">�X�N���[����ʂ̉��T�C�Y</param>
	/// <param name="height">�X�N���[����ʂ̏c�T�C�Y</param>
	/// <returns>DirectX�̃X�N���[���s��</returns>
	static Matrix4 CreateScreenDirectX(const Vector2& position, float width, float height);
	/// <summary>
	/// OpenGL�̃X�N���[���s��𐶐�
	/// </summary>
	/// <param name="position">�X�N���[�����W</param>
	/// <param name="width">�X�N���[����ʂ̉��T�C�Y</param>
	/// <param name="height">�X�N���[����ʂ̏c�T�C�Y</param>
	/// <returns>OpenGL�̃X�N���[���s��</returns>
	static Matrix4 CreateScreenOpenGL(const Vector2& position, float width, float height);	
	/// <summary>
	/// ���̍s�񂩂�u���s��𐶐�
	/// </summary>
	/// <returns>�u���s��</returns>
	Matrix4 Transpose();	
	/// <summary>
	/// �s����Ԃ���
	/// </summary>
	/// <param name="matrix">�s��</param>
	/// <param name="amount">��</param>
	/// <returns>��Ԃ����s��</returns>
	Matrix4 Lerp(const Matrix4& matrix, float amount);
	/// <summary>
	/// ���̍s�񂩂�傫���A��]�A���W���擾����
	/// </summary>
	/// <param name="scale">�傫��</param>
	/// <param name="rotation">��]</param>
	/// <param name="translation">���W</param>
	void Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;	
	/// <summary>
	/// �������x�N�g����ݒ�
	/// </summary>
	/// <param name="left">�������x�N�g��</param>
	/// <returns>�������x�N�g����ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetLeft(const Vector3& left);
	/// <summary>
	/// ������x�N�g����ݒ�
	/// </summary>
	/// <param name="left">������x�N�g��</param>
	/// <returns>������x�N�g����ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetUp(const Vector3& up);
	/// <summary>
	/// �O�����x�N�g����ݒ�
	/// </summary>
	/// <param name="left">�O�����x�N�g��</param>
	/// <returns>�O�����x�N�g����ݒ肵�����̍s��̎Q��</returns>
	Matrix4& SetFront(const Vector3& front);	
	/// <summary>
	/// ���̍s�񂩂獶�����x�N�g���𐒓�
	/// </summary>
	/// <returns>�������x�N�g��</returns>
	Vector3 GetLeft() const;
	/// <summary>
	/// ���̍s�񂩂������x�N�g���𐒓�
	/// </summary>
	/// <returns>������x�N�g��</returns>
	Vector3 GetUp() const;
	/// <summary>
	/// ���̍s�񂩂�O�����x�N�g���𐒓�
	/// </summary>
	/// <returns>�O�����x�N�g��</returns>
	Vector3 GetFront() const;
	/// <summary>
	/// ���̍s��ō��W�ϊ����s��
	/// </summary>
	/// <param name="vector">���W�ϊ�������W</param>
	/// <returns>
	/// ���̍s��ɂ���č��W�ϊ����ꂽ���W
	/// </returns>
	Vector3 Transform(const Vector3& vector) const;	
	/// <summary>
	/// �P�ʍs��
	/// </summary>
	/// <returns>�P�ʍs��ɂ������̍s��̎Q��</returns>
	Matrix4& Identity();	
	/// <summary>
	/// ���̍s��̋t�s����擾
	/// </summary>
	/// <returns>�t�s��</returns>
	Matrix4 Inverse() const;
	/// <summary>
	/// ���̍s�񂩂��]�ƕ��s�ړ��݂̂̋t�s����擾
	/// </summary>
	/// <returns>��]�ƕ��s�ړ��݂̂̋t�s��</returns>
	Matrix4 InverseFast() const;	
	/// <summary>
	/// ���̍s�񂩂琳�K��������]�s����擾
	/// </summary>
	/// <returns>���K��������]�s��</returns>
	Matrix4 GetNormalizeRotationMatrix() const;
	/// <summary>
	/// ���̍s��𐳋K������
	/// </summary>
	/// <returns>���K��������]�s��</returns>
	Matrix4& NormalizeRotationMatrix();

private:	
	/// <summary>
	/// ��]�s�񂩂�p�x�����߂�
	/// </summary>
	/// <returns>XYZ���̉�]��</returns>
	Vector3 CalculateAngleFromRotate() const;
public:
	//!�P�ʍs��
	static const Matrix4 IdentityMatrix;

public:
	Matrix4 operator * (const Matrix4& matrix);
	Vector3 operator * (const Vector3& vector);
	Matrix4& operator *= (const Matrix4& matrix);

public:	
	Matrix4 Multiply(const Matrix4& a, const Matrix4& b);
	Vector3 Multiply(const Vector3& vector, const Matrix4& matrix);

public:
	//!�s��̒�`
	using Matrix = std::array<std::array<float, 4>, 4>;
	//!4x4�̍s��
	Matrix m;
};

inline 	Vector3 operator * (const Vector3& vector, const Matrix4& matrix) {
	return Matrix4(matrix).Transform(vector);
}

inline Matrix4 operator * (const Matrix4& m1, const Matrix4& m2) {
	return Matrix4().Multiply(m1, m2);
}