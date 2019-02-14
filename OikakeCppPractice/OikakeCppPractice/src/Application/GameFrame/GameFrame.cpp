#include "GameFrame.h"
#include"World/World.h"
#include"Scenes/Base/SceneManager.h"
#include"Scenes/Base/Scene.h"
#include"Scenes/Title/Title.h"
#include"Scenes/CharacterSelect/CharacterSelect.h"
#include"Scenes/Description/Description.h"
#include"Scenes/GameMain/GameMain.h"
#include"Scenes/Result/Result.h"
#include "Scenes/GameEnd/GameEnd.h"
#include "Actor/Map/MapGenerater/MapGenerater.h"


GameFrame::GameFrame()
	: GameApplication()
	, world(nullptr)
	, sceneManager()
{
	
}

GameFrame::~GameFrame()
{
}

void GameFrame::Initialize()
{
	world = std::make_shared<World>();
	sceneManager.Initialize();

	sceneManager.Add(Scene::Title, std::make_shared<Title>(world));
	sceneManager.Add(Scene::CharacterSelect, std::make_shared<CharacterSelect>(world));
	sceneManager.Add(Scene::Description, std::make_shared<Description>(world));
	sceneManager.Add(Scene::GameMain, std::make_shared<GameMain>(world));
	sceneManager.Add(Scene::Result, std::make_shared<Result>(world));
	sceneManager.Add(Scene::GameEnd, std::make_shared<GameEnd>());

	sceneManager.Change(Scene::CharacterSelect);

}

void GameFrame::Update(float deltaTime)
{
	sceneManager.Update(deltaTime);
}

void GameFrame::Draw()
{
	sceneManager.Draw();
}

void GameFrame::Reset()
{
	MapGenerater::clear_toufu();
}

void GameFrame::Finalize()
{
	sceneManager.Finalize();
}