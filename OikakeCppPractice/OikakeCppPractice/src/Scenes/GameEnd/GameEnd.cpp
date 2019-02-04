#include "GameEnd.h"
#include "Application/GameApplication/GameApplication.h"

GameEnd::GameEnd()
{
}

GameEnd::~GameEnd()
{
}

void GameEnd::LoadAssets()
{
}

void GameEnd::Initialize()
{
	GameApplication::ShutDown();
}

void GameEnd::FirstUpdate(float deltaTime)
{
}

void GameEnd::Update(float deltaTime)
{
}

void GameEnd::Draw() const
{
}

bool GameEnd::IsEnd() const
{
	return false;
}

Scene GameEnd::Next() const
{
	return Scene();
}

void GameEnd::Finalize()
{
}
