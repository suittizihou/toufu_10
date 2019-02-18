#include "Player2.h"
#include "Renderer/Renderer.h"
#include"Input/Input.h"
#include"Application/Window/Window.h"
#include"Collision/Collision2D/Box/Box.h"
#include "../Map/MapGenerater/MapGenerater.h"
#include "../PlayerManager/PlayerManager.h"


Player2::Player2(IWorld * world, const Vector2 & position, const int& _number, const float _speed, int input_pad, Character chara)
	: Actor2D(world, "player", position, std::make_shared<Box>(Vector2(-5, 75), Vector2(117, 149)), _number, _speed, input_pad, chara)
	, speed(_speed)
{
	actor_group = ActorGroup::Player2;
}

Player2::~Player2()
{
}

void Player2::OnInitialize()
{
	target_position = Input::GetInstance().GetMapDistanceMove_Arrow(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	position = target_position - Vector2(0.0f, 80.0f);
}

void Player2::OnFirstUpdate(float deltaTime)
{
	previous_target_position = target_position;
}

void Player2::OnUpdate(float deltaTime)
{
	// 止まっているとき動く
	if (move_state == MoveState::Stop) {
		target_position = Input::GetInstance().GetMapDistanceMove_Arrow(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y) - Vector2(0.0f, 80.0f);
		if ((target_position.x != previous_target_position.x) || (target_position.y != previous_target_position.y)) { move_state = MoveState::Move; }
	}
	if (move_state == MoveState::Stop)
	{
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_S))
		{
			bool aa = MapGenerater::check_toufu(center_pos, 0, 1);
			if (aa&&GetCharacter() == Character::Ninja) { direction = 0; }
			else { direction = 1; }
		}
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_W))
		{
			direction = 3;
		}
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_D))
		{
			direction = 2;
		}
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_A))
		{
			direction = 4;
		}
	}
	velocity = target_position - position;

	if (move_state == MoveState::Move) {
		if (velocity.Length() != 0) {
			// 正規化(Normalizeにバグあり)
			velocity = velocity / Math::SquareRoot(velocity.x * velocity.x + velocity.y * velocity.y);
			movement = velocity;
		}
		if (movement.y == 1)
		{
			direction = 1;
		}
		if (movement.y == -1)
		{
			direction = 3;
		}
		if (movement.x == 1)
		{
			direction = 2;
		}
		if (movement.x == -1)
		{
			direction = 4;
		}
	}

	position += movement * speed * deltaTime;

	// 目標座標と自分の座標の距離が5ドット以下
	if (target_position.Vector2::Distance(position) <= 5.0f) {
		movement = Vector2::Zero;
		position = target_position;
	}

	// 止まってない時は動いてるとする
	if (movement.Length() != 0) {
		move_state = MoveState::Move;
	}
	else {
		move_state = MoveState::Stop;
	}

	// マスの中心を入れる
	center_pos = Average_Position();

	collision = position.Clamp(Vector2(MapGenerater::map_spaceX, 0), Vector2(1016, 508));
}

