#pragma once

#include"Actor/Base/Actor2D.h"
#include "../../Input/MoveState.h"
#include "Utility/Random/Random.h"

class Player2 : public Actor2D {
public:
	Player2(IWorld* world, const Vector2& position, const int& _number, const float _speed, int input_pad, Character chara);
	~Player2();

private:
	virtual void OnInitialize() override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(Renderer& renderer)override;
	virtual void OnFinalize()override;
	virtual void OnMessage(EventMessage message, void* param)override;
	virtual void OnCollide(const HitInfo& hitInfo)override;
private:
	float speed;
	bool collision = false;

	Vector2 target_position{};
	Vector2 velocity{};

	Random rand;

	int hp{ 3 };

	int time	{};
	int animeX	{};

private:
	Vector2 Average_Position();
};