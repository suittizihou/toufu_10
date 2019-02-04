#pragma once
#include"Actor/Base/ActorBase.h"
#include"Math/Vector2/Vector2.h"
#include"Collision/Collision2D/ShapePtr2D.h"

class Actor2D : public ActorBase {
public:
	Actor2D(IWorld* world, const std::string& name, const Vector2& position, const ShapePtr2D& body, const int& _number, const float speed = 1, const int input_type = 0, const Character chara = Character::None);
	virtual ~Actor2D();
protected:
	virtual void OnInitialize();
	virtual void OnFirstUpdate(float deltaTime);
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(Renderer& renderer);
	virtual void OnFinalize();
	virtual void OnMessage(EventMessage message, void* param);
	virtual void OnCollide(const HitInfo& hitInfo);
private:
	virtual bool IsCollide(const ActorBase& other, HitInfo& hitInfo) override;
protected:

	ShapePtr2D body;
};