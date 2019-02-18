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
	renderer.LoadTexture(Assets::Texture::Background, "gameplay/gameplay.png");
	renderer.LoadTexture(Assets::Texture::NormalTile, "gameplay/normalTile.png");
	renderer.LoadTexture(Assets::Texture::Hole, "gameplay/hole.png");
	renderer.LoadTexture(Assets::Texture::NormalToufuTile, "gameplay/normalToufuTile.png");
	renderer.LoadTexture(Assets::Texture::MetalToufuTile, "gameplay/metalToufuTile.png");
	renderer.LoadTexture(Assets::Texture::RedTile, "gameplay/redTile.png");
	renderer.LoadTexture(Assets::Texture::BlueTile, "gameplay/blueTile.png");
	//renderer.LoadTexture(Assets::Texture::Player, "player.png");
	//renderer.LoadTexture(Assets::Texture::Player2, "player.png");

	//�E�҂̃e�N�X�`��
	renderer.LoadTexture(Assets::Texture::Ninja, "gameplay/player3.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Back,"gameplay/player3-2.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Front_Anime, "gameplay/player3_anime_walk_front.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Back_Anime, "gameplay/player3_anime_walk_back.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Left_Anime, "gameplay/player3_anime_walk_left.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Right_Anime, "gameplay/player3_anime_walk_right.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Icon, "gameplay/player1_cara3A.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Icon_Cry, "gameplay/player1_cara3B.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Icon2, "gameplay/player2_cara3A.png");
	renderer.LoadTexture(Assets::Texture::Ninja_Icon_Cry2, "gameplay/player2_cara3B.png");
	renderer.LoadTexture(Assets::Texture::Ninja_point, "gameplay/point2.png");
	//�����܂ŔE��

	//��������ؓ�
	renderer.LoadTexture(Assets::Texture::Kinniku, "gameplay/player1.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Back, "gameplay/player1-2.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Front_Anime, "gameplay/player1_anime_walk.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Back_Anime, "gameplay/player1_anime_walk2.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Left_Anime, "gameplay/player1_anime_walk3.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Right_Anime, "gameplay/player1_anime_walk4.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Icon, "gameplay/player1_cara1A.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Icon_Cry, "gameplay/player1_cara1B.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Icon2, "gameplay/player2_cara1A.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_Icon_Cry2, "gameplay/player2_cara1B.png");
	renderer.LoadTexture(Assets::Texture::Kinniku_point, "gameplay/point.png");
	//�����܂ŋؓ�

	//��������Z
	renderer.LoadTexture(Assets::Texture::Yoroi, "gameplay/player4.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Back, "gameplay/player4-2.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Front_Anime, "gameplay/player4_anime_walk.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Back_Anime, "gameplay/player4_anime_walk2.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Left_Anime, "gameplay/player4_anime_walk3.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Right_Anime, "gameplay/player4_anime_walk4.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Icon, "gameplay/player1_cara4A.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Icon_Cry, "gameplay/player1_cara4B.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Icon2, "gameplay/player2_cara4A.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_Icon_Cry2, "gameplay/player2_cara4B.png");
	renderer.LoadTexture(Assets::Texture::Yoroi_point, "gameplay/point4.png");
	//�����܂ŊZ

	//��������i����
	renderer.LoadTexture(Assets::Texture::Kakutouka, "gameplay/player2.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Back, "gameplay/player2-2.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Front_Anime, "gameplay/player2_anime_walk.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Back_Anime, "gameplay/player2_anime_walk2.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Left_Anime, "gameplay/player2_anime_walk3.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Right_Anime, "gameplay/player2_anime_walk4.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Icon, "gameplay/player1_cara2A.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Icon_Cry, "gameplay/player1_cara2B.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Icon2, "gameplay/player2_cara2A.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_Icon_Cry2, "gameplay/player2_cara2B.png");
	renderer.LoadTexture(Assets::Texture::Kakutouka_point, "gameplay/point3.png");
	//�����܂Ŋi����

	//renderer.LoadTexture(Assets::Texture::Player2, "player_atari.jpg");
	renderer.LoadTexture(Assets::Texture::NormalToufu, "gameplay/tofu.png");
	renderer.LoadTexture(Assets::Texture::MetalToufu, "gameplay/iron_tofu.png");
	renderer.LoadTexture(Assets::Texture::Number, "number.png");
}

void GameMain::Initialize() {
	world->GetSceneShareValue().Initialize();
	world->Initialize();

	//// �}�b�v�`�b�v���A�N�^�[�ɂ܂Ƃ߂ēo�^
	mapGenerater.AddMapChip();

	world->AddActor_Back(ActorGroup::NormalToufu, std::make_shared<Player>(world.get(), Vector2::Zero, objNumber, 5.0f, DX_INPUT_PAD1, CharacterManager::GetCharacterP1()));
	objNumber++;
	world->AddActor_Back(ActorGroup::NormalToufu, std::make_shared<Player2>(world.get(), mapGenerater.up_left_get_pos(7, 7) - Vector2(0, 58.0f), objNumber, 5.0f, DX_INPUT_PAD2, CharacterManager::GetCharacterP2()));
	objNumber++;
	//world->AddActor_Back(ActorGroup::UI, std::make_shared<Score>(world.get()));
	world->AddActor_Back(ActorGroup::UI, std::make_shared<TimerUI>(world.get(),1 * 60000,0));
	objNumber++;
	Random rand;
	for (int i = 0; i < 3;) {
		int x = rand.Range(0, 7);
		int y = rand.Range(0, 7);//Vector2(187, 31)

		// 0��7�̔z��ԍ��̎��m����������
		if (x == 0 || y == 0 || x == 7 || y == 7) {
			// 30%�̊m���Ń��Z�b�g
			if (rand.Range(0, 10) <= 7) { continue; }
		}
		// x��y�ǂ����0�̏ꍇ�����͗����Ȃ� || x��y�ǂ����7�̏ꍇ�����͗����Ȃ�
		if (x == 0 && y == 0 || x == 7 && y == 7) { continue; }
		// ���������������琶��
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

		// 0��7�̔z��ԍ��̎��m����������
		if (x == 0 || y == 0 || x == 7 || y == 7) {
			// 70%�̊m���Ń��Z�b�g
			if (rand.Range(0, 10) <= 7) { continue; }
		}
		// x��y�ǂ����0�̏ꍇ�����͗����Ȃ� || x��y�ǂ����7�̏ꍇ�����͗����Ȃ�
		if (x == 0 && y == 0 || x == 7 && y == 7) { continue; }
		// ���������������琶��
		if (mapGenerater.check_toufu(x, y)) { continue; }
			world->AddActor_Back(ActorGroup::NormalToufu,
			std::make_shared<MetalToufu>(world.get(),
			mapGenerater.up_left_get_pos(x, y) + Vector2(1.0f, -57.0f),
			objNumber,
			FALSE));
			mapGenerater.set_map_toufu(x, y, ToufuID::Metal);
			objNumber++;
			++i;
	}

	isEnd = false;

	//!���[���h�̃C�x���g���b�Z�[�W���󂯎��
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

void GameMain::AddToufu() {

	if (random_toufu_time > toufu_spone_limit/* && 20 > MapGenerater::get_toufu_value()*/)
	{
		Random rand;

		int x{};
		int y{};

		// 15�b�ȏ�o�߂����炱��������
		if (random_toufu_time >= 900) {
			x = RandomJudge(0, 7);
			y = RandomJudge(0, 7);
		}// 5�Ŋ���؂�鐔���Ȃ烉���_������
		else if (random_toufu_time % 5 == 0) {
			x = rand.Range(1, 6);
			y = rand.Range(1, 6);
		}

		// 0��7�̔z��ԍ��̎��m����������
		if (x == 0 || y == 0 || x == 7 || y == 7) {
			// 70%�̊m���Ń��Z�b�g
			if (rand.Range(0, 10) <= 7) { return; }
		}
		// x��y�ǂ����0�̏ꍇ�����͗����Ȃ� || x��y�ǂ����7�̏ꍇ�����͗����Ȃ�
		if (x == 0 && y == 0 || x == 7 && y == 7) { return; }
		// ���������������琶��
		if (mapGenerater.check_toufu(x, y)) { return; }
		if (rand.Range(0, 10) == 0) {
			world->AddActor_Back(ActorGroup::NormalToufu,
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
}

void GameMain::Update(float deltaTime) {

	// �����ǉ������[
	AddToufu();

	random_toufu_time++;
	Input::GetInstance().Update();
	world->Update(deltaTime);
	world->sort(ActorGroup::NormalToufu);
}

void GameMain::Draw() const {
	renderer.DrawTexture(Assets::Texture::Background);
	DrawFormatString(0, 48, GetColor(255, 0, 0), "toufu : %d", MapGenerater::get_toufu_value());
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

