#include "ShapeBase2D.h"
#include<cassert>

ShapeBase2D::CollisionFunc  ShapeBase2D::func;

ShapeBase2D::ShapeBase2D()
	: isActive(true)
{
	RegistFunc();
}

bool ShapeBase2D::Intersect(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	return func[static_cast<int>(shape.GetShapeType())](shape, hitInfo);
}


bool ShapeBase2D::Collide_Circle(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	assert(!"It does not override this function.");
	return false;
}

bool ShapeBase2D::Collide_Capsule(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	assert(!"It does not override this function.");
	return false;
}

bool ShapeBase2D::Collide_Line(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	assert(!"It does not override this function.");
	return false;
}

bool ShapeBase2D::Collide_Box(const ShapeBase2D & shape, HitInfo & hitInfo)
{
	assert(!"It does not override this function.");
	return false;
}

void ShapeBase2D::Draw() const
{
}

void ShapeBase2D::RegistFunc()
{
	func[0] = [&](const ShapeBase2D& shape, HitInfo& hitInfo) { return Collide_Circle(shape, hitInfo); };
	func[1] = [&](const ShapeBase2D& shape, HitInfo& hitInfo) { return Collide_Box(shape, hitInfo); };
}
