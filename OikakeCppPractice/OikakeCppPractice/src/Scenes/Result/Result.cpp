#include "Result.h"
#include "Scenes/Base/Scene.h"
#include"Renderer/Renderer.h"
#include"Input/Input.h"
#include"Actor/UI/Score/Score.h"
#include"World/World.h"

Result::Result(WorldPtr & world)
	: isEnd(false)
	, world(world)
	, renderer(Renderer::GetInstance())
{
}

Result::~Result()
{
}

void Result::LoadAssets()
{
	renderer.LoadTexture(Assets::Texture::Result_Loser1, "result/result_loser1.png");
	renderer.LoadTexture(Assets::Texture::Result_Loser2, "result/result_loser2.png");
	renderer.LoadTexture(Assets::Texture::Result_Loser3, "result/result_loser3.png");
	renderer.LoadTexture(Assets::Texture::Result_Loser4, "result/result_loser4.png");
	renderer.LoadTexture(Assets::Texture::Result_Winner1, "result/result_winner1.png");
	renderer.LoadTexture(Assets::Texture::Result_Winner2, "result/result_winner2.png");
	renderer.LoadTexture(Assets::Texture::Result_Winner3, "result/result_winner3.png");
	renderer.LoadTexture(Assets::Texture::Result_Winner4, "result/result_winner4.png");
	renderer.LoadTexture(Assets::Texture::Result_Menu, "result/result_menu.png");
	renderer.LoadTexture(Assets::Texture::Result_Menu1, "result/result_menu1.png");
	renderer.LoadTexture(Assets::Texture::Result_Menu2, "result/result_menu2.png");
	renderer.LoadTexture(Assets::Texture::Result_Menu3, "result/result_menu3.png");
	renderer.LoadTexture(Assets::Texture::Result, "result/result.png");
}

void Result::Initialize()
{
	isEnd = false;
	world->Initialize();
	world->AddActor_Back(ActorGroup::UI, std::make_shared<ResultMenu>(world.get()));
	world->AddActor_Back(ActorGroup::UI, std::make_shared<ResultCharacter>(world.get()));
}

void Result::FirstUpdate(float deltaTime)
{
}

void Result::Update(float deltaTime)
{
	// 今選ばれているメニューをゲットしてくる
	select = ResultManager::GetSelect();

	Input::GetInstance().Update();
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_SPACE)) {
		// メニューでゲームエンド以外が選択された場合、シーンを切り替える
		isEnd = true;
	}
	world->Update(deltaTime);
}

void Result::Draw() const
{
	renderer.DrawTexture(Assets::Texture::Result);
	

	world->Draw(renderer);
}

bool Result::IsEnd() const
{
	return isEnd;
}

Scene Result::Next() const
{
	switch (select) {
	case 0:
		return Scene::GameMain;
		break;

	case 1:
		return Scene::CharacterSelect;
		break;

	default:
		return Scene::GameEnd;
		break;
	}
}

void Result::Finalize()
{
	world->Finalize();
	renderer.Clear();
}

void Result::HandleMessage(EventMessage message, void * param)
{
}
