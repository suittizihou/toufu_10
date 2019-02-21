#include "Player.h"
#include "Renderer/Renderer.h"
#include"Input/Input.h"
#include"Application/Window/Window.h"
#include"Collision/Collision2D/Box/Box.h"
#include "../Map/MapGenerater/MapGenerater.h"
#include "../PlayerManager/PlayerManager.h"

Player::Player(IWorld * world, const Vector2 & position, const int& _number, const float _speed, int input_pad, Character chara)
	: Actor2D(world, "player", position, std::make_shared<Box>(Vector2(-5, 75), Vector2(117, 149)), _number, 5.0f, input_pad, chara)//Vector2(5, 76), Vector2(108, 118)
	, speed(5.0f)
{
	actor_group = ActorGroup::Player;

	if (chara == Character::Kinniku) { speed = 5.0f; }
	if (chara == Character::Kakutouka) { speed = 5.0f; }
	if (chara == Character::Ninja) { speed = 6.0f; }
	if (chara == Character::Yoroi) { speed = 3.0f; }
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


	if (move_state == MoveState::Move && !toufu_hit) {
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
	 

	//DrawCircle(target_position.x, target_position.y, 3, GetColor(0, 0, 255));
	//DrawFormatString(0, 32, GetColor(255, 0, 0), "Player1HP : %d", hp);

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
			PlayerManager::SetP1Hp(hp, GetCharacter());
			toufu_hit = false;
		}
	}
}

void Player::OnCollide(const HitInfo & hitInfo)
{
	//(5, 86), Vector2(108, 118) プレイヤーのサイズ
	//Vector2(182,3), Vector2(1016,509)P kabe
	//Vector2(0,80), Vector2(110,120)　豆腐のサイズ
	//Vector2(187, 31), Vector2(1013, 509) T kabe

	if ((hitInfo.collideActor->GetName() == "StopNormalToufu" || hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "MetalToufu")
		&& (hitInfo.collideActor->GetCenterPosition().Distance(center_pos) <= 66.0f)) {

		////movement = hitInfo.collideActor->GetMovement();

		if (TopHit(hitInfo.collideActor->GetVec2Position(), position)) { target_pos = Vector2(position.x, position.y + 1000.0f); }
		if (BottomHit(hitInfo.collideActor->GetVec2Position(), position)) { target_pos = Vector2(position.x, position.y - 1000.0f); }
		if (RightHit(hitInfo.collideActor->GetVec2Position(), position)) { target_pos = Vector2(position.x - 1000.0f, position.y); }
		if (LeftHit(hitInfo.collideActor->GetVec2Position(), position)) { target_pos = Vector2(position.x + 1000.0f, position.y); }

		if (!damage) {
			Vector2 temp{};
			if (TopHit(hitInfo.collideActor->GetCenterPosition(), center_pos)) {
				temp = Vector2(position.x, position.y + 1000.0f);
			}
			else if (BottomHit(hitInfo.collideActor->GetCenterPosition(), center_pos)) {
				temp = Vector2(position.x, position.y - 1000.0);
			}
			else if (RightHit(hitInfo.collideActor->GetCenterPosition(), center_pos)) {
				//temp = Vector2(position.x - 1000.0f, position.y);
				target_position = hitInfo.collideActor->GetTargetPosition() - Vector2(60.0f, 95.0f);
			}
			else if (LeftHit(hitInfo.collideActor->GetCenterPosition(), center_pos)) {
				temp = Vector2(position.x + 1000.0f, position.y);
			}

			target_position = temp/* - Vector2(112 / 2, 144 / 2)*/;
			damage = true;
			speed = 5.1f;
			move_state = MoveState::Move;
		}

		// 豆腐の中心点と自分の中心点が50ドット以下なら
		if (hitInfo.collideActor->GetCenterPosition().Distance(center_pos) <= 40.0f) {
			// ダメージ
			Damage();
			PlaySoundMem(hitSh, DX_PLAYTYPE_BACK);
			seflag = 0;
			damage = false;
		}

		seflag += 1;

		if (seflag == 1) {
			PlaySoundMem(hitSh, DX_PLAYTYPE_BACK);
		}

		speed = 5.1f;
		move_state = MoveState::Move;

	}
	world->SendEventMessage(EventMessage::Hit);
}

/// <summary>
/// 自身を基準としたターゲットの中心点との角度
/// </summary>
/// <param name="targetPos">ターゲットオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <returns></returns>
float Player::GetDegree(Vector2 targetposition, Vector2 thisposition)
{
	Vector2 dif = thisposition - targetposition;

	float radian = std::atan2(dif.y, dif.x);

	float degree = radian * Math::toDegree;

	return -degree;
}

// 上に当たったか
bool Player::TopHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * Math::toDegree;

	return degree >= 89.0f && degree <= 91.0f;
}

/// <summary)
/// 下に当たったか
/// </summary>
/// <param name="targetObject">ターゲットのオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <param name="sub">角度を指定された度数狭める</param>
/// <returns></returns>
bool Player::BottomHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * 180.0f / DX_PI;

	return degree <= -89.0f && degree >= -91.0f;
}

/// <summary>
/// 左に当たったか
/// </summary>
/// <param name="targetObject">ターゲットのオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <returns></returns>
bool Player::LeftHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * 180.0f / DX_PI;

	return degree >= -1.0f && degree <= 1.0f;
}

/// <summary>
/// 右に当たったか
/// </summary>
/// <param name="targetObject">ターゲットのオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <returns></returns>
bool Player::RightHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * 180.0f / DX_PI;

	return degree <= -178.0f;
}

/// <summary>
/// 左右のヒット判定をまとめたもの
/// </summary>
/// <param name="targetObject"></param>
/// <param name="thisObject"></param>
/// <param name="sub"></param>
/// <returns></returns>
bool Player::L_R_Hit(Vector2 targetposition, Vector2 thisposition)
{
	return LeftHit(targetposition, thisposition) || RightHit(targetposition, thisposition);
}

/// <summary>
/// 上下のヒット判定をまとめたもの
/// </summary>
/// <param name="targetObject"></param>
/// <param name="thisObject"></param>
/// <param name="sub"></param>
/// <returns></returns>
bool Player::T_B_Hit(Vector2 targetposition, Vector2 thisposition)
{
	return TopHit(targetposition, thisposition) || BottomHit(targetposition, thisposition);
}
