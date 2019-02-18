#include "NormalToufu.h"
#include <windows.h>
#include <sstream>

#include"Renderer/Renderer.h"
#include"Collision/Collision2D/Box/Box.h"
#include"Utility/Random/Random.h"
#include"Application/Window/Window.h"
#include "Actor/Map/MapGenerater/MapGenerater.h"
#include "../ToufuID.h"
#include "Input/Input.h"

NormalToufu::NormalToufu(IWorld* world, const Vector2& position_, const int& _number)
	: Actor2D(world, "SponeNormalToufu", position_, std::make_shared<Box>(Vector2(0, 57), Vector2(110, 120)), _number)
{
	sponed_pos = position_;
	actor_group = ActorGroup::NormalToufu;
	MapGenerater::set_map_toufu(Average_Position(position), ToufuID::Normal);
	spone_position = Vector2(position.x, -128.0f);
	spone_move = NormalToufuMove::SponeMove;

	default_position = position_;
	position = spone_position;
}

NormalToufu::~NormalToufu()
{
}

void NormalToufu::OnInitialize()
{
	dropSh = LoadSoundMem("asset/BGM&SE/gameplay_drop_se.mp3");
	punchSh = LoadSoundMem("asset/BGM&SE/gameplay_punch_se.mp3");
}

void NormalToufu::OnFirstUpdate(float deltaTime)
{
	MapGenerater::set_map_toufu(Average_Position(position), ToufuID::Normal);
	// そこが穴なら自分は死んでノーマル豆腐のタイルにする
	if (MapGenerater::check_hole(center_pos)) {
		status = Status::Dead;
		MapGenerater::set_map_Texture(center_pos, Assets::Texture::NormalToufuTile);
	}
}

void NormalToufu::OnUpdate(float deltaTime)
{
	// 筋肉豆腐ムーブ中でない時
	if (!kinniku_move) {
		 // X、Yどちらかでも０でないなら
		if (moveX != 0 || moveY != 0) {
			target_pos = Input::GetInstance().PlayerHitToufuMove(center_pos, moveX, moveY) + Vector2(55, 30);
			kinniku_move = false;
		}
	}

	if (_move)
	{
		Move();
	}
	//one_time_position = position;

	if (spone_move == NormalToufuMove::SponeMove) {
		position.y += 10.0f;
	}
	if (default_position.y <= position.y && spone_move == NormalToufuMove::SponeMove) {
		spone_move = NormalToufuMove::SponeMoveStop;
		position = default_position;
		name = "StopNormalToufu";
	}
	if (spone_move == NormalToufuMove::SponeMoveStop && position.Clamp(MapGenerater::up_left_get_pos(0, 0) - Vector2(0, 58.0f), MapGenerater::up_left_get_pos(7, 7) - Vector2(0, 58.0f)))
	{
		_move = false;
		movement = Vector2::Zero;
	}
	if (spone_move == NormalToufuMove::SponeMoveStop && movement.Length() == 0.0f) {
		name = "StopNormalToufu";
	}
	else if (spone_move == NormalToufuMove::SponeMoveStop) {
		name = "NormalToufu";
	}


	//if (one_time_position.x == position.x && one_time_position.y == position.y) _move = false;

	center_pos = Average_Position(position);
}

void NormalToufu::OnDraw(Renderer & renderer)
{
	renderer.DrawTexture(Assets::Texture::NormalToufu, position);
	DrawBox(position.x, position.y + 57, position.x + 110, position.y + 120, GetColor(0, 255, 0), TRUE);
	//DrawPixel(target_pos.x, target_pos.y, GetColor(255, 0, 0));
	DrawCircle(center_pos.x, center_pos.y, 5, GetColor(0, 0, 255));
	if (name == "SponeNormalToufu") {
		DrawFormatString(center_pos.x, center_pos.y, GetColor(255, 255, 0), name.c_str());
	}
	else {
		DrawFormatString(center_pos.x, center_pos.y, GetColor(0, 255, 255), name.c_str());
	}
	DrawCircle(target_pos.x, target_pos.y, 5, GetColor(255, 0, 0));
	DrawFormatString(position.x, position.y, GetColor(255, 0, 0), "Length : %f", movement.Length());
	DrawFormatString(0, 32, GetColor(255, 0, 0), "move : %d", _move);

	//float test = GetDegree(MapGenerater::up_left_get_pos(5, 5), Average_Position());

	//DrawFormatString(0, 96, GetColor(255, 0, 0), "agree : %f", test);
}

Vector2 NormalToufu::Average_Position(const Vector2 & position) {
	Vector2 pos{ position.x + position.x + 110, position.y + 57 + position.y + 120 };
	return Vector2(pos.x / 2, pos.y / 2);
}

void NormalToufu::OnFinalize()
{
}

void NormalToufu::OnMessage(EventMessage message, void* param)
{
}

