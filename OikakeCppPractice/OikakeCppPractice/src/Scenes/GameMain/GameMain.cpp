#include "GameMain.h"
#include "Scenes/Base/Scene.h"
#include"World/World.h"
#include"Actor/Base/ActorGroup.h"
#include"Renderer/Renderer.h"
#include"Actor/Base/EventMessage.h"
#include"Actor/Player/Player.h"
#include"Actor/Player2/Player2.h"
#include"Actor/Toufu/NormalToufu/NormalToufu.h"
#include"Actor/Toufu/MetalToufu/MetalToufu.h"
#include"Utility/Random/Random.h"
#include"Application/Window/Window.h"
#include"Actor/UI/Score/Score.h"
#include"Actor/UI/TimerUI/TimerUI.h"
#include"Input/Input.h"
#include"Scenes/CharacterSelect/CharacterManager.h"

GameMain::GameMain(WorldPtr& world)
	: isEnd(false)
	, world(world)
	, mapGenerater(world)
	, renderer(Renderer::GetInstance())
{
}

GameMain::~GameMain() {

}

void GameMain::LoadAssets()
{
	renderer.LoadTexture(Assets::Texture::NormalTile, "gameplay/normalTile.png");
	renderer.LoadTexture(Assets::Texture::Hole, "gameplay/hole.png");
	renderer.LoadTexture(Assets::Texture::NormalToufuTile, "gameplay/normalToufuTile.png");
	renderer.LoadTexture(Assets::Texture::MetalToufuTile, "gameplay/metalToufuTile.png");
	renderer.LoadTexture(Assets::Texture::RedTile, "gameplay/redTile.png");
	renderer.LoadTexture(Assets::Texture::BlueTile, "gameplay/blueTile.png");
	//renderer.LoadTexture(Assets::Texture::Player, "player.png");
	//renderer.LoadTexture(Assets::Texture::Player2, "player.png");
	renderer.LoadTexture(Assets::Texture::Ninja, "gameplay/player3.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Front_Anime, "gameplay/player3_anime_walk.png");
	renderer.LoadTexture(Assets::Texture::Kinniku, "gameplay/player1.png");
	renderer.LoadTexture(Assets::Texture::Yoroi, "gameplay/player4.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka, "gameplay/player2.png");
	//renderer.LoadTexture(Assets::Texture::Player2, "player_atari.jpg");
	renderer.LoadTexture(Assets::Texture::NormalToufu, "gameplay/tofu.png");
	renderer.LoadTexture(Assets::Texture::MetalToufu, "gameplay/iron_tofu.png");
	renderer.LoadTexture(Assets::Texture::Number, "number.png");
}

void GameMain::Initialize() {
	world->GetSceneShareValue().Initialize();
	world->Initialize();

	//// マップチップをアクターにまとめて登録
	mapGenerater.AddMapChip();

	world->AddActor_Back(ActorGroup::Player, std::make_shared<Player>(world.get(), Vector2::Zero, objNumber, 5.0f, DX_INPUT_PAD1, CharacterManager::GetCharacterP1()));
	objNumber++;
	world->AddActor_Back(ActorGroup::Player2, std::make_shared<Player2>(world.get(), mapGenerater.up_left_get_pos(7, 7) - Vector2(0, 58.0f), objNumber, 5.0f, DX_INPUT_PAD2, CharacterManager::GetCharacterP2()));
	objNumber++;
	//world->AddActor_Back(ActorGroup::UI, std::make_shared<Score>(world.get()));
	world->AddActor_Back(ActorGroup::UI, std::make_shared<TimerUI>(world.get(),1 * 60000,0));
	objNumber++;
	Random rand;
	for (int i = 0; i < 3;) {
		int x = rand.Range(0, 7);
		int y = rand.Range(0, 7);//Vector2(187, 31)

		// 0と7の配列番号の時確率をいじる
		if (x == 0 || y == 0 || x == 7 || y == 7) {
			// 30%の確立でリセット
			if (rand.Range(0, 10) <= 7) { continue; }
		}
		// xとyどちらも0の場合豆腐は落ちない || xとyどちらも7の場合豆腐は落ちない
		if (x == 0 && y == 0 || x == 7 && y == 7) { continue; }
		// 豆腐が無かったら生成
		if (mapGenerater.check_toufu(x, y)) { continue; }
		world->AddActor_Back(ActorGroup::NormalToufu,
				std::make_shared<NormalToufu>(world.get(),
					mapGenerater.up_left_get_pos(x, y) + Vector2(1.0f, -57.0f),
					objNumber));

		mapGenerater.set_map_toufu(x, y, ToufuID::Normal);
			objNumber++;
			++i;
	}

	for (int i = 0; i < 3;) {
		int x = rand.Range(0, 7);
		int y = rand.Range(0, 7);//Vector2(187, 31)

		// 0と7の配列番号の時確率をいじる
		if (x == 0 || y == 0 || x == 7 || y == 7) {
			// 70%の確立でリセット
			if (rand.Range(0, 10) <= 7) { continue; }
		}
		// xとyどちらも0の場合豆腐は落ちない || xとyどちらも7の場合豆腐は落ちない
		if (x == 0 && y == 0 || x == 7 && y == 7) { continue; }
		// 豆腐が無かったら生成
		if (mapGenerater.check_toufu(x, y)) { continue; }
			world->AddActor_Back(ActorGroup::MetalToufu,
			std::make_shared<MetalToufu>(world.get(),
			mapGenerater.up_left_get_pos(x, y) + Vector2(1.0f, -57.0f),
			objNumber,
			FALSE));
			mapGenerater.set_map_toufu(x, y, ToufuID::Metal);
			objNumber++;
			++i;
	}

	isEnd = false;

	//!ワールドのイベントメッセージを受け取る
	world->AddEventMessageListener([&](EventMessage message, void* param) {
		HandleMessage(message, param);
	});
}

void GameMain::FirstUpdate(float deltaTime)
{
	world->FirstUpdate(deltaTime);
}

int GameMain::RandomJudge(int value1, int value2) {
	Random rand;

	if (rand.Range(0, 1) == 0) {
		return value1;
	}
	else {
		return value2;
	}
}

void GameMain::Update(float deltaTime) {

	if (random_toufu_time > toufu_spone_limit && 20 > MapGenerater::get_toufu_value())
	{
		Random rand;

		int x{};
		int y{};

		// 15秒以上経過したらこっちを回す
		if (random_toufu_time >= 900) {
			x = RandomJudge(0, 7);
			y = RandomJudge(0, 7);
		}// 5で割り切れる数字ならランダムを回す
		else if (random_toufu_time % 5 == 0) {
			x = rand.Range(1, 6);
			y = rand.Range(1, 6);
		}		

		// 0と7の配列番号の時確率をいじる
		if (x == 0 || y == 0 || x == 7 || y == 7) {
			// 70%の確立でリセット
			if (rand.Range(0, 10) <= 7) { goto end; }
		}
		// xとyどちらも0の場合豆腐は落ちない || xとyどちらも7の場合豆腐は落ちない
		if (x == 0 && y == 0 || x == 7 && y == 7) { goto end; }
		// 豆腐が無かったら生成
		if (mapGenerater.check_toufu(x, y)) { goto end; }
		if (rand.Range(0, 10) == 0) {
			world->AddActor_Back(ActorGroup::MetalToufu,
			std::make_shared<MetalToufu>(world.get(),
			mapGenerater.up_left_get_pos(x, y) + Vector2(1.0f, -57.0f),
			objNumber,
			TRUE));
		}
		else {
			world->AddActor_Back(ActorGroup::NormalToufu,
				std::make_shared<NormalToufu>(world.get(),
					mapGenerater.up_left_get_pos(x, y) + Vector2(1.0f, -57.0f),
					objNumber));
		}
			objNumber++;

			toufu_spone_limit += 300;

			if (toufu_spone_limit >= 900) {
				toufu_spone_limit = 300; 
				random_toufu_time = 0;
			}
	}

	// gotoはここに飛ぶよ =========================================================== 
	
	end:

	// ==============================================================================

	random_toufu_time++;
	Input::GetInstance().Update();
	world->Update(deltaTime);
}

void GameMain::Draw() const {
	//renderer.DrawTexture(Assets::Texture::Background);
	world->Draw(renderer);
}

bool GameMain::IsEnd() const {
	return isEnd;
}

Scene GameMain::Next() const {
	return Scene::Result;
}

void GameMain::Finalize() {
	world->Finalize();
	renderer.Clear();
}

void GameMain::HandleMessage(EventMessage message, void * param)
{
	if (message == EventMessage::GameEnd || message == EventMessage::PlayerDead) {
		isEnd = true;
	}
}

