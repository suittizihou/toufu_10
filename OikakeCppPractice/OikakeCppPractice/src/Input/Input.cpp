#include"Input/Input.h"
#include<DxLib.h>
#include <math.h>
#include"Math/Convert/Convert.h"
#include "Actor/Map/MapGenerater/MapGenerater.h"
#include "Actor/Player/Player.h"

Input::Input() 
	: xboxController()
	, keyBoard()
{
	RegistFunc();
}

Input::~Input() {
}

Input & Input::GetInstance() {
	static Input instance;
	return instance;
}

void Input::RegistFunc() {
	axisFunc[0] = [&](void)->float {return GetVertical(); };
	axisFunc[1] = [&](void)->float {return GetHorizontal(); };
	axisFunc[2] = [&](void)->float {return  GetVertical2(); };
	axisFunc[3] = [&](void)->float {return  GetHorizontal2(); };
}

bool Input::GetCommand(Command command) {
	return commandFunc[static_cast<int>(command)]();
}

float Input::GetAxis(Axis axis)
{
	return axisFunc[static_cast<int>(axis)]();
}



KeyBoard & Input::GetKeyBoard()
{
	return keyBoard;
}


void Input::Update() {
	keyBoard.Update();
	xboxController.Update();
	prevInput = curInput;
	curInput = Input::GetInstance().GetVelocity();
}

XBoxController & Input::GetXBoxController() {
	return xboxController;
}

Vector2 Input::GetVelocity() const
{
	return Vector2(GetHorizontal(), GetVertical());
}
Vector2 Input::GetVelocity2() const
{
	return Vector2(GetHorizontal2(), GetVertical2());
}
Vector2 Input::GetDInputVelocity(int input_type) const {
	return Vector2(GetDInputHorizontal(input_type), GetDInputVertical(input_type));
}


