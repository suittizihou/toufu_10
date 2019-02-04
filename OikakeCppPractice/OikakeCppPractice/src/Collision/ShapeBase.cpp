#include"ShapeBase.h"

#include<cassert>

ShapeBase::CollisionFunc  ShapeBase::func;

ShapeBase::ShapeBase()
	: isActive(true)
{
	RegistFunc();
}

bool ShapeBase::Intersect(const ShapeBase& shape, HitInfo& hitInfo) {
	if (shape.GetShapeType() == ShapeType::Max_Num) return false;
	return func[static_cast<int>(shape.GetShapeType())](shape, hitInfo);
}

bool ShapeBase::Collide_BoundingSphere(const ShapeBase& shape, HitInfo& hitInfo) {
	assert(!"It does not override this function.");
	return false;
}
bool ShapeBase::Collide_Capsule(const ShapeBase& shape, HitInfo& hitInfo) {
	assert(!"It does not override this function.");
	return false;
}
bool ShapeBase::Collide_Line(const ShapeBase& shape, HitInfo& hitInfo) {
	assert(!"It does not override this function.");
	return false;
}

bool ShapeBase::Collide_BoundingBox(const ShapeBase & shape, HitInfo & hitInfo)
{
	assert(!"It does not override this function.");
	return false;
}

bool ShapeBase::Collide_OrientedBoundingBox(const ShapeBase & shape, HitInfo & hitInfo)
{
	assert(!"It does not override this function.");
	return false;
}

void ShapeBase::Draw() const {

}

void ShapeBase::RegistFunc() {
	func[0] = [&](const ShapeBase& shape, HitInfo& hitInfo) { return Collide_BoundingSphere(shape, hitInfo); };
	func[1] = [&](const ShapeBase& shape, HitInfo& hitInfo) { return Collide_Capsule(shape, hitInfo); };
	func[2] = [&](const ShapeBase& shape, HitInfo& hitInfo) { return Collide_Line(shape, hitInfo); };
}