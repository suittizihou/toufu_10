#pragma once

#include"Actor/Base/Actor2D.h"

class Score : public Actor2D {
public:
	explicit Score(IWorld* world);
	~Score();
private:
	virtual void OnInitialize() override;
	virtual void OnDraw(Renderer& renderer)override;
	virtual void OnFinalize()override;
	virtual void OnMessage(EventMessage message, void* param)override;
private:
	int score;
};