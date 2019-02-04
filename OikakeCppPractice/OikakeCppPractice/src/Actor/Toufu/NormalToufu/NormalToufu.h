#pragma once

#include"Actor/Base/Actor2D.h"

enum class NormalToufuMove {
	SponeMove,
	SponeMoveStop,
};

class NormalToufu : public Actor2D {
public:
	NormalToufu(IWorld* world, const Vector2& position, const int& _number);
	~NormalToufu();
	bool GetBoolMove();
private:
	virtual void OnInitialize() override;
	virtual void OnFirstUpdate(float deltaTime) override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(Renderer& renderer)override;
	virtual void OnFinalize()override;
	virtual void OnMessage(EventMessage message, void* param)override;
	virtual void OnCollide(const HitInfo& hitInfo)override;

	void Damage(const HitInfo& hitInfo);

	float GetDegree(Vector2 targetposition, Vector2 thisposition);
	bool TopHit(Vector2 targetposition, Vector2 thisposition);
	bool BottomHit(Vector2 targetposition, Vector2 thisposition);
	bool LeftHit(Vector2 targetposition, Vector2 thisposition);
	bool RightHit(Vector2 targetposition, Vector2 thisposition);
	bool L_R_Hit(Vector2 targetposition, Vector2 thisposition);
	bool T_B_Hit(Vector2 targetposition, Vector2 thisposition);
	float RightUpDegree();
	float LeftUpDegree();

private:
	void Move();
	bool _move = false;
	NormalToufuMove spone_move{};
	Vector2 spone_position{};
	Vector2 one_time_position{};
	Vector2 default_position{};

	Vector2 target_pos{};
	Vector2 velocity{};

	int hp{ 3 };	// �̗�

private:
	Vector2 Average_Position(const Vector2& position);
};