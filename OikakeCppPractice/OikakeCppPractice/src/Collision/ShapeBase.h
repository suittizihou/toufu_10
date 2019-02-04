#pragma once

#include<array>
#include<functional>
#include"ShapeType.h"
#include"ShapePtr.h"

class Vector3;
class Matrix4;
class HitInfo;

/**
 * @file ShapeBase.h
 * @brief �����蔻��̃x�[�X�ɂȂ�N���X��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

 /*! @class ShapeBase
 *   @brief �����蔻��̃x�[�X�ɂȂ�N���X
 */
class ShapeBase {
public:	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ShapeBase();	
	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~ShapeBase() {}
	
	/// <summary>
	/// �����蔻����s���֐�
	/// </summary>
	/// <param name="shape">�����蔻��p�̌`��</param>
	/// <param name="hitInfo">�����蔻����</param>
	/// <returns></returns>
	bool Intersect(const ShapeBase& shape, HitInfo& hitInfo);
	
	/// <summary>
	/// ���W�ړ�
	/// </summary>
	/// <param name="position">���W</param>
	/// <returns>�ړ������`��|�C���^</returns>
	virtual ShapePtr Translate(const Vector3& position) const = 0;	
	/// <summary>
	/// ���W�ϊ�
	/// </summary>
	/// <param name="matrix">�p���s��</param>
	/// <returns>���W�ϊ����ꂽ�`��|�C���^</returns>
	virtual ShapePtr Transform(const Matrix4& matrix) const = 0;
	
	/// <summary>
	/// �`��̎�ނ��擾
	/// </summary>
	/// <returns>�`��̎��</returns>
	virtual ShapeType GetShapeType() const { return ShapeType::Max_Num; }
	
	/// <summary>
	/// ���Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">���̃|�C���^</param>
	/// <param name="hitInfo">�����蔻����</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_BoundingSphere(const ShapeBase& shape, HitInfo& hitInfo);
	
	/// <summary>
	/// �J�v�Z���Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">�J�v�Z���̃|�C���^</param>
	/// <param name="hitInfo">�����蔻��̏��</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Capsule(const ShapeBase& shape, HitInfo& hitInfo);
	
	/// <summary>
	/// �����Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">�����̃|�C���^</param>
	/// <param name="hitInfo">�����蔻��̏��</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Line(const ShapeBase& shape, HitInfo& hitInfo);
	
	virtual bool Collide_BoundingBox(const ShapeBase& shape, HitInfo& hitInfo);
	virtual bool Collide_OrientedBoundingBox(const ShapeBase& shape, HitInfo& hitInfo);

	/// <summary>
	/// �����蔻������C���[�t���[���ŕ`��
	/// </summary>
	virtual void Draw() const;

public:
	//!�����蔻����s�����ǂ����H
	bool isActive;
private:	
	/// <summary>
	/// �����蔻��̊֐���o�^����
	/// </summary>
	void RegistFunc();
private:
	//!�����蔻��̊֐�������z��
	using CollisionFunc = std::array < std::function<bool(const ShapeBase&, HitInfo& hitInfo)>, static_cast<int>(ShapeType::Max_Num)>;
	//!�����蔻��̊֐�������z��
	static CollisionFunc func;
};