#include "TimerUI.h"
#include"Renderer/Renderer.h"

TimerUI::TimerUI(IWorld * world, float time , const int& _number)
	: Actor2D(world,"TimerUI",Vector2::Zero,nullptr, _number)
	, timer(time, [&]() {
		GameEnd();
	})
{
}

TimerUI::~TimerUI()
{
}

void TimerUI::OnInitialize()
{
	timer.Initialize();
	position = Vector2(640, 0.0f);
}

void TimerUI::OnUpdate(float deltaTime)
{
	timer.Update(deltaTime);
}

void TimerUI::OnDraw(Renderer & renderer)
{
	int minute = (int)timer.GetSecond() / 60;
	renderer.DrawNumber(Assets::Texture::Number, position, minute, 32, 64, 2);
	int second = (int)timer.GetSecond() % 60;
	renderer.DrawNumber(Assets::Texture::Number, position + Vector2(32 * 3,0.0f), second, 32, 64, 2);
}

void TimerUI::OnFinalize()
{
}

void TimerUI::OnMessage(EventMessage message, void * param)
{
}

void TimerUI::GameEnd()
{
	world->SendEventMessage(EventMessage::GameEnd);
}