void Player2::OnDraw(Renderer & renderer)
{
	time++;
	if (time > 5)
	{
		animeY += abs(movement.y);
		animeX += abs(movement.x);
		time = 0;
		if (animeY == 4)animeY = 0;
		if (animeX == 4)animeX = 0;
	}

	if (movement.y != 0)
	{
		beforeMovementY = movement.y;
	}

	if (movement.x != 0)
	{
		beforeMovementX = movement.x;
	}
	
	switch (GetCharacter())
	{
		case Character::Ninja:
			renderer.DrawTexture(Assets::Texture::Ninja_Icon2, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Ninja_point, Vector2(1155, 480 - 80 * i));
			}

			switch (direction)
			{
				case 0:
					renderer.DrawTexture(Assets::Texture::Ninja, position + Vector2(0, 73));
					break;
				case 1://前
					renderer.DrawRectangle(Assets::Texture::Ninja_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 2://右
					renderer.DrawRectangle(Assets::Texture::Ninja_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
				case 3://後ろ
					renderer.DrawRectangle(Assets::Texture::Ninja_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 4://左
					renderer.DrawRectangle(Assets::Texture::Ninja_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
			}
			break;

		case Character::Kinniku:
			renderer.DrawTexture(Assets::Texture::Kinniku_Icon2, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Kinniku_point, Vector2(1155, 480 - 80 * i));
			}

			switch (direction)
			{
				case 1://前
					renderer.DrawRectangle(Assets::Texture::Kinniku_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 2://右
					renderer.DrawRectangle(Assets::Texture::Kinniku_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
				case 3://後ろ
					renderer.DrawRectangle(Assets::Texture::Kinniku_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 4://左
					renderer.DrawRectangle(Assets::Texture::Kinniku_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
			}
			break;

		case Character::Yoroi:
			renderer.DrawTexture(Assets::Texture::Yoroi_Icon2, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Yoroi_point, Vector2(1155, 480 - 80 * i));
			}

			switch (direction)
			{
				case 1://前
					renderer.DrawRectangle(Assets::Texture::Yoroi_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 2://右
					renderer.DrawRectangle(Assets::Texture::Yoroi_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
				case 3://後ろ
					renderer.DrawRectangle(Assets::Texture::Yoroi_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 4://左
					renderer.DrawRectangle(Assets::Texture::Yoroi_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
			}
			break;


		case Character::Kakutouka:
			renderer.DrawTexture(Assets::Texture::Kakutouka_Icon2, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Kakutouka_point, Vector2(1155, 480 - 80 * i));
			}

			switch (direction)
			{
				case 1://前
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 2://右
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
				case 3://後ろ
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 4://左
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
			}
			break;
	}

#if _DEBUG
	//DrawFormatString(0, 16, GetColor(255, 0, 0), "positionX:%f positionY:%f", position.x, position.y);
	//DrawFormatString(0, 32, GetColor(255, 0, 0), "target_positionX:%f target_positionY:%f", target_position.x, target_position.y);
	//DrawFormatString(0, 48, GetColor(255, 0, 0), "Distance:%f", target_position.Vector2::Distance(position));
	//DrawFormatString(0, 64, GetColor(255, 0, 0), "numverX:%f　numverY:%f", MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	//DrawFormatString(0, 80, GetColor(255, 0, 0), "centerX:%f　centerY:%f", Average_Position().x, Average_Position().y);

	DrawFormatString(0, 16, GetColor(255, 0, 0), "Player2HP : %d", hp);
	DrawCircle(target_position.x, target_position.y, 3, GetColor(255, 0, 0));

	//DrawBox(position.x - 5, position.y + 75, position.x + 117, position.y + 149, GetColor(255, 0, 0), TRUE);
	//DrawPixel(Average_Position().x, Average_Position().y, GetColor(0, 255, 0));
#endif
}

// 二点間の平均値から中心座標を割り出す
Vector2 Player2::Average_Position() {
	Vector2 pos{ position.x + position.x + 112, position.y + 80 + position.y + 144 };
	return Vector2(pos.x / 2, pos.y / 2);
}

void Player2::OnFinalize()
{
	PlayerManager::SetP2Hp(hp, GetCharacter());
}

void Player2::OnMessage(EventMessage message, void * param)
{
}

void Player2::Damage() {
	--hp;
	// プレイヤーのhpをセット
	PlayerManager::SetP1Hp(hp, GetCharacter());

	if (hp <= 0) {
		world->SendEventMessage(EventMessage::PlayerDead);
		status = Status::Dead;
	}
	else {// hpが0じゃないならリスポーン
		int x = rand.Range(0, 7);
		int y = rand.Range(0, 7);
		// 豆腐が無かったら生成
		if (!MapGenerater::check_toufu(x, y)) {
			position = MapGenerater::up_left_get_pos(x, y);
			movement = Vector2::Zero;
			move_state = MoveState::Stop;
		}
	}
}

void Player2::OnCollide(const HitInfo & hitInfo)
{
	if (hitInfo.collideActor->GetName() == "NormalToufu") {
		move_state = MoveState::Move;
		movement = hitInfo.collideActor->GetMovement();
	}

	// 当たった豆腐がStopしてる豆腐、動いてる普通豆腐、鉄豆腐のどれかであり、かつ豆腐と自キャラの中心点との距離が66.0f以下である時ダメージを受ける
	if ((hitInfo.collideActor->GetName() == "StopNormalToufu" || hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "MetalToufu")
		&& hitInfo.collideActor->GetCenterPosition().Distance(center_pos) <= 66.0f) {

		Damage();
	}

	//if (hitInfo.collideActor->GetName() == "NormalToufu")
	//{
	//	// エネミーの座標を入れる
	//	Vector2 NormalToufu_pos = hitInfo.collideActor->GetVec2Position();

	//	// 自分の座標Xよりエネミーの座標Xが大きい かつ 動きが-1以下なら
	//	if (position.x < NormalToufu_pos.x && hitInfo.collideActor->GetMovement().x <= -1)
	//	{
	//		// 自分の座標に敵の移動量を加算
	//		position += hitInfo.collideActor->GetMovement();

	//		if (NormalToufu_pos.x - 187 < 113) {
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//			}l
	//		}
	//	}
	//	if (position.x > NormalToufu_pos.x&& hitInfo.collideActor->GetMovement().x >= 1) {
	//		position += hitInfo.collideActor->GetMovement();
	//		if (1016 - (NormalToufu_pos.x + 110) < 40) {
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//			}
	//		}
	//	}
	//	if (position.y < NormalToufu_pos.y&& hitInfo.collideActor->GetMovement().y <= -1)
	//	{
	//		position += hitInfo.collideActor->GetMovement();
	//		if (NormalToufu_pos.y - 3 < 45) {
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//			}
	//		}
	//	}
	//	if (position.y > NormalToufu_pos.y&& hitInfo.collideActor->GetMovement().y >= 1)
	//	{
	//		position += hitInfo.collideActor->GetMovement();
	//		if (508 - (NormalToufu_pos.y + 40) < 22) {
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//			}
	//		}
	//	}

	//}
	world->SendEventMessage(EventMessage::Hit);
}
