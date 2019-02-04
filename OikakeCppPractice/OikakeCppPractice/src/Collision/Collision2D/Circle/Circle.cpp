#include "Circle.h"
#include<cassert>
#include"Collision/Collision.h"
#include<DxLib.h>

Circle::Circle(const Vector2 & center, float radius)
	: center(center)
	, radius(radius)
{
}

Circle::~Circle()
{
}

ShapePtr2D Circle::Translate(const Vector2 & position) const
{
	ShapePtr2D shape = std::make_shared<Circle>(position + center, radius);
	shape->isActive = isActive;
	return shape;
}

bool Circle::Collide_Circle(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	const Circle* circle = static_cast<const Circle*>(&shape);
	if (circle == nullptr) {
		assert(!"Conversion failed.");
		return false;
	}
	return Collision2D::Circle_Circle(*this, *circle, hitInfo);
}

bool Circle::Collide_Capsule(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	return false;
}

bool Circle::Collide_Line(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	return false;
}

bool Circle::Collide_Box(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	return false;
}

void Circle::Draw() const
{

}
