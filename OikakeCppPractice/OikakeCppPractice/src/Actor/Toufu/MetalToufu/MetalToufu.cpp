#include "MetalToufu.h"
#include <windows.h>
#include <sstream>

#include"Renderer/Renderer.h"
#include"Collision/Collision2D/Box/Box.h"
#include"Utility/Random/Random.h"
#include"Application/Window/Window.h"
#include "Actor/Map/MapGenerater/MapGenerater.h"
#include "../ToufuID.h"

MetalToufu::MetalToufu(IWorld * world, const Vector2 & position_, const int& _number, bool spone_special_move)
	: Actor2D(world, "SponeMetalToufu", position_, std::make_shared<Box>(Vector2(0, 57), Vector2(110, 120)), _number)
{
	// 267
	MapGenerater::set_map_toufu(Average_Position(), ToufuID::Metal);

	spone_special_move_ = spone_special_move;

	if (spone_special_move) {
		spone_position = Vector2(position.x, -128.0f);
		spone_move = MetalToufuMove::SponeMove;

		default_position = position_;
		position = spone_position;
	}
}

MetalToufu::~MetalToufu()
{
}

void MetalToufu::OnInitialize()
{
}

void MetalToufu::OnFirstUpdate(float deltaTime)
{
	MapGenerater::set_map_toufu(Average_Position(), ToufuID::Metal);
	if (MapGenerater::check_hole(center_pos)) {
		status = Status::Dead;
		MapGenerater::set_map_Texture(center_pos, Assets::Texture::MetalToufuTile);
	}
}

void MetalToufu::OnUpdate(float deltaTime)
{
	// ���܂ꂽ���̓���()
	if (spone_special_move_) {
		SponeMove();
	}

	if (_move)
	{
		Move();

		if (MapGenerater::check_hole(center_pos)) {
			status = Status::Dead;
			MapGenerater::set_map_Texture(center_pos, Assets::Texture::MetalToufuTile);
		}
	}

	if (spone_move == MetalToufuMove::SponeMoveStop && position.Clamp(MapGenerater::up_left_get_pos(0, 0) - Vector2(0, 58.0f), MapGenerater::up_left_get_pos(7, 7) - Vector2(0, 58.0f)))
	{
		_move = false;
		movement = Vector2::Zero;

	}

	//if (one_time_position.x == position.x && one_time_position.y == position.y) b_move = false;
	center_pos = Average_Position();
}

void MetalToufu::OnDraw(Renderer & renderer)
{
	renderer.DrawTexture(Assets::Texture::MetalToufu, position);
	//DrawBox(position.x, position.y + 57, position.x + 110, position.y + 120, GetColor(0, 255, 0), TRUE);
	//DrawPixel(Average_Position().x, Average_Position().y, GetColor(255, 0, 0));
	//
	//float test = GetDegree(MapGenerater::up_left_get_pos(5, 5), Average_Position());

	//DrawFormatString(0, 96, GetColor(255, 0, 0), "agree : %f", test);
}

void MetalToufu::Move()
{
	position += movement;
}

void MetalToufu::SponeMove() {
	// ���܂ꂽ��ǂ�ǂ񉺂ɗ����Ă���
	if (spone_move == MetalToufuMove::SponeMove) {
		position.y += 10.0f;
	}
	// �w��̗����ӏ���y�������̃|�W�V��������������~�߂�
	if (default_position.y <= position.y) {
		spone_move = MetalToufuMove::SponeMoveStop;
		position = default_position;
		name = "MetalToufu";
		// ��������������
		if (!MapGenerater::check_holeAndMetal(position)) {
			status = Status::Dead;
			MapGenerater::set_map_Texture(center_pos, Assets::Texture::Hole);
		}
	}
}

bool MetalToufu::GetBoolMove()
{
	return _move;
}

Vector2 MetalToufu::Average_Position() {
	Vector2 pos{ position.x + position.x + 110, position.y + 57 + position.y + 120 };
	return Vector2(pos.x / 2, pos.y / 2);
}

void MetalToufu::OnFinalize()
{
}

void MetalToufu::OnMessage(EventMessage message, void * param)
{
}

