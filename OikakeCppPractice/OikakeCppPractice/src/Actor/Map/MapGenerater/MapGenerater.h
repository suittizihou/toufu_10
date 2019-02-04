#pragma once
#include <iostream>
#include <vector>
#include "Math/Vector3/Vector3.h"
#include "Math/Vector2/Vector2.h"
#include "Utility/CSVLoader/CSVLoader.h"
#include "Actor/Base/Actor2D.h"
#include "Utility/Assets.h"
#include "World//WorldPtr.h"
#include "Actor/Toufu/ToufuID.h"

class MapGenerater {
public:

	// �R���X�g���N�^
	MapGenerater(WorldPtr& world);
	~MapGenerater() {};

	void AddMapChip();

	// �}�b�v�Q�b�^�[(�^�C��)
	static Assets::Texture get_mapChip(int x, int y);
	static Assets::Texture get_mapChip(const Vector2& position);
	static Vector3 get_posAndChip(int x, int y);
	static Vector2 get_near_pos(const Vector2 & position);
	static inline Vector2 up_left_get_pos(int x, int y) {

		float tempX = (112.0f + map_chip_space) * x;
		float tempY = (64.0f + map_chip_space) * y;

		tempX += map_spaceX;
		tempY += map_spaceY;

		return Vector2(tempX, tempY);
	};
	static inline Vector2 up_left_get_pos(const Vector2& position) {

		float tempX = (112.0f + map_chip_space) * get_pos_numver(position).x;
		float tempY = (64.0f + map_chip_space) * get_pos_numver(position).y;

		tempX += map_spaceX;
		tempY += map_spaceY;

		return Vector2(tempX, tempY);
	};
	static Vector2 up_left_get_localpos(int x, int y);
	static Vector2 down_right_get_pos(int x, int y);
	static Vector2 down_right_get_localpos(int x, int y);
	static Vector2 get_pos_vector(Vector2 & position);
	static Vector2 get_pos_numver(const Vector2 & position);

	// �Q�b�^�[(����)
	static ToufuID get_toufu_id(int x, int y);
	static Vector3 get_toufuPos_and_id(int x, int y);

	// �}�b�v�Z�b�^�[(�^�C��)
	static void set_map_Texture(int x, int y, Assets::Texture value);
	// ���Vector2�o�[�W����
	static void set_map_Texture(const Vector2& position, Assets::Texture value);
	static void set_map_Int(int x, int y, int value);

	// �}�b�v�Z�b�^�[(����)
	static void set_map_toufu(int x, int y, ToufuID value);
	static void set_map_toufu(const Vector2 & position, ToufuID value);


	static int get_toufu_value();
	// ���ׂ��}�X�������ǂ������ׂ�(���Ȃ�true)
	static bool check_hole(int x, int y);
	// ���ׂ��}�X�������ǂ���(Vector2)
	static bool check_hole(const Vector2& position);
	// ���ׂ��}�X�������A�������͓S�^�C�����𒲂ׂ�
	static bool check_holeAndMetal(const Vector2& position);
	// ���������͓������������`�F�b�N
	static bool check_holeAndtoufu(int x, int y);
	// ���ׂ��}�X�ɓ��������邩���ׂ�(��������true)
	static bool check_toufu(int x, int y);

	// ���������Z�b�g
	static void clear_toufu();

	static const int map_spaceX{ 178 };
	static const int map_spaceY{ 85 };
private:
	static const int map_X{ 8 };					// �}�b�v�����ɉ��}�X���邩
	static const int map_Y{ 8 };					// �}�b�v���c�ɉ��}�X���邩	
	static const int map_chip_space{ 4 };			// �P�}�X�P�}�X�̊Ԃ̌���(�h�b�g���Z)
	static Assets::Texture map[map_Y][map_X];		// �}�b�v�̎�ނƃe�N�X�`�����p
	static ToufuID toufu_map[map_Y][map_X];
	WorldPtr world;
	Vector3 mapPosition_And_Chip{ {0}, {0}, {0} };	// �ŏ���x,y�ɂ͍��W������Az�ɂ̓}�b�v�̎��(Texture��int�^)������
};