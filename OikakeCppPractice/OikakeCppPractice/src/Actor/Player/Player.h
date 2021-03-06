#pragma once

#include"Actor/Base/Actor2D.h"
#include "Utility/Random/Random.h"
#include"../PlayerManager/MoveState.h"

class Player : public Actor2D {
public:
	Player(IWorld* world, const Vector2& position, const int& _number, const float _speed, int input_pad, Character chara);
	~Player();

private:
	virtual void OnInitialize() override;
	virtual void OnFirstUpdate(float deltaTime) override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(Renderer& renderer)override;
	virtual void OnFinalize()override;
	virtual void OnMessage(EventMessage message, void* param)override;
	virtual void OnCollide(const HitInfo& hitInfo)override;
private:

	void Damage();
	Vector2 Average_Position();

	float GetDegree(Vector2 targetposition, Vector2 thisposition);
	bool TopHit(Vector2 targetposition, Vector2 thisposition);
	bool BottomHit(Vector2 targetposition, Vector2 thisposition);
	bool LeftHit(Vector2 targetposition, Vector2 thisposition);
	bool RightHit(Vector2 targetposition, Vector2 thisposition);
	bool L_R_Hit(Vector2 targetposition, Vector2 thisposition);
	bool T_B_Hit(Vector2 targetposition, Vector2 thisposition);

private:

	Random rand;

	float speed{};
	bool collision{};
	bool toufu_hit{};

	Vector2 target_position{};
	Vector2 previous_target_position{};
	Vector2 velocity{};

	MoveState move_state{ MoveState::Stop };

	int hp{ 3 };

	int time{};
	int animeY{};
	int animeX{};
	int beforeMovementY{};
	int beforeMovementX{};

	bool firstDraw{};
	bool damage{};

	int direction = 1;

	//��
	int hitSh{};

	int seflag{};
};