void MetalToufu::OnCollide(const HitInfo & hitInfo)
{
	if (hitInfo.collideActor->GetNumber() == this->GetNumber()) { 
		return; 
	}

	//if (name != "SponeMetalToufu") {
	//	if (hitInfo.collideActor->GetName() == "MetalToufu")
	//	{
	//		MapGenerater::set_map_toufu(Average_Position(), ToufuID::None);
	//		status = Status::Dead;
	//	}
	//}
	//else if ((hitInfo.collideActor->GetName() == "player" || hitInfo.collideActor->GetName() == "player2") && !b_move)
	//{
	//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) != 0 || (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A) != 0) {

	//		// ��ɓ������Ă���Ƃ�
	//		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0 || (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_DOWN) != 0) {

	//			if (TopHit(hitInfo.collideActor->GetCenterPosition(), Average_Position())) {
	//				
	//				movement = Vector2(0, hitInfo.collideActor->GetSpeed());
	//			}
	//		}

	//		// ���ɓ������Ă���Ƃ�
	//		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0 || (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_UP) != 0) {

	//			if (BottomHit(hitInfo.collideActor->GetCenterPosition(), Average_Position())) {
	//				movement = Vector2(0, -hitInfo.collideActor->GetSpeed());
	//			}
	//		}

	//		// ���ɓ������Ă���Ƃ�
	//		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0 || (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_RIGHT) != 0) {

	//			if (LeftHit(hitInfo.collideActor->GetCenterPosition(), Average_Position())) {
	//				movement = Vector2(hitInfo.collideActor->GetSpeed(), 0);
	//			}
	//		}


	//		// �E�ɓ������Ă���Ƃ�
	//		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0 || (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_LEFT) != 0) {

	//			if (RightHit(hitInfo.collideActor->GetCenterPosition(), Average_Position())) {
	//				movement = Vector2(-hitInfo.collideActor->GetSpeed(), 0);
	//			}
	//		}
	//	}

	//	//position += movement;
	//	if (movement.x != 0 || movement.y != 0)b_move = true;
	//	//Vector2(103, 32) + Vector2(110, 40))

	//	
	//}

	int score = 1;
	world->SendEventMessage(EventMessage::AddScore, &score);
}

/// <summary>
/// ���g����Ƃ����^�[�Q�b�g�̒��S�_�Ƃ̊p�x
/// </summary>
/// <param name="targetPos">�^�[�Q�b�g�I�u�W�F�N�g</param>
/// <param name="thisObject">���g</param>
/// <returns></returns>
float MetalToufu::GetDegree(Vector2 targetposition, Vector2 thisposition)
{
	Vector2 dif = thisposition - targetposition;

	float radian = std::atan2(dif.y, dif.x);

	float degree = radian * Math::toDegree;

	return -degree;
}

