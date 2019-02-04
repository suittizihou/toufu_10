#include "Box.h"

#include<cassert>
#include"Collision/Collision.h"

Box::Box(const Vector2 & min, const Vector2 & max)
	: min(min)
	, max(max)
	, size(max - min)
{
}

Box::~Box()
{
}

ShapePtr2D Box::Translate(const Vector2 & position) const
{
	ShapePtr2D shape = std::make_shared<Box>(position + min, position + max);
	shape->isActive = isActive;
	return shape;
}

bool Box::Collide_Circle(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	return false;
}

bool Box::Collide_Capsule(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	return false;
}

bool Box::Collide_Line(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	return false;
}

bool Box::Collide_Box(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	const Box* box = static_cast<const Box*>(&shape);
	if (box == nullptr) {
		assert(!"Conversion failed.");
		return false;
	}
	return Collision2D::Box_Box(*this, *box,hitInfo);
}

void Box::Draw() const
{
}