void NormalToufu::Move()
{
	if (target_pos.Vector2::Distance(center_pos) <= 5.0f) {
		movement = Vector2::Zero;
		position = target_pos - Vector2(54, 87);
		moveX = 0;
		moveY = 0;
		target_pos = Vector2::Zero;
		_move = false;
	}
	else {
		position += movement;
	}
}

bool NormalToufu::GetBoolMove()
{
	return _move;
}

Vector2 Normalize(const Vector2 & velocity) {
	if (velocity.Length() == 0) { return velocity; }
	return velocity / Math::SquareRoot(velocity.x * velocity.x + velocity.y * velocity.y);
}

void NormalToufu::Damage(const HitInfo & hitInfo) {
	if (hitInfo.collideActor->GetCharacter() == Character::Kakutouka) {
		hp -= 2;
	}
	else {
		--hp;
	}

	if (hp <= 0) {
		MapGenerater::set_map_toufu(Average_Position(position), ToufuID::None);
		status = Status::Dead;
	}
}

// 上に当たっているとき
void NormalToufu::TopHitRiaction_1(const HitInfo & hitInfo)
{
	if (TopHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧豆腐じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Down) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_S)) {
				// Aボタン || Jボタンで押す
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					// 行きたい座標				 -						// 自分の今の座標
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;

					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Down) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_S)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// Aボタン || Jボタンで押す || Xボタン || Hボタンで押す(鎧豆腐の必殺技用)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					// 行きたい座標				 -						// 自分の今の座標
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void NormalToufu::TopHitRiaction_2(const HitInfo & hitInfo)
{
	if (TopHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧豆腐じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Down) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_DOWN)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Down) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_DOWN) ||
				(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
				// Aボタン || 1ボタンで押す || Xボタン || 3ボタンで押す(鎧豆腐の必殺技用)
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

// 下に当たっているとき
void NormalToufu::BottomHitRiaction_1(const HitInfo & hitInfo)
{
	if (BottomHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Up) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_W)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}

				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Up) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_W)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// Aボタン || Jボタンで押す || Xボタン || Hボタンで押す(鎧豆腐の必殺技用)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void NormalToufu::BottomHitRiaction_2(const HitInfo & hitInfo)
{
	// 下に当たっているとき
	if (BottomHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧豆腐じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Up) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_UP)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
			
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Up) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_UP) ||
				(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
				// Aボタン || 1ボタンで押す || Xボタン || 3ボタンで押す(鎧豆腐の必殺技用)
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

// 右に当たっているとき
void NormalToufu::RightHitRiaction_1(const HitInfo & hitInfo)
{
	// 右に当たっているとき
	if (RightHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧豆腐じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Left) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_A)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}

				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Left) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_A)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// Aボタン || Jボタンで押す || Xボタン || Hボタンで押す(鎧豆腐の必殺技用)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void NormalToufu::RightHitRiaction_2(const HitInfo & hitInfo)
{
	// 右に当たっているとき
	if (RightHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧豆腐じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Left) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_LEFT)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
			
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);

				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Left) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_LEFT) ||
				(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
				// Aボタン || 1ボタンで押す || Xボタン || 3ボタンで押す(鎧豆腐の必殺技用)
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}


// 左に当たっているとき
void NormalToufu::LeftHitRiaction_1(const HitInfo & hitInfo)
{
	// 左に当たっているとき
	if (LeftHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧豆腐じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Right) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_D)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Right) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_D)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// Aボタン || Jボタンで押す || Xボタン || Hボタンで押す(鎧豆腐の必殺技用)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void NormalToufu::LeftHitRiaction_2(const HitInfo & hitInfo)
{
	// 左に当たっているとき
	if (LeftHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// 鎧豆腐じゃない時
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Right) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_RIGHT)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Right) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_RIGHT) ||
				Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
				// Aボタン || 1ボタンで押す || Xボタン || 3ボタンで押す(鎧豆腐の必殺技用)
				if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// 殴られ
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}


