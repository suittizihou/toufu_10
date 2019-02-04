#pragma once

#include<array>
#include<functional>
#include"../ShapeType.h"
#include"ShapePtr2D.h"
#include"../HitInfo.h"
#include"Math/Vector2/Vector2.h"

class ShapeBase2D {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ShapeBase2D();
	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~ShapeBase2D() {}

	/// <summary>
	/// �����蔻����s���֐�
	/// </summary>
	/// <param name="shape">�����蔻��p�̌`��</param>
	/// <param name="hitInfo">�����蔻����</param>
	/// <returns></returns>
	bool Intersect(const ShapeBase2D& shape, HitInfo& hitInfo);

	/// <summary>
	/// ���W�ړ�
	/// </summary>
	/// <param name="position">���W</param>
	/// <returns>�ړ������`��|�C���^</returns>
	virtual ShapePtr2D Translate(const Vector2& position) const = 0;

	/// <summary>
	/// �`��̎�ނ��擾
	/// </summary>
	/// <returns>�`��̎��</returns>
	virtual ShapeType2D GetShapeType() const { return ShapeType2D::Max_Num; }

	/// <summary>
	/// ���Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">���̃|�C���^</param>
	/// <param name="hitInfo">�����蔻����</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Circle(const ShapeBase2D& shape, HitInfo& hitInfo);

	/// <summary>
	/// �J�v�Z���Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">�J�v�Z���̃|�C���^</param>
	/// <param name="hitInfo">�����蔻��̏��</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Capsule(const ShapeBase2D& shape, HitInfo& hitInfo);

	/// <summary>
	/// �����Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">�����̃|�C���^</param>
	/// <param name="hitInfo">�����蔻��̏��</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Line(const ShapeBase2D& shape, HitInfo& hitInfo);

	virtual bool Collide_Box(const ShapeBase2D& shape, HitInfo& hitInfo);

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
	using CollisionFunc = std::array < std::function<bool(const ShapeBase2D&, HitInfo& hitInfo)>, static_cast<int>(ShapeType2D::Max_Num)>;
	//!�����蔻��̊֐�������z��
	static CollisionFunc func;

};
