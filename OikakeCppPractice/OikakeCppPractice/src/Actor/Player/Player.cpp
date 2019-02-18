#include "Player.h"
#include "Renderer/Renderer.h"
#include"Input/Input.h"
#include"Application/Window/Window.h"
#include"Collision/Collision2D/Box/Box.h"
#include "../Map/MapGenerater/MapGenerater.h"
#include "../PlayerManager/PlayerManager.h"

Player::Player(IWorld * world, const Vector2 & position, const int& _number, const float _speed, int input_pad, Character chara)
	: Actor2D(world, "player", position, std::make_shared<Box>(Vector2(-5, 75), Vector2(117, 149)), _number, _speed, input_pad, chara)//Vector2(5, 76), Vector2(108, 118)
	, speed(_speed)
{
	actor_group = ActorGroup::Player;
}

Player::~Player()
{
}

void Player::OnInitialize()
{ 
	//target_position = Input::GetInstance().GetMapDistanceMove_WASD(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	target_position = Input::GetInstance().GetMapDistanceMove_Pad1(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	//target_position = Input::GetInstance().GetMapDistanceMove_WASD(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	position = target_position - Vector2(0.0f, 80.0f);
	firstDraw = true;

	hitSh = LoadSoundMem("asset/BGM&SE/gameplay_ataru_se.mp3");
}

void Player::OnFirstUpdate(float deltaTime)
{
	// 今のターゲットポジションを入れて取っておく
	previous_target_position = target_position;
}

void Player::OnUpdate(float deltaTime)
{
	// 止まっているとき && 豆腐に押されてない時動く
	if (move_state == MoveState::Stop && !toufu_hit) {
		//target_position = Input::GetInstance().GetMapDistanceMove_WASD(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y) - Vector2(0.0f, 80.0f);
		target_position = Input::GetInstance().GetMapDistanceMove_Pad1(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y) - Vector2(0.0f, 80.0f);	
		if ((target_position.x != previous_target_position.x) || (target_position.y != previous_target_position.y)) {move_state = MoveState::Move;}
	}

	if (move_state == MoveState::Stop)
	{
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_S)|| Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Down))
		{
			bool aa = MapGenerater::check_toufu(center_pos, 0, 1);
			if (aa&&GetCharacter()== Character::Ninja) { direction = 0; }
			else { direction = 1; }
		}
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_W) || Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Up))
		{
			direction = 3;
		}
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_D) || Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Right))
		{
			direction = 2;
		}
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_A) || Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Left))
		{
			direction = 4;
		}
	}


	if (move_state == MoveState::Move) {
		velocity = target_position - position;
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
		move_state = MoveState::Stop;
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
	
	collision = position.Clamp(Vector2(MapGenerater::map_spaceX, 0), Vector2(1016,508));

}

float distance{};

void Player::OnDraw(Renderer & renderer)
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

		if (movement.y != 0) {
			beforeMovementY = movement.y;
		}

		if (movement.x != 0) {
			beforeMovementX = movement.x;
		}


		switch (GetCharacter())
		{
		case Character::Ninja:
			renderer.DrawTexture(Assets::Texture::Ninja_Icon, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Ninja_point, Vector2(30,190 + 80*i));
			}

			switch (direction)
			{
			case 0:
				renderer.DrawTexture(Assets::Texture::Ninja, position + Vector2(0,73));
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
			renderer.DrawTexture(Assets::Texture::Kinniku_Icon, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Kinniku_point, Vector2(30, 190 + 80 * i));
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
			renderer.DrawTexture(Assets::Texture::Yoroi_Icon, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Yoroi_point, Vector2(30, 190 + 80 * i));
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
			renderer.DrawTexture(Assets::Texture::Kakutouka_Icon, Vector2(0, 0));
			for (int i = 0; i < hp; i++)
			{
				renderer.DrawTexture(Assets::Texture::Kakutouka_point, Vector2(30, 190 + 80 * i));
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
	//DrawFormatString(0, 80, GetColor(255, 0, 0), "movementX:%f　movementY:%f", movement.x, movement.y);
	 

	DrawCircle(target_position.x, target_position.y, 3, GetColor(0, 0, 255));
	DrawFormatString(0, 32, GetColor(255, 0, 0), "Player1HP : %d", hp);

	//DrawBox(position.x - 5, position.y + 75, position.x + 117, position.y + 149, GetColor(255, 0, 0), TRUE);
	//DrawBox(position.x, position.y, position.x + 117, position.y + 149, GetColor(255, 0, 0), TRUE);
	//DrawPixel(Average_Position().x, Average_Position().y, GetColor(0, 255, 0));
#endif
}

// 二点間の平均値から中心座標を割り出す
Vector2 Player::Average_Position() {
	Vector2 pos{ position.x + position.x + 112, position.y + 80 + position.y + 144};
	return Vector2(pos.x / 2, pos.y / 2);
}

void Player::OnFinalize()
{
}

void Player::OnMessage(EventMessage message, void * param)
{
}

void Player::Damage() {
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
			movement = Vector2::Zero;
			Vector2 respawn_position{ MapGenerater::up_left_get_pos(x, y) };
			target_position = respawn_position;
			position = respawn_position;
			speed = 5.0f;
		}
	}
}

