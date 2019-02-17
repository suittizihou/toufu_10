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
	target_position = Input::GetInstance().GetMapDistanceMove_WASD(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	//target_position = Input::GetInstance().GetMapDistanceMove_Pad1(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	position = target_position - Vector2(0.0f, 80.0f);
	firstDraw = true;
}

void Player::OnFirstUpdate(float deltaTime)
{
	// ���̃^�[�Q�b�g�|�W�V���������Ď���Ă���
	previous_target_position = target_position;
}

void Player::OnUpdate(float deltaTime)
{
	// �~�܂��Ă���Ƃ� && �����ɉ�����ĂȂ�������
	if (move_state == MoveState::Stop && !toufu_hit) {
		target_position = Input::GetInstance().GetMapDistanceMove_WASD(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y) - Vector2(0.0f, 80.0f);
		//target_position = Input::GetInstance().GetMapDistanceMove_Pad1(MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y) - Vector2(0.0f, 80.0f);	
		if ((target_position.x != previous_target_position.x) || (target_position.y != previous_target_position.y)) {move_state = MoveState::Move;}
	}
	if (move_state == MoveState::Stop)
	{
		if (Input::GetInstance().GetKeyBoard().IsState(KEY_INPUT_S))
		{
			bool aa = MapGenerater::check_toufu(center_pos, 0, 1);
			if (aa&&GetCharacter()== Character::Ninja) { direction = 0; }else { direction = 1; }
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
			// ���K��(Normalize�Ƀo�O����)
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

	// �ڕW���W�Ǝ����̍��W�̋�����5�h�b�g�ȉ�
	if (target_position.Vector2::Distance(position) <= 5.0f) {
		move_state = MoveState::Stop;
		movement = Vector2::Zero;
		position = target_position;
	}

	// �~�܂��ĂȂ����͓����Ă�Ƃ���
	if (movement.Length() != 0) {
		move_state = MoveState::Move;
	}
	else {
		move_state = MoveState::Stop;
	}

	// �}�X�̒��S������
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
			if (firstDraw)
			{
				renderer.DrawTexture(Assets::Texture::Ninja, position);
				if (movement.Length() == 1)
				{
					firstDraw = false;
				}
			}

			switch (direction)
			{
			case 0:
				renderer.DrawTexture(Assets::Texture::Ninja, position + Vector2(0,73));
				break;
			case 1://�O
				renderer.DrawRectangle(Assets::Texture::Ninja_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
				break;
			case 2://�E
				renderer.DrawRectangle(Assets::Texture::Ninja_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
				break;
			case 3://���
				renderer.DrawRectangle(Assets::Texture::Ninja_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
				break;
			case 4://��
				renderer.DrawRectangle(Assets::Texture::Ninja_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
				break;
			}
			break;

		case Character::Kinniku:
			renderer.DrawTexture(Assets::Texture::Kinniku_Icon, Vector2(0, 0));
			if (firstDraw)
			{
				renderer.DrawTexture(Assets::Texture::Kinniku, position);
				if (movement.Length() == 1)
				{
					firstDraw = false;
				}
			}

			switch (direction)
			{
				case 1://�O
					renderer.DrawRectangle(Assets::Texture::Kinniku_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 2://�E
					renderer.DrawRectangle(Assets::Texture::Kinniku_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
				case 3://���
					renderer.DrawRectangle(Assets::Texture::Kinniku_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 4://��
					renderer.DrawRectangle(Assets::Texture::Kinniku_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
			}
			break;

		case Character::Yoroi:
			renderer.DrawTexture(Assets::Texture::Yoroi_Icon, Vector2(0, 0));
			if (firstDraw)
			{
				renderer.DrawTexture(Assets::Texture::Yoroi, position);
				if (movement.Length() == 1)
				{
					firstDraw = false;
				}
			}

			switch (direction)
			{
				case 1://�O
					renderer.DrawRectangle(Assets::Texture::Yoroi_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 2://�E
					renderer.DrawRectangle(Assets::Texture::Yoroi_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
				case 3://���
					renderer.DrawRectangle(Assets::Texture::Yoroi_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 4://��
					renderer.DrawRectangle(Assets::Texture::Yoroi_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
			}
			break;


		case Character::Kakutouka:
			renderer.DrawTexture(Assets::Texture::Kakutouka_Icon, Vector2(0, 0));
			if (firstDraw)
			{
				renderer.DrawTexture(Assets::Texture::Kakutouka, position);
				if (movement.Length() == 1)
				{
					firstDraw = false;
				}
			}

			switch (direction)
			{
				case 1://�O
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Front_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 2://�E
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Right_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
				case 3://���
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Back_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeY, 0), Vector2(181, 181)));
					break;
				case 4://��
					renderer.DrawRectangle(Assets::Texture::Kakutouka_Left_Anime, position - Vector2(35, 30), Rect(Vector2(181 * animeX, 0), Vector2(181, 181)));
					break;
			}
			break;
		}

	
#if _DEBUG
	//DrawFormatString(0, 16, GetColor(255, 0, 0), "positionX:%f positionY:%f", position.x, position.y);
	//DrawFormatString(0, 32, GetColor(255, 0, 0), "target_positionX:%f target_positionY:%f", target_position.x, target_position.y);
	//DrawFormatString(0, 48, GetColor(255, 0, 0), "Distance:%f", target_position.Vector2::Distance(position));
	//DrawFormatString(0, 64, GetColor(255, 0, 0), "numverX:%f�@numverY:%f", MapGenerater::get_pos_numver(Average_Position()).x, MapGenerater::get_pos_numver(Average_Position()).y);
	//DrawFormatString(0, 80, GetColor(255, 0, 0), "movementX:%f�@movementY:%f", movement.x, movement.y);
	 

	DrawCircle(target_position.x, target_position.y, 3, GetColor(0, 0, 255));
	DrawFormatString(0, 32, GetColor(255, 0, 0), "Player1HP : %d", hp);

	//DrawBox(position.x - 5, position.y + 75, position.x + 117, position.y + 149, GetColor(255, 0, 0), TRUE);
	//DrawBox(position.x, position.y, position.x + 117, position.y + 149, GetColor(255, 0, 0), TRUE);
	//DrawPixel(Average_Position().x, Average_Position().y, GetColor(0, 255, 0));
#endif
}

// ��_�Ԃ̕��ϒl���璆�S���W������o��
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
	// �v���C���[��hp���Z�b�g
	PlayerManager::SetP1Hp(hp, GetCharacter());
	
	if (hp <= 0) {
		world->SendEventMessage(EventMessage::PlayerDead);
		status = Status::Dead;
	}
	else {// hp��0����Ȃ��Ȃ烊�X�|�[��
		int x = rand.Range(0, 7);
		int y = rand.Range(0, 7);
		// ���������������琶��
		if (!MapGenerater::check_toufu(x, y)) {
			position = MapGenerater::up_left_get_pos(x, y);
		}

	}
}

void Player::OnCollide(const HitInfo & hitInfo)
{
	//(5, 86), Vector2(108, 118) �v���C���[�̃T�C�Y
	//Vector2(182,3), Vector2(1016,509)P kabe
	//Vector2(0,80), Vector2(110,120)�@�����̃T�C�Y
	//Vector2(187, 31), Vector2(1013, 509) T kabe

	toufu_hit = false;

	if ((hitInfo.collideActor->GetName() == "StopNormalToufu" || hitInfo.collideActor->GetName() == "NormalToufu" || hitInfo.collideActor->GetName() == "MetalToufu")
		&& hitInfo.collideActor->GetCenterPosition().Distance(center_pos) <= 66.0f) {

		Damage();
	}

	//if (hitInfo.collideActor->GetName() == "NormalToufu")
	//{
	//	toufu_hit = true;
	//	// �G�l�~�[�̍��W������
	//	Vector2 enemy_pos = hitInfo.collideActor->GetVec2Position();

	//	// �����̍��WX���G�l�~�[�̍��WX���傫�� ���� ������-1�ȉ��Ȃ�
	//	if (position.x < enemy_pos.x && hitInfo.collideActor->GetMovement().x <= -1)
	//	{
	//		// �����̍��W�ɓG�̈ړ��ʂ����Z
	//		position += hitInfo.collideActor->GetMovement();

	//		if (enemy_pos.x - 187 < 113) { 
	//			int x = rand.Range(0, 7);
	//			int y = rand.Range(0, 7);
	//			// ���������������琶��
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
	//			// ���������������琶��
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
	//			// ���������������琶��
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
	//			// ���������������琶��
	//			if (!MapGenerater::check_toufu(x, y)) {
	//				position = MapGenerater::up_left_get_pos(x, y);
	//				Damage();
	//			}
	//		}
	//	}

	//}
	world->SendEventMessage(EventMessage::Hit);
}
