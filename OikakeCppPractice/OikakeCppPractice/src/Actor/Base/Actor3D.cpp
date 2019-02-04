#include "Actor3D.h"
#include"Collision/ShapeBase.h"
#include"Collision/HitInfo.h"
#include"Utility/cpplinq.hpp"
using namespace cpplinq;

Actor3D::Actor3D()
	: ActorBase(nullptr,"none", Vector2::Zero, Vector2::Zero, 0, 0.0f, 0)
	, position()
	, matrix()
	, bodies(0)
{
}

Actor3D::Actor3D(IWorld * world, const std::string & name, const Vector3 & position, const ShapePtr & body)
	: ActorBase(world, name, Vector2::Zero, Vector2::Zero, 0, 0.0f, 0)
	, position(position)
	, matrix()
	, bodies(0)
{
	if (body == nullptr)
		return;

	bodies.emplace_back(body);
}

Actor3D::Actor3D(IWorld * world, const std::string & name, const Vector3 & position, const std::vector<ShapePtr>& bodies)
	: ActorBase(world, name, Vector2::Zero, Vector2::Zero, 0, 0.0f, 0)
	, position(position)
	, matrix()
	, bodies(bodies)
{
}

Actor3D::~Actor3D()
{
	bodies.clear();
	bodies.reserve(0);
}

void Actor3D::SetBodyActive(bool isActive, int index)
{
	bodies.at(index)->isActive = isActive;
}

Matrix4 Actor3D::GetMatrix() const
{
	return Matrix4(matrix).SetPosition(position);
}


void Actor3D::DrawBodies()
{
	for (auto i : bodies) {
		i->Transform(GetMatrix())->Draw();
	}
}

std::vector<ShapePtr> Actor3D::GetBodies() const
{
	return bodies;
}

void Actor3D::OnInitialize()
{
}

void Actor3D::OnUpdate(float deltaTime)
{
	static_cast<void>(deltaTime);
}

void Actor3D::OnDraw(Renderer & renderer)
{
	static_cast<void>(renderer);
}

void Actor3D::OnDrawShadow(Renderer & renderer)
{
	static_cast<void>(renderer);
}

void Actor3D::OnDrawAlpha(Renderer & renderer)
{
	static_cast<void>(renderer);
}

void Actor3D::OnFinalize()
{
}

void Actor3D::OnMessage(EventMessage message, void * param)
{
	static_cast<void>(message);
	static_cast<void>(param);
}

void Actor3D::OnCollision(const HitInfo & hitInfo)
{
	static_cast<void>(hitInfo);
}

bool Actor3D::IsCollide(const ActorBase & other, HitInfo & hitInfo)
{
	//TODO:‚±‚±Œ©’¼‚µ•‘Š’k

	const Actor3D* otherActor = dynamic_cast<const Actor3D*>(&other);
	if (otherActor == nullptr) return false;

	//“–‚½‚è”»’è‚ª–³‚©‚Á‚½‚çƒŠƒ^[ƒ“‚·‚é
	if (bodies.empty() == true || otherActor->bodies.empty() == true) return false;

	auto activeBodies = from(bodies) >> where([](const ShapePtr& shape) {return shape->isActive == true; }) >> to_vector();
	auto activeOtherBodies = from(otherActor->bodies) >> where([](const ShapePtr& shape) {return shape->isActive == true; }) >> to_vector();

	for (auto self : activeBodies) {
		for (auto other : activeOtherBodies) {
			bool isIntersect = self->Transform(GetMatrix())->Intersect(
				*other->Transform(otherActor->GetMatrix()).get(), hitInfo);
			if (isIntersect == true) {
				//‚±‚±‚Å‚¨Œİ‚¢‚Ì“–‚½‚è”»’è‚Ì”Ô†‚ğ“o˜^‚·‚éƒvƒƒOƒ‰ƒ€‚ğ’Ç‰Á
				return true;
			}
		}
	}
	//1‚ÂˆÈãÕ“Ëî•ñ‚ª“ü‚Á‚Ä‚¢‚½‚çÕ“Ë‚µ‚Ä‚¢‚é
	//return hitInfo.contents.empty() == false;
	return false;
}
