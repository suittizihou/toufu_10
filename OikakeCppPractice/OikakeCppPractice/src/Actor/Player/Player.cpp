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
}

Player::~Player()
{
}

void Player::OnInitialize()
{ 
	//target_position = Input::GetInstance().GetMapDistanceMove_Pad1(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	target_position = Input::GetInstance().GetMapDistanceMove_Pad1(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	position = target_position - Vector2(0.0f, 80.0f);
}

void Player::OnUpdate(float deltaTime)
{
	// 止まっているとき && 豆腐に押されてない時動く
	if (Input::GetInstance().move_state == MoveState::Stop && !toufu_hit) {
		target_position = Input::GetInstance().GetMapDistanceMove_WASD(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y) - Vector2(0.0f, 80.0f);
		//target_position = Input::GetInstance().GetMapDistanceMove_Pad1(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y) - Vector2(0.0f, 80.0f);
	
	}

	//if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::A)) {
	//	DrawBox(position.x - 5, position.y + 75, position.x + 117, position.y + 149, GetColor(255, 0, 0), TRUE);
	//}

	velocity = target_position - position;

	if (Input::GetInstance().move_state == MoveState::Move) {
		if (velocity.Length() != 0) {
			// 正規化(Normalizeにバグあり)
			velocity = velocity / Math::SquareRoot(velocity.x * velocity.x + velocity.y * velocity.y);
			movement = velocity;
		}
	}

	position += movement * speed * deltaTime;

	// 目標座標と自分の座標の距離が5ドット以下
	if (target_position.Vector2::Distance(position) <= 5.0f) {
		Input::GetInstance().move_state = MoveState::Stop;
		movement = Vector2::Zero;
		position = target_position;
	}

	// マスの中心を入れる
	center_pos = Average_Position();
	
	collision = position.Clamp(Vector2(MapGenerater::map_spaceX, 0), Vector2(1016,508));
}

void Player::OnDraw(Renderer & renderer)
{
	time++;
	if (time > 5)
	{
		animeX++;
		time = 0;
		if (animeX == 4)animeX = 0;
	}

	if (GetCharacter() == Character::Ninja) {
		renderer.DrawRectangle(Assets::Texture::Ninja_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
	}
	else if (GetCharacter() == Character::Kinniku) {
		renderer.DrawTexture(Assets::Texture::Kinniku, position);
	}
	else if (GetCharacter() == Character::Yoroi) {
		renderer.DrawTexture(Assets::Texture::Yoroi, position);
	}
	else if (GetCharacter() == Character::Kakutouka) {
		renderer.DrawTexture(Assets::Texture::Kakutouka, position);
	}
	
#if _DEBUG
	//DrawFormatString(0, 16, GetColor(255, 0, 0), "positionX:%f positionY:%f", position.x, position.y);
	//DrawFormatString(0, 32, GetColor(255, 0, 0), "target_positionX:%f target_positionY:%f", target_position.x, target_position.y);
	//DrawFormatString(0, 48, GetColor(255, 0, 0), "Distance:%f", target_position.Vector2::Distance(position));
	//DrawFormatString(0, 64, GetColor(255, 0, 0), "numverX:%f　numverY:%f", MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	//DrawFormatString(0, 80, GetColor(255, 0, 0), "centerX:%f　centerY:%f", Average_Position().x, Average_Position().y);

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
}

void Player::OnCollide(const HitInfo & hitInfo)
{
	//(5, 86), Vector2(108, 118) プレイヤーのサイズ
	//Vector2(182,3), Vector2(1016,509)P kabe
	//Vector2(0,80), Vector2(110,120)　豆腐のサイズ
	//Vector2(187, 31), Vector2(1013, 509) T kabe
	toufu_hit = false;
	if (hitInfo.collideActor->GetName() == "SponeNormalToufu") {
		Damage();
	}
	if (hitInfo.collideActor->GetName() == "NormalToufu")
	{
		toufu_hit = true;
		// エネミーの座標を入れる
		Vector2 enemy_pos = hitInfo.collideActor->GetVec2Position();

		// 自分の座標Xよりエネミーの座標Xが大きい かつ 動きが-1以下なら
		if (position.x < enemy_pos.x && hitInfo.collideActor->GetMovement().x <= -1)
		{
			// 自分の座標に敵の移動量を加算
			position += hitInfo.collideActor->GetMovement();

			if (enemy_pos.x - 187 < 113) { 
				int x = rand.Range(0, 7);
				int y = rand.Range(0, 7);
				// 豆腐が無かったら生成
				if (!MapGenerater::check_toufu(x, y)) {
					position = MapGenerater::up_left_get_pos(x, y);
					Damage();
				}
			}
		}
		if (position.x > enemy_pos.x&& hitInfo.collideActor->GetMovement().x >= 1) {
			position += hitInfo.collideActor->GetMovement();
			if (1016 - (enemy_pos.x + 110) < 40) {
				int x = rand.Range(0, 7);
				int y = rand.Range(0, 7);
				// 豆腐が無かったら生成
				if (!MapGenerater::check_toufu(x, y)) {
					position = MapGenerater::up_left_get_pos(x, y);
					Damage();
				}
			}
		}
		if (position.y < enemy_pos.y&& hitInfo.collideActor->GetMovement().y <= -1)
		{
			position += hitInfo.collideActor->GetMovement();
			if (enemy_pos.y - 3 < 45) {
				int x = rand.Range(0, 7);
				int y = rand.Range(0, 7);
				// 豆腐が無かったら生成
				if (!MapGenerater::check_toufu(x, y)) {
					position = MapGenerater::up_left_get_pos(x, y);
					Damage();
				}
			}
		}
		if (position.y > enemy_pos.y&& hitInfo.collideActor->GetMovement().y >= 1)
		{
			position += hitInfo.collideActor->GetMovement();
			if (508 - (enemy_pos.y + 40) < 22) {
				int x = rand.Range(0, 7);
				int y = rand.Range(0, 7);
				// 豆腐が無かったら生成
				if (!MapGenerater::check_toufu(x, y)) {
					position = MapGenerater::up_left_get_pos(x, y);
					Damage();
				}
			}
		}

	}
	world->SendEventMessage(EventMessage::Hit);
}
/*
総当たりで全部見て
範囲に入ってるかどうかを見て
範囲に入っていたら押した方向の
配列をみてあったらその配列の壁を
なかったら自分の立っている
配列の壁を取得
*/
/*
豆腐にぶつかる
豆腐が移動中だったら
プレイヤーにポジションをプラス
その間操作は受け付けないように遮断する
壁に触れたら死ぬ
*/