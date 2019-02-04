#pragma once

class HitInfo;
class Box;
class Circle;

/**
 * @file Collision.h
 * @brief �����蔻��̊֐����܂Ƃ߂��N���X��`�t�@�C��
 * @author ���]
 * @date Unknown
 */

/*! @class Collision
 *   @brief �����蔻��̊֐����܂Ƃ߂��N���X
 */
class Collision2D {
public:

	static bool Box_Box(const Box& box1, const Box& box2, HitInfo& hitInfo);
	static bool Circle_Circle(const Circle& circle1, const Circle& circle2, HitInfo& hitInfo);
	static bool Box_Circle(const Box& box, const Circle& circle, HitInfo& hitInfo);

};