void Player::OnCollide(const HitInfo & hitInfo)
{
	//(5, 86), Vector2(108, 118) プレイヤーのサイズ
	//Vector2(182,3), Vector2(1016,509)P kabe
	//Vector2(0,80), Vector2(110,120)　豆腐のサイズ
	//Vector2(187, 31), Vector2(1013, 509) T kabe

	toufu_hit = false;

	if ((hitInfo.collideActor->GetName() == "StopNormalToufu" || hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "MetalToufu")
		&& (hitInfo.collideActor->GetCenterPosition().Distance(center_pos) <= 66.0f)) {

		target_position = hitInfo.collideActor->GetTargetPosition() - Vector2(60.0f, 95.0f);
		//movement = hitInfo.collideActor->GetMovement();
		speed = 5.1f;
		move_state = MoveState::Move;

		seflag += 1;

		if (seflag == 1) {
			PlaySoundMem(hitSh, DX_PLAYTYPE_BACK);
		}

		// 豆腐の中心点と自分の中心点が60ドット以下なら
		if (hitInfo.collideActor->GetCenterPosition().Distance(center_pos) <= 60.0f) {
			// damage
			Damage();
			PlaySoundMem(hitSh, DX_PLAYTYPE_BACK);
			seflag = 0;
		}
	}

	//if (hitInfo.collideActor->GetName() == "NormalToufu")
	//{
	//	toufu_hit = true;
	//	// エネミーの座標を入れる
	//	Vector2 enemy_pos = hitInfo.collideActor->GetVec2Position();

	//	// 自分の座標Xよりエネミーの座標Xが大きい かつ 動きが-1以下なら
	//	if (position.x < enemy_pos.x && hitInfo.collideActor->GetMovement().x <= -1)
	//	{
	//		// 自分の座標に敵の移動量を加算
	//		position += hitInfo.collideActor->GetMovement();

	//		if (enemy_pos.x - 187 < 113) { 
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//				Damage();
	//			}
	//		}
	//	}
	//	if (position.x > enemy_pos.x&& hitInfo.collideActor->GetMovement().x >= 1) {
	//		position += hitInfo.collideActor->GetMovement();
	//		if (1016 - (enemy_pos.x + 110) < 40) {
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//				Damage();
	//			}
	//		}
	//	}
	//	if (position.y < enemy_pos.y&& hitInfo.collideActor->GetMovement().y <= -1)
	//	{
	//		position += hitInfo.collideActor->GetMovement();
	//		if (enemy_pos.y - 3 < 45) {
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//				Damage();
	//			}
	//		}
	//	}
	//	if (position.y > enemy_pos.y&& hitInfo.collideActor->GetMovement().y >= 1)
	//	{
	//		position += hitInfo.collideActor->GetMovement();
	//		if (508 - (enemy_pos.y + 40) < 22) {
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// 豆腐が無かったら生成
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//				Damage();
	//			}
	//		}
	//	}

	//}
	world->SendEventMessage(EventMessage::Hit);
}