void NormalToufu::OnCollide(const HitInfo & hitInfo)
{
	// 自分と同じ奴には当たらない
	if (hitInfo.collideActor->GetNumber() == this->GetNumber()) {
		return;
	}

	//if(hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "StopNormalToufu" || hitInfo)

	// 自身が筋肉豆腐押されていて、なおかつ当たった豆腐たちが普通の豆腐なら
	if (kinniku_move && (hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "StopNormalToufu"))
	{
		// 当たった豆腐を消す
		hitInfo.collideActor->ChangeStatus(Status::Dead);

		kinniku_move = false;
	}

	// 押す処理関連
	if (name != "SponeNormalToufu") { // 生まれたての豆腐じゃない時(豆腐が落ちきったら)
		if (/*hitInfo.collideActor->GetName() == "player" && */hitInfo.collideActor->GetControllerType() == DX_INPUT_PAD1 && !_move)
		{// プレイヤー１用

			// 上に当たっているとき
			TopHitRiaction_1(hitInfo);

			// 下に当たっているとき
			BottomHitRiaction_1(hitInfo);

			// 右に当たっているとき
			RightHitRiaction_1(hitInfo);

			// 左に当たっているとき
			LeftHitRiaction_1(hitInfo);

			if (movement.x != 0 || movement.y != 0)
			{
				_move = true;
			}
		}
		else if (/*hitInfo.collideActor->GetName() == "player" && */hitInfo.collideActor->GetControllerType() == DX_INPUT_PAD2 && !_move)
		{// プレイヤー２用

			// 上に当たっているとき
			TopHitRiaction_2(hitInfo);

			// 下に当たっているとき
			BottomHitRiaction_2(hitInfo);

			// 右に当たっているとき
			RightHitRiaction_2(hitInfo);

			// 左に当たっているとき
			LeftHitRiaction_2(hitInfo);

			if (movement.x != 0 || movement.y != 0)
			{
				_move = true;
			}
		}
	}

	// スコア(今回使ってないからなくてもいい)
	int score = 1;
	world->SendEventMessage(EventMessage::AddScore, &score);
}

/// <summary>
/// 自身を基準としたターゲットの中心点との角度
/// </summary>
/// <param name="targetPos">ターゲットオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <returns></returns>
float NormalToufu::GetDegree(Vector2 targetposition, Vector2 thisposition)
{
	Vector2 dif = thisposition - targetposition;

	float radian = std::atan2(dif.y, dif.x);

	float degree = radian * Math::toDegree;

	return -degree;
}

// 上に当たったか
bool NormalToufu::TopHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * Math::toDegree;

	std::ostringstream ss;

	ss << degree << std::endl;

	OutputDebugString(ss.str().c_str());

	return degree >= 89.0f && degree <= 91.0f;
}

/// <summary)
/// 下に当たったか
/// </summary>
/// <param name="targetObject">ターゲットのオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <param name="sub">角度を指定された度数狭める</param>
/// <returns></returns>
bool NormalToufu::BottomHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * 180.0f / DX_PI;

	std::ostringstream ss;

	ss << degree << std::endl;

	OutputDebugString(ss.str().c_str());

	return degree <= -89.0f && degree >= -91.0f;
}

/// <summary>
/// 左に当たったか
/// </summary>
/// <param name="targetObject">ターゲットのオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <returns></returns>
bool NormalToufu::LeftHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * 180.0f / DX_PI;

	std::ostringstream ss;

	ss << degree << std::endl;

	OutputDebugString(ss.str().c_str());

	return degree >= -1.0f && degree <= 1.0f;
}

/// <summary>
/// 右に当たったか
/// </summary>
/// <param name="targetObject">ターゲットのオブジェクト</param>
/// <param name="thisObject">自身</param>
/// <returns></returns>
bool NormalToufu::RightHit(Vector2 targetposition, Vector2 thisposition)
{
	float radian = std::atan2(thisposition.y - targetposition.y, thisposition.x - targetposition.x);
	float degree = radian * 180.0f / DX_PI;

	std::ostringstream ss;

	ss << degree << std::endl;

	OutputDebugString(ss.str().c_str());

	return degree <= -179.0f;
}

/// <summary>
/// 左右のヒット判定をまとめたもの
/// </summary>
/// <param name="targetObject"></param>
/// <param name="thisObject"></param>
/// <param name="sub"></param>
/// <returns></returns>
bool NormalToufu::L_R_Hit(Vector2 targetposition, Vector2 thisposition)
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
bool NormalToufu::T_B_Hit(Vector2 targetposition, Vector2 thisposition)
{
	return TopHit(targetposition, thisposition) || BottomHit(targetposition, thisposition);
}
float NormalToufu::LeftUpDegree() {

	//左上
		// 自身を基準としたターゲットオブジェクトが当たる可能性があるであろう一番左上の座標
	Vector2 targetLeftUpPos = Vector2(position.x - (112 / 2 + 110 / 2), position.y + (74 / 2 + 63 / 2));

	Vector2 dif = targetLeftUpPos - Vector2(position.x, position.y);

	// ラジアンを求める
	float radian = Math::ArcTan(dif.y, dif.x);

	// ラジアンを角度に変換
	float degree = radian * Math::toDegree;

	// 角度を返す
	return degree;

}
float NormalToufu::RightUpDegree() {
	//右上
		// 自身を基準としたターゲットオブジェクトが当たる可能性があるであろう一番右上の座標
	Vector2 targetRightUpPos = Vector2(position.x + (112 / 2 + 110 / 2), position.y + (74 / 2 + 63 / 2));

	Vector2 dif = targetRightUpPos - Vector2(position.x, position.y);

	float radian = Math::ArcTan(dif.y, dif.x);

	float degree = radian * Math::toDegree;

	return degree;
}
