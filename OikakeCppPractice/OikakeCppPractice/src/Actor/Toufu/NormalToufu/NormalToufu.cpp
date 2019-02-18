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
	pushSh = LoadSoundMem("asset/BGM&SE/gameplay_push_se.mp3");
}

void NormalToufu::OnFirstUpdate(float deltaTime)
{
	MapGenerater::set_map_toufu(Average_Position(position), ToufuID::Normal);
	// ���������Ȃ玩���͎���Ńm�[�}�������̃^�C���ɂ���
	if (MapGenerater::check_hole(center_pos)) {
		status = Status::Dead;
		PlaySoundMem(dropSh,DX_PLAYTYPE_BACK);
		MapGenerater::set_map_Texture(center_pos, Assets::Texture::NormalToufuTile);
	}
}

void NormalToufu::OnUpdate(float deltaTime)
{
	// �ؓ��������[�u���łȂ���
	if (!kinniku_move) {
		 // X�AY�ǂ��炩�ł��O�łȂ��Ȃ�
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

// ��ɓ������Ă���Ƃ�
void NormalToufu::TopHitRiaction_1(const HitInfo & hitInfo)
{
	if (TopHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// �Z��������Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Down) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_S)) {
				// A�{�^�� || J�{�^���ŉ���
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);


					// �s���������W				 -						// �����̍��̍��W
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;

					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Down) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_S)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// A�{�^�� || J�{�^���ŉ��� || X�{�^�� || H�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					// �s���������W				 -						// �����̍��̍��W
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
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
		// �Z��������Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Down) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_DOWN)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);
					
					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Down) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_DOWN) ||
				(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
				// A�{�^�� || 1�{�^���ŉ��� || X�{�^�� || 3�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, 1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = 1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

// ���ɓ������Ă���Ƃ�
void NormalToufu::BottomHitRiaction_1(const HitInfo & hitInfo)
{
	if (BottomHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// �Z����Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Up) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_W)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}

				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Up) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_W)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// A�{�^�� || J�{�^���ŉ��� || X�{�^�� || H�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void NormalToufu::BottomHitRiaction_2(const HitInfo & hitInfo)
{
	// ���ɓ������Ă���Ƃ�
	if (BottomHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// �Z��������Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Up) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_UP)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
			
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Up) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_UP) ||
				(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
				// A�{�^�� || 1�{�^���ŉ��� || X�{�^�� || 3�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 0, -1) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 0;
					moveY = -1;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

// �E�ɓ������Ă���Ƃ�
void NormalToufu::RightHitRiaction_1(const HitInfo & hitInfo)
{
	// �E�ɓ������Ă���Ƃ�
	if (RightHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// �Z��������Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Left) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_A)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}

				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Left) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_A)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// A�{�^�� || J�{�^���ŉ��� || X�{�^�� || H�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void NormalToufu::RightHitRiaction_2(const HitInfo & hitInfo)
{
	// �E�ɓ������Ă���Ƃ�
	if (RightHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// �Z��������Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Left) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_LEFT)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
			
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);

				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Left) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_LEFT) ||
				(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
				// A�{�^�� || 1�{�^���ŉ��� || X�{�^�� || 3�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, -1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = -1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}


// ���ɓ������Ă���Ƃ�
void NormalToufu::LeftHitRiaction_1(const HitInfo & hitInfo)
{
	// ���ɓ������Ă���Ƃ�
	if (LeftHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// �Z��������Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Right) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_D)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if ((Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::Dpad_Right) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_D)) ||
				(Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H))) {
				// A�{�^�� || J�{�^���ŉ��� || X�{�^�� || H�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if (Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_J) ||
					Input::GetInstance().GetXBoxController().IsButtonState(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_H)) {

					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_K)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void NormalToufu::LeftHitRiaction_2(const HitInfo & hitInfo)
{
	// ���ɓ������Ă���Ƃ�
	if (LeftHit(hitInfo.collideActor->GetCenterPosition(), Average_Position(position))) {
		// �Z��������Ȃ���
		if (hitInfo.collideActor->GetCharacter() != Character::Yoroi) {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Right) ||
				Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_RIGHT)) {
				if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1)) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
					if (hitInfo.collideActor->GetCharacter() == Character::Kinniku) { kinniku_move = true; }
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
		else {
			if (Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Right) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_RIGHT) ||
				Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)) {
				// A�{�^�� || 1�{�^���ŉ��� || X�{�^�� || 3�{�^���ŉ���(�Z�����̕K�E�Z�p)
				if ((Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::A) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_1) ||
					(Input::GetInstance().GetXBoxController().IsButtonState2(XboxGamePad::X) || Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_3)))) {
					
					//��������
					PlaySoundMem(pushSh, DX_PLAYTYPE_BACK);

					movement = Normalize(Input::GetInstance().PlayerHitToufuMove(center_pos, 1, 0) - MapGenerater::up_left_get_pos(center_pos)) * hitInfo.collideActor->GetSpeed();
					moveX = 1;
					moveY = 0;
				}
				else if (Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::B) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_2)) {
					// �����
					Damage(hitInfo);
					PlaySoundMem(punchSh, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}


void NormalToufu::OnCollide(const HitInfo & hitInfo)
{
	// �����Ɠ����z�ɂ͓�����Ȃ�
	if (hitInfo.collideActor->GetNumber() == this->GetNumber()) {
		return;
	}

	//if(hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "StopNormalToufu" || hitInfo)

	// ���g���ؓ�����������Ă��āA�Ȃ������������������������ʂ̓����Ȃ�
	if (kinniku_move && (hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "StopNormalToufu"))
	{
		// ������������������
		hitInfo.collideActor->ChangeStatus(Status::Dead);

		kinniku_move = false;
	}

	// ���������֘A
	if (name != "SponeNormalToufu") { // ���܂ꂽ�Ă̓�������Ȃ���(������������������)
		if (/*hitInfo.collideActor->GetName() == "player" && */hitInfo.collideActor->GetControllerType() == DX_INPUT_PAD1 && !_move)
		{// �v���C���[�P�p

			// ��ɓ������Ă���Ƃ�
			TopHitRiaction_1(hitInfo);

			// ���ɓ������Ă���Ƃ�
			BottomHitRiaction_1(hitInfo);

			// �E�ɓ������Ă���Ƃ�
			RightHitRiaction_1(hitInfo);

			// ���ɓ������Ă���Ƃ�
			LeftHitRiaction_1(hitInfo);

			if (movement.x != 0 || movement.y != 0)
			{
				_move = true;
			}
		}
		else if (/*hitInfo.collideActor->GetName() == "player" && */hitInfo.collideActor->GetControllerType() == DX_INPUT_PAD2 && !_move)
		{// �v���C���[�Q�p

			// ��ɓ������Ă���Ƃ�
			TopHitRiaction_2(hitInfo);

			// ���ɓ������Ă���Ƃ�
			BottomHitRiaction_2(hitInfo);

			// �E�ɓ������Ă���Ƃ�
			RightHitRiaction_2(hitInfo);

			// ���ɓ������Ă���Ƃ�
			LeftHitRiaction_2(hitInfo);

			if (movement.x != 0 || movement.y != 0)
			{
				_move = true;
			}
		}
	}

	// �X�R�A(����g���ĂȂ�����Ȃ��Ă�����)
	int score = 1;
	world->SendEventMessage(EventMessage::AddScore, &score);
}

/// <summary>
/// ���g����Ƃ����^�[�Q�b�g�̒��S�_�Ƃ̊p�x
/// </summary>
/// <param name="targetPos">�^�[�Q�b�g�I�u�W�F�N�g</param>
/// <param name="thisObject">���g</param>
/// <returns></returns>
float NormalToufu::GetDegree(Vector2 targetposition, Vector2 thisposition)
{
	Vector2 dif = thisposition - targetposition;

	float radian = std::atan2(dif.y, dif.x);

	float degree = radian * Math::toDegree;

	return -degree;
}

// ��ɓ���������
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
/// ���ɓ���������
/// </summary>
/// <param name="targetObject">�^�[�Q�b�g�̃I�u�W�F�N�g</param>
/// <param name="thisObject">���g</param>
/// <param name="sub">�p�x���w�肳�ꂽ�x�����߂�</param>
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
/// ���ɓ���������
/// </summary>
/// <param name="targetObject">�^�[�Q�b�g�̃I�u�W�F�N�g</param>
/// <param name="thisObject">���g</param>
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
/// �E�ɓ���������
/// </summary>
/// <param name="targetObject">�^�[�Q�b�g�̃I�u�W�F�N�g</param>
/// <param name="thisObject">���g</param>
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
/// ���E�̃q�b�g������܂Ƃ߂�����
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
/// �㉺�̃q�b�g������܂Ƃ߂�����
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

	//����
		// ���g����Ƃ����^�[�Q�b�g�I�u�W�F�N�g��������\��������ł��낤��ԍ���̍��W
	Vector2 targetLeftUpPos = Vector2(position.x - (112 / 2 + 110 / 2), position.y + (74 / 2 + 63 / 2));

	Vector2 dif = targetLeftUpPos - Vector2(position.x, position.y);

	// ���W�A�������߂�
	float radian = Math::ArcTan(dif.y, dif.x);

	// ���W�A�����p�x�ɕϊ�
	float degree = radian * Math::toDegree;

	// �p�x��Ԃ�
	return degree;

}
float NormalToufu::RightUpDegree() {
	//�E��
		// ���g����Ƃ����^�[�Q�b�g�I�u�W�F�N�g��������\��������ł��낤��ԉE��̍��W
	Vector2 targetRightUpPos = Vector2(position.x + (112 / 2 + 110 / 2), position.y + (74 / 2 + 63 / 2));

	Vector2 dif = targetRightUpPos - Vector2(position.x, position.y);

	float radian = Math::ArcTan(dif.y, dif.x);

	float degree = radian * Math::toDegree;

	return degree;
}
