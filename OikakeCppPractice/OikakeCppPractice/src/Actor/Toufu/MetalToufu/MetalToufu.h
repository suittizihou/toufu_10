#pragma once

#include"Actor/Base/Actor2D.h"

enum class MetalToufuMove {
	SponeMove,
	SponeMoveStop,
};

class MetalToufu : public Actor2D {
public:
	MetalToufu(IWorld* world, const Vector2& position, const int& _number, bool spone_special_move);
	~MetalToufu();
	bool GetBoolMove();
private:
	virtual void OnInitialize() override;
	virtual void OnFirstUpdate(float deltaTime) override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(Renderer& renderer)override;
	virtual void OnFinalize()override;
	virtual void OnMessage(EventMessage message, void* param)override;
	virtual void OnCollide(const HitInfo& hitInfo)override;

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
	void SponeMove();
	bool _move = false;
	bool spone_special_move_{};
	MetalToufuMove spone_move{};
	Vector2 spone_position{};
	Vector2 one_time_position{};
	Vector2 default_position{};

private:
	Vector2 Average_Position();
};