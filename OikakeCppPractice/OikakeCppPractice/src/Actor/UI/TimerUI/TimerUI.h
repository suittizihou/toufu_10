#pragma once

#include"Actor/Base/Actor2D.h"
#include"Utility/Timer/Timer.h"

class TimerUI : public Actor2D {
public:
	TimerUI(IWorld* world, float time,  const int& _number);
	~TimerUI();
private:
	virtual void OnInitialize() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw(Renderer& renderer)override;
	virtual void OnFinalize()override;
	virtual void OnMessage(EventMessage message, void* param)override;
private:
	void GameEnd();
private:
	Timer timer;
};