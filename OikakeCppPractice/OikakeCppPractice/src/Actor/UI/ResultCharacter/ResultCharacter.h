#pragma once
#include "Actor/Base/Actor2D.h"
#include "DecideWinnerAndLoser.h"

class ResultCharacter : public Actor2D {
public:
	ResultCharacter(IWorld* world);
	~ResultCharacter();

private:
	virtual void OnInitialize()override;
	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(Renderer& renderer)override;
};