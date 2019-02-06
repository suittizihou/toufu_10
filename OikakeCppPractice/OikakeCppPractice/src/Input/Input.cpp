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


// WASD用
Vector2 Input::GetMapDistanceMove_WASD(int map_chipX, int map_chipY) {
	int valueX{};
	int valueY{};
	int map_chip_numverX{ map_chipX };
	int map_chip_numverY{ map_chipY };

	// 上ボタン
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_W)) {

		//// 豆腐があればリターンする
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
				move_state = MoveState::Move;
			}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// 下ボタン
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
			move_state = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// 右ボタン
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
			move_state = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// 左ボタン
	if (Input::GetInstance().keyBoard.IsState(KEY_INPUT_A))
	{
		//	// 行こうとしている場所に豆腐はあるか
		if (MapGenerater::check_holeAndtoufu(map_chipX - 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else if (map_chip_numverX - 1 < 0 || map_chip_numverX - 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			//return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
			valueX = -1;
			move_state = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	map_chip_numverX += valueX;
	map_chip_numverY += valueY;

	return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
}

// 矢印キー用
//Vector2 Input::GetMapDistanceMove_Arrow(int map_chipX, int map_chipY) {
//	int map_chip_numverX{ map_chipX };
//	int map_chip_numverY{ map_chipY };
//
//	// 上
//	if (keyBoard.IsState(KEY_INPUT_UP) && move_state == MoveState::Stop) {
//
//		// 豆腐があればリターンする
//		if (MapGenerater::check_toufu(map_chip_numverX, map_chip_numverY - 1)) { return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY); }
//
//		valueY += -1;
//		move_state = MoveState::Move;
//	}
//
//	// 下
//	if (keyBoard.IsState(KEY_INPUT_DOWN) && move_state == MoveState::Stop) {
//
//		if (MapGenerater::check_toufu(map_chip_numverX, map_chip_numverY + 1)) { return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY); }
//
//		valueY += 1;
//		move_state = MoveState::Move;
//	}
//
//	// 右
//	if (keyBoard.IsState(KEY_INPUT_RIGHT) && move_state == MoveState::Stop) {
//
//		if (MapGenerater::check_toufu(map_chip_numverX + 1, map_chip_numverY)) { return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY); }
//
//		valueX += 1;
//		move_state = MoveState::Move;
//	}
//
//	// 左
//	if (keyBoard.IsState(KEY_INPUT_LEFT) && move_state == MoveState::Stop) {
//
//		if (MapGenerater::check_toufu(map_chip_numverX - 1, map_chip_numverY)) { return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY); }
//
//		valueX += -1;
//		move_state = MoveState::Move;
//	}
//
//	map_chip_numverX += valueX;
//	map_chip_numverY += valueY;
//
//	return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
//}

// パッド用(1P)
Vector2 Input::GetMapDistanceMove_Pad1(int map_chipX, int map_chipY) {

	int valueX{};
	int valueY{};
	int map_chip_numverX{ map_chipX };
	int map_chip_numverY{ map_chipY };

	//if ((GetJoypadInputState(input_type) & PAD_INPUT_UP) != 0/*GetXBoxController().IsButtonDown(XboxGamePad::DPad_Up*/) {

	// 上ボタン
	if (GetXBoxController().IsButtonState(XboxGamePad::Dpad_Up)) {
	// 豆腐があればリターンする
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
				move_state = MoveState::Move;
			}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	//}

	// 下ボタン
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
		move_state = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// 右ボタン
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
		move_state = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// 左ボタン
	if (GetXBoxController().IsButtonState(XboxGamePad::Dpad_Left))
	{

		//	// 行こうとしている場所に豆腐はあるか
		if (MapGenerater::check_holeAndtoufu(map_chipX - 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX - 1 < 0 || map_chip_numverX - 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
		valueX = -1;
		move_state = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	map_chip_numverX += valueX;
	map_chip_numverY += valueY;

	return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
}

// パッド用(2P)
Vector2 Input::GetMapDistanceMove_Pad2(int map_chipX, int map_chipY) {

	int valueX{};
	int valueY{};
	int map_chip_numverX{ map_chipX };
	int map_chip_numverY{ map_chipY };

	//if ((GetJoypadInputState(input_type) & PAD_INPUT_UP) != 0/*GetXBoxController().IsButtonDown(XboxGamePad::DPad_Up*/) {

	// 上ボタン
	if (GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Up)) {
	// 豆腐があればリターンする
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
				move_state2 = MoveState::Move;
			}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}
	//}

	// 下ボタン
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
		move_state2 = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// 右ボタン
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
		move_state2 = MoveState::Move;
		}
		map_chip_numverX += valueX;
		map_chip_numverY += valueY;

		return MapGenerater::up_left_get_pos(map_chip_numverX, map_chip_numverY);
	}

	// 左ボタン
	if (GetXBoxController().IsButtonState2(XboxGamePad::Dpad_Left))
	{

		//	// 行こうとしている場所に豆腐はあるか
		if (MapGenerater::check_holeAndtoufu(map_chipX - 1, map_chipY)) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY); 
		}
		else if (map_chip_numverX - 1 < 0 || map_chip_numverX - 1 >= 8 ||
			map_chip_numverY < 0 || map_chip_numverY >= 8) {
			return MapGenerater::up_left_get_pos(map_chipX, map_chipY);
		}
		else {
		valueX = -1;
		move_state2 = MoveState::Move;
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

// 豆腐の座標、移動したい方向の配列座標たち
Vector2 Input::PlayerHitToufuMove(const Vector2& position, int map_chipX, int map_chipY)
{
	int x{ static_cast<int>(MapGenerater::get_pos_numver(position).x) };
	int y{ static_cast<int>(MapGenerater::get_pos_numver(position).y) };

	while (true) {
		x += map_chipX;
		y += map_chipY;
		if (MapGenerater::check_toufu(x, y)) {
			// 上から下に押されたときの処理
			if (map_chipY == 1) {
				y -= 1;
			}
			// 下から上に押されたときの処理
			if (map_chipY == -1) {
				y += 1;
			}
			// 左から下に押されたときの処理
			if (map_chipX == 1) {
				x -= 1;
			}
			// 右から左に押されたときの処理
			if (map_chipX == -1) {
				x += 1;
			}
			break;
		}
		if (x < 0 || x > 7 || y < 0 || y > 7) {
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

	//// 右ボタン
	//if ((d_input.POV[0] * 0.01f) == 90) {
	//	value = 1.0f;
	//}
	//	
	//// 左ボタン
	//if ((d_input.POV[0] * 0.01f) == 270) {
	//	value = -1.0f;
	//}
	// 右ボタン
	if ((GetJoypadInputState(input_type) & PAD_INPUT_RIGHT) != 0) {
		value = 1.0f;
	}
		
	// 左ボタン
	if ((GetJoypadInputState(input_type) & PAD_INPUT_LEFT) != 0) {
		value = -1.0f;
	}

	return value;
}

float Input::GetDInputVertical(int input_type) const
{
	float value{};

	//// 上ボタン
	//if ((d_input.POV[0] * 0.01f) == 0) {
	//	value = -1.0f;
	//}
	//
	//// 下ボタン
	//if ((d_input.POV[0] * 0.01f) == 180) {
	//	value = 1.0f;
	//}
	// 上ボタン
	if ((GetJoypadInputState(input_type) & PAD_INPUT_UP) != 0) {
		value = -1.0f;
	}
	
	// 下ボタン
	if ((GetJoypadInputState(input_type) & PAD_INPUT_DOWN) != 0) {
		value = 1.0f;
	}
	
	return value;
}

