#pragma once

#include"../ShapeBase2D.h"

class Circle : public ShapeBase2D {
public:

	Circle(const Vector2& center,float radius);
	~Circle();

	/// <summary>
	/// ���W�ړ�
	/// </summary>
	/// <param name="position">���W</param>
	/// <returns>�ړ������`��|�C���^</returns>
	virtual ShapePtr2D Translate(const Vector2& position) const override;

	/// <summary>
	/// �`��̎�ނ��擾
	/// </summary>
	/// <returns>�`��̎��</returns>
	virtual ShapeType2D GetShapeType() const override { return ShapeType2D::Circle; }

	/// <summary>
	/// ���Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">���̃|�C���^</param>
	/// <param name="hitInfo">�����蔻����</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Circle(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	/// <summary>
	/// �J�v�Z���Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">�J�v�Z���̃|�C���^</param>
	/// <param name="hitInfo">�����蔻��̏��</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Capsule(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	/// <summary>
	/// �����Ƃ̂����蔻��
	/// </summary>
	/// <param name="shape">�����̃|�C���^</param>
	/// <param name="hitInfo">�����蔻��̏��</param>
	/// <returns>[true �Փ˂���: false �Փ˂��Ă��Ȃ�]</returns>
	virtual bool Collide_Line(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	virtual bool Collide_Box(const ShapeBase2D& shape, HitInfo& hitInfo) override;

	/// <summary>
	/// �����蔻������C���[�t���[���ŕ`��
	/// </summary>
	virtual void Draw() const override;

public:
	Vector2 center;
	float radius;
};