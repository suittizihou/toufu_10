#include "Actor2D.h"
#include"Collision/Collision2D/ShapeBase2D.h"

Actor2D::Actor2D(IWorld* world, const std::string& name, const Vector2& position, const ShapePtr2D& body, const int& _number, const float speed, const int input_type, const Character chara)
	: ActorBase(world, name, position, center_pos, _number, speed, input_type, chara)
	, body(body)
{
}

Actor2D::~Actor2D()
{
}

void Actor2D::OnInitialize()
{
}

void Actor2D::OnFirstUpdate(float deltaTime) {
	static_cast<void>(deltaTime);
}

void Actor2D::OnUpdate(float deltaTime)
{
	static_cast<void>(deltaTime);
}

void Actor2D::OnDraw(Renderer & renderer)
{
	static_cast<void>(renderer);
}

void Actor2D::OnFinalize()
{
}

void Actor2D::OnMessage(EventMessage message, void * param)
{
	static_cast<void>(message);
	static_cast<void>(param);
}

void Actor2D::OnCollide(const HitInfo & hitInfo)
{
	static_cast<void>(hitInfo);
}

bool Actor2D::IsCollide(const ActorBase & other, HitInfo & hitInfo)
{
	const Actor2D* otherActor = static_cast<const Actor2D*>(&other);
	if (otherActor == nullptr)
		return false;
	if (body == nullptr || otherActor->body == nullptr)
		return false;
	if (body->isActive == false || otherActor->body->isActive == false)
		return false;

	return body->Translate(position)->Intersect(
		*(otherActor->body->Translate(otherActor->position)), hitInfo);

}
