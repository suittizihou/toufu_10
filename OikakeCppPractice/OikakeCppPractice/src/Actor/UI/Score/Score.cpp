#include "Score.h"
#include"Renderer/Renderer.h"
#include"World/SceneShareValue/SceneShareValue.h"

Score::Score(IWorld * world)
	: Actor2D(world, "Score", Vector2::Zero, nullptr,0)
	, score(0)
{
	status = Status::DrawOnly;
}

Score::~Score()
{
}

void Score::OnInitialize()
{
	score = world->GetSceneShareValue().score;
}

void Score::OnDraw(Renderer & renderer)
{
	renderer.DrawNumber(Assets::Texture::Number, position, score, 32, 64, 3);
}

void Score::OnFinalize()
{
}

void Score::OnMessage(EventMessage message, void * param)
{
	if (message == EventMessage::AddScore) {
		score += *(int*)param;
	}
	if (message == EventMessage::GameEnd) {
		world->GetSceneShareValue().score = score;
	}
}