// ��ɓ���������
bool MetalToufu::TopHit(Vector2 targetposition, Vector2 thisposition)
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
bool MetalToufu::BottomHit(Vector2 targetposition, Vector2 thisposition)
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
bool MetalToufu::LeftHit(Vector2 targetposition, Vector2 thisposition)
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
bool MetalToufu::RightHit(Vector2 targetposition, Vector2 thisposition)
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
bool MetalToufu::L_R_Hit(Vector2 targetposition, Vector2 thisposition)
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
bool MetalToufu::T_B_Hit(Vector2 targetposition, Vector2 thisposition)
{
	return TopHit(targetposition, thisposition) || BottomHit(targetposition, thisposition);
}
float MetalToufu::LeftUpDegree(){

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
float MetalToufu::RightUpDegree(){
	//�E��
		// ���g����Ƃ����^�[�Q�b�g�I�u�W�F�N�g��������\��������ł��낤��ԉE��̍��W
		Vector2 targetRightUpPos = Vector2(position.x + (112 / 2 + 110 / 2), position.y + (74 / 2 + 63 / 2));

		Vector2 dif = targetRightUpPos - Vector2(position.x, position.y);

		float radian = Math::ArcTan(dif.y, dif.x);

		float degree = radian * Math::toDegree;

		return degree;
}

// ���ϑO�̊p�x�œ����蔻�肷��z
///// <summary>
///// ���g����Ƃ����^�[�Q�b�g�̒��S�_�Ƃ̊p�x
///// </summary>
///// <param name="targetPos">�^�[�Q�b�g�I�u�W�F�N�g</param>
///// <param name="thisObject">���g</param>
///// <returns></returns>
//float MetalToufu::GetDegree(Vector2 targetposition, Vector2 thisposition)
//{
//	Vector2 dif = thisposition - targetposition;
//
//	float radian = Math::ArcTan(dif.y, dif.x);
//
//	float degree = radian * Math::toDegree;
//
//	return -degree;
//}
//bool MetalToufu::TopHit(Vector2 targetposition, Vector2 thisposition)
//{
//	bool upLeftAngle = GetDegree(targetposition, thisposition) <= LeftUpDegree();
//	bool upRightAngle = GetDegree(targetposition, thisposition) >= RightUpDegree();
//
//	return upLeftAngle && upRightAngle;
//}
//
///// <summary)
///// ���ɓ���������
///// </summary>
///// <param name="targetObject">�^�[�Q�b�g�̃I�u�W�F�N�g</param>
///// <param name="thisObject">���g</param>
///// <param name="sub">�p�x���w�肳�ꂽ�x�����߂�</param>
///// <returns></returns>
//bool MetalToufu::BottomHit(Vector2 targetposition, Vector2 thisposition)
//{
//	bool downLeftAngle = GetDegree(targetposition, thisposition) >= -LeftUpDegree();
//	bool downRightAngle = GetDegree(targetposition, thisposition) <= -RightUpDegree();
//
//	return downLeftAngle && downRightAngle;
//}
//
///// <summary>
///// ���ɓ���������
///// </summary>
///// <param name="targetObject">�^�[�Q�b�g�̃I�u�W�F�N�g</param>
///// <param name="thisObject">���g</param>
///// <returns></returns>
//bool MetalToufu::LeftHit(Vector2 targetposition, Vector2 thisposition)
//{
//	bool upLeftAngle = -GetDegree(targetposition, thisposition) > LeftUpDegree();
//	bool downLeftAngle = -GetDegree(targetposition, thisposition) < -LeftUpDegree();
//
//	return upLeftAngle || downLeftAngle;
//}
//
///// <summary>
///// �E�ɓ���������
///// </summary>
///// <param name="targetObject">�^�[�Q�b�g�̃I�u�W�F�N�g</param>
///// <param name="thisObject">���g</param>
///// <returns></returns>
//bool MetalToufu::RightHit(Vector2 targetposition, Vector2 thisposition)
//{
//	bool upRightAngle = GetDegree(targetposition, thisposition) < RightUpDegree();
//	bool downRightAngle = GetDegree(targetposition, thisposition) > -RightUpDegree();
//
//	return upRightAngle && downRightAngle;
//}
//
///// <summary>
///// ���E�̃q�b�g������܂Ƃ߂�����
///// </summary>
///// <param name="targetObject"></param>
///// <param name="thisObject"></param>
///// <param name="sub"></param>
///// <returns></returns>
//bool MetalToufu::L_R_Hit(Vector2 targetposition, Vector2 thisposition)
//{
//	return LeftHit(targetposition, thisposition) || RightHit(targetposition, thisposition);
//}
//
///// <summary>
///// �㉺�̃q�b�g������܂Ƃ߂�����
///// </summary>
///// <param name="targetObject"></param>
///// <param name="thisObject"></param>
///// <param name="sub"></param>
///// <returns></returns>
//bool MetalToufu::T_B_Hit(Vector2 targetposition, Vector2 thisposition)
//{
//	return TopHit(targetposition, thisposition) || BottomHit(targetposition, thisposition);
//}
//float MetalToufu::LeftUpDegree() {
//
//	//����
//		// ���g����Ƃ����^�[�Q�b�g�I�u�W�F�N�g��������\��������ł��낤��ԍ���̍��W
//	Vector2 targetLeftUpPos = Vector2(position.x - (112 / 2 + 110 / 2), position.y + (74 / 2 + 63 / 2));
//
//	Vector2 dif = targetLeftUpPos - Vector2(position.x, position.y);
//
//	// ���W�A�������߂�
//	float radian = Math::ArcTan(dif.y, dif.x);
//
//	// ���W�A�����p�x�ɕϊ�
//	float degree = radian * Math::toDegree;
//
//	// �p�x��Ԃ�
//	return degree;
//
//}
//float MetalToufu::RightUpDegree() {
//	//�E��
//		// ���g����Ƃ����^�[�Q�b�g�I�u�W�F�N�g��������\��������ł��낤��ԉE��̍��W
//	Vector2 targetRightUpPos = Vector2(position.x + (112 / 2 + 110 / 2), position.y + (74 / 2 + 63 / 2));
//
//	Vector2 dif = targetRightUpPos - Vector2(position.x, position.y);
//
//	float radian = Math::ArcTan(dif.y, dif.x);
//
//	float degree = radian * Math::toDegree;
//
//	return degree;
//}
//void MetalToufu::Move()
//{
//	position += movement;
//}
//bool MetalToufu::GetBoolMove()
//{
//	return b_move;
//}