// WASD�p
Vector2 Input::GetMapDistanceMove_WASD(int map_chipX, int map_chipY) {
	int valueX{};
	int valueY{};
	int map_chip_numverX{ map_chipX };
	int map_chip_numverY{ map_chipY };

	// ��{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_W)) {

		//// ����������΃��^�[������
		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY - 1)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else
			if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
				map_chip_numverY - 1 < 0 || map_chip_numverY - 1 >= 8) {
				return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
			}
			else {
				valueY = -1;
			}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// ���{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_S)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY + 1)) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
			map_chip_numverY + 1 < 0 || map_chip_numverY + 1 >= 8) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueY = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// �E�{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_D)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX + 1, map_chipY)) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX + 1 < 0 || map_chip_numverX + 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueX = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// ���{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_A))
	{
		//	// �s�����Ƃ��Ă���ꏊ�ɓ����͂��邩
		if (MapGenerater::check_holeAndtoufu(map_chipX - 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else if (map_chip_numverX - 1 < 0 || map_chip_numverX - 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueX = -1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	map_chip_numverX += valueX;
	map_chip_numverY += valueY;

	return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
}

// ���L�[�p
Vector2 Input::GetMapDistanceMove_Arrow(int map_chipX, int map_chipY) {
	int valueX{};
	int valueY{};
	int map_chip_numverX{ map_chipX };
	int map_chip_numverY{ map_chipY };

	// ��{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_UP)) {

		//// ����������΃��^�[������
		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY - 1)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else
			if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
				map_chip_numverY - 1 < 0 || map_chip_numverY - 1 >= 8) {
				return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
			}
			else {
				valueY = -1;
			}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// ���{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_DOWN)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY + 1)) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
			map_chip_numverY + 1 < 0 || map_chip_numverY + 1 >= 8) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueY = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// �E�{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_RIGHT)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX + 1, map_chipY)) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX + 1 < 0 || map_chip_numverX + 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueX = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// ���{�^��
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_LEFT))
	{
		//	// �s�����Ƃ��Ă���ꏊ�ɓ����͂��邩
		if (MapGenerater::check_holeAndtoufu(map_chipX - 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else if (map_chip_numverX - 1 < 0 || map_chip_numverX - 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueX = -1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	map_chip_numverX += valueX;
	map_chip_numverY += valueY;

	return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
}

// �p�b�h�p(1P)
Vector2 Input::GetMapDistanceMove_Pad1(int map_chipX, int map_chipY) {

	int valueX{};
	int valueY{};
	int map_chip_numverX{ map_chipX };
	int map_chip_numverY{ map_chipY };

	//if ((GetJoypadInputState(input_type) & PAD_INPUT_UP) != 0/*GetXBoxController().IsButtonDown(XboxGamePad::DPad_Up*/) {

	// ��{�^��
	if (GetXBoxController().IsButtonState(XboxGamePad::Dpad_Up)) {
	// ����������΃��^�[������
		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY - 1)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else
			if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
				map_chip_numverY - 1 < 0 || map_chip_numverY - 1 >= 8) {
				return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
			}
			else {
				valueY = -1;
			}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	//}

	// ���{�^��
	if (GetXBoxController().IsButtonState(XboxGamePad::Dpad_Down)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY + 1)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
			map_chip_numverY + 1 < 0 || map_chip_numverY + 1 >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
		valueY = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// �E�{�^��
	if (GetXBoxController().IsButtonState(XboxGamePad::Dpad_Right)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX + 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX + 1 < 0 || map_chip_numverX + 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
		valueX = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// ���{�^��
	if (GetXBoxController().IsButtonState(XboxGamePad::Dpad_Left))
	{

		//	// �s�����Ƃ��Ă���ꏊ�ɓ����͂��邩
		if (MapGenerater::check_holeAndtoufu(map_chipX - 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX - 1 < 0 || map_chip_numverX - 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
		valueX = -1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	map_chip_numverX += valueX;
	map_chip_numverY += valueY;

	return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
}

// �p�b�h�p(2P)
Vector2 Input::GetMapDistanceMove_Pad2(int map_chipX, int map_chipY) {

	int valueX{};
	int valueY{};
	int map_chip_numverX{ map_chipX };
	int map_chip_numverY{ map_chipY };

	//if ((GetJoypadInputState(input_type) & PAD_INPUT_UP) != 0/*GetXBoxController().IsButtonDown(XboxGamePad::DPad_Up*/) {

	// ��{�^��
	if (GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Up)) {
		// ����������΃��^�[������
		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY - 1)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else
			if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
				map_chip_numverY - 1 < 0 || map_chip_numverY - 1 >= 8) {
				return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
			}
			else {
				valueY = -1;
			}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	//}

	// ���{�^��
	if (GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Down)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX, map_chipY + 1)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else if (map_chip_numverX < 0 || map_chip_numverX >= 8 ||
			map_chip_numverY + 1 < 0 || map_chip_numverY + 1 >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueY = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// �E�{�^��
	if (GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Right)) {

		if (MapGenerater::check_holeAndtoufu(map_chipX + 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else if (map_chip_numverX + 1 < 0 || map_chip_numverX + 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueX = 1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// ���{�^��
	if (GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Left))
	{

		//	// �s�����Ƃ��Ă���ꏊ�ɓ����͂��邩
		if (MapGenerater::check_holeAndtoufu(map_chipX - 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else if (map_chip_numverX - 1 < 0 || map_chip_numverX - 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueX = -1;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	map_chip_numverX += valueX;
	map_chip_numverY += valueY;

	return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
}

Vector2 AveragePosition(const Vector2& position) {
	Vector2 pos{ position.x + position.x + 112, position.y + position.y + 64 };
	return Vector2(pos.x / 2, pos.y / 2);
}

int x{};
int y{};

// �����̍��W�A�ړ������������̔z����W����
Vector2 Input::PlayerHitToufuMove(const Vector2& center_pos, int map_chipX, int map_chipY)
{
	x = static_cast<int>(MapGenerater::get_pos_numver(center_pos).x);
	y = static_cast<int>(MapGenerater::get_pos_numver(center_pos).y);

	while (true) {
		x += map_chipX;
		y += map_chipY;

		// ��������������
		if (MapGenerater::check_toufu(x, y)) {
			// �ォ�牺�ɉ����ꂽ�Ƃ��̏���
			if (map_chipY == 1) {
				y -= 1;
			}
			// �������ɉ����ꂽ�Ƃ��̏���
			if (map_chipY == -1) {
				y += 1;
			}
			// �����牺�ɉ����ꂽ�Ƃ��̏���
			if (map_chipX == 1) {
				x -= 1;
			}
			// �E���獶�ɉ����ꂽ�Ƃ��̏���
			if (map_chipX == -1) {
				x += 1;
			}
			break;
		}

		// �Ǎۂɓ���������
		if (x < 0 || x > 7 || y < 0 || y > 7) {
			// �ォ�牺�ɉ����ꂽ�Ƃ��̏���
			if (map_chipY == 1) {
				y -= 1;
			}
			// �������ɉ����ꂽ�Ƃ��̏���
			if (map_chipY == -1) {
				y += 1;
			}
			// �����牺�ɉ����ꂽ�Ƃ��̏���
			if (map_chipX == 1) {
				x -= 1;
			}
			// �E���獶�ɉ����ꂽ�Ƃ��̏���
			if (map_chipX == -1) {
				x += 1;
			}
			break;
		}
	}

	//if (x <= 0) {
	//	x -= map_chipX;
	//}
	//if (y <= 0) {
	//	y -= map_chipY;
	//}

	x = Math::Clamp(x, 0, 7);
	y = Math::Clamp(y, 0, 7);

	return /*Vector2(AveragePosition(*/MapGenerater::up_left_get_pos(x, y)/*))*/;
}


float Input::GetVertical() const
{
	float value = 0.0f;

	if (keyBoard.IsState(KEY_INPUT_W)) {
		value = -1.0f;
	}
	if (keyBoard.IsState(KEY_INPUT_S)) {
		value = 1.0f;
	}

	return value;
}

float Input::GetHorizontal() const
{
	float value = 0.0f;
	if (keyBoard.IsState(KEY_INPUT_A)) {
		value = -1.0f;
	}
	if (keyBoard.IsState(KEY_INPUT_D)) {
		value = 1.0f;
	}
	return value;
}

float Input::GetVertical2() const
{
	float value = 0.0f;

	if (keyBoard.IsState(KEY_INPUT_UP)) {
		value = 1.0f;
	}
	if (keyBoard.IsState(KEY_INPUT_DOWN)) {
		value = -1.0f;
	}
	return value;
}

float Input::GetHorizontal2() const
{
	float value = 0.0f;

	if (keyBoard.IsState(KEY_INPUT_LEFT)) {
		value = -1.0f;
	}
	if (keyBoard.IsState(KEY_INPUT_RIGHT)) {
		value = 1.0f;
	}
	return value;
}

float Input::GetDInputHorizontal(int input_type) const
{
	float value{};

	//// �E�{�^��
	//if ((d_input.POV[0] * 0.01f) == 90) {
	//	value = 1.0f;
	//}
	//	
	//// ���{�^��
	//if ((d_input.POV[0] * 0.01f) == 270) {
	//	value = -1.0f;
	//}
	// �E�{�^��
	if ((GetJoypadInputState(input_type) & PAD_INPUT_RIGHT) != 0) {
		value = 1.0f;
	}
		
	// ���{�^��
	if ((GetJoypadInputState(input_type) & PAD_INPUT_LEFT) != 0) {
		value = -1.0f;
	}

	return value;
}

float Input::GetDInputVertical(int input_type) const
{
	float value{};

	//// ��{�^��
	//if ((d_input.POV[0] * 0.01f) == 0) {
	//	value = -1.0f;
	//}
	//
	//// ���{�^��
	//if ((d_input.POV[0] * 0.01f) == 180) {
	//	value = 1.0f;
	//}
	// ��{�^��
	if ((GetJoypadInputState(input_type) & PAD_INPUT_UP) != 0) {
		value = -1.0f;
	}
	
	// ���{�^��
	if ((GetJoypadInputState(input_type) & PAD_INPUT_DOWN) != 0) {
		value = 1.0f;
	}
	
	return value;
}

