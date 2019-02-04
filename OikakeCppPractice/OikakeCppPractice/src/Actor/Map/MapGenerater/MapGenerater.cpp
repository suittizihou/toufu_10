#include "MapGenerater.h"
#include "Actor/Base/ActorGroup.h"
#include "../MapChip/MapChip.h"
#include "World/World.h"
#include "Math/Math.h"

using namespace Assets;

Assets::Texture MapGenerater::map[map_Y][map_X]{};
ToufuID MapGenerater::toufu_map[map_Y][map_X]{};

// �R���X�g���N�^
MapGenerater::MapGenerater(WorldPtr& world) 
	: world(world){
	// CSV�t�@�C���̓ǂݍ���
	CSVLoader loader("map.csv");

	// �}�b�v�f�[�^���R�s�[
	for (int i = 0; i < map_Y; ++i) {
		for (int j = 0; j < map_X; ++j) {
			map[i][j] = static_cast<Texture>(loader.GetDataInt(j, i));
		}
	}
}

// �o�^
void MapGenerater::AddMapChip() {
	for (int i = 0; i < map_Y; i++)
	{
		for (int j = 0; j < map_X; j++)
		{
			world->AddActor_Back(ActorGroup::BackGround, std::make_shared<MapChip>(world.get(), map[i][j], up_left_get_pos(j, i), 0));
		}
	}
}

// �w�肵���z��ԍ��̃}�b�v�^�C���̏����擾(�߂�l��Texture)
Texture MapGenerater::get_mapChip(int x, int y) {
	//if (x < 0 || y < 0 || x >= map_X || y >= map_Y) { return Texture::None; }
	return map[y][x];
}
// Vector2�o�[�W����
Texture MapGenerater::get_mapChip(const Vector2& position) {
	//if (x < 0 || y < 0 || x >= map_X || y >= map_Y) { return Texture::None; }
	return map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)];
}

// �ŏ���x, y�ɂ͍��W������Az�ɂ̓}�b�v�̎�ނ�����܂�
Vector3 MapGenerater::get_posAndChip(int x, int y) {
	// �m�肽�����W�̃}�b�v�`�b�v����int�^�ɕϊ�
	int tempChip = static_cast<int>(map[y][x]);

	float  tempX = 112.0f * x;
	float tempY = 64.0f * y;

	// Y�͏オ�Q�}�X�󂢂Ă��邽��
	tempX += map_spaceX;
	tempY += map_spaceY;

	return Vector3(tempX, tempY, static_cast<float>(tempChip));
}

// ��������W�����ԋ߂��^�C���̍��W���擾
Vector2 MapGenerater::get_near_pos(const Vector2 & position) {

	float current_distance;		{ 0.0f; }
	float most_short_distance	{ 10000.0f };

	Vector2 near_position{ 0.0f, 0.0f };

	for (int i = 0; i < map_Y; ++i) {
		for (int j = 0; j < map_X; ++j)
		{
			current_distance = (position - up_left_get_pos(i, j)).Length();
			if (current_distance < most_short_distance) {
				most_short_distance = current_distance;
				near_position = up_left_get_pos(i, j);
			}
		}
	}

	return near_position;
}

// �m�肽���}�X��x�Ay���w�肷��Ƃ����̍�����W���Ԃ��Ă���
//Vector2 MapGenerater::up_left_get_pos(int x, int y) {
//
//		float tempX = (112.0f + map_chip_space) * x;
//		float tempY = (64.0f + map_chip_space) * y;
//
//		tempX += map_spaceX;
//		tempY += map_spaceY;
//
//		return Vector2(tempX, tempY);
//}

//Vector2 MapGenerater::up_left_get_pos(const Vector2& position) {
//
//	float tempX = (112.0f + map_chip_space) * get_pos_numver(position).x;
//	float tempY = (64.0f + map_chip_space) * get_pos_numver(position).y;
//
//	tempX += map_spaceX;
//	tempY += map_spaceY;
//
//	return Vector2(tempX, tempY);
//}

// �m�肽���}�X��x�Ay���w�肷��Ƃ����̍�����W���Ԃ��Ă���
Vector2 MapGenerater::up_left_get_localpos(int x, int y) {

		float tempX = (112.0f + map_chip_space) * x;
		float tempY = (64.0f + map_chip_space) * y;

		return Vector2(tempX, tempY);
}

// �E���̍��W
Vector2 MapGenerater::down_right_get_pos(int x, int y)
{
	float tempX = (112.0f + map_chip_space) * x;
	float tempY = (64.0f + map_chip_space) * y;

	tempX += map_spaceX;
	tempY += map_spaceY;

	return Vector2(tempX + 112.0f, tempY + 64.0f);
}

// �E��̍��W
Vector2 MapGenerater::down_right_get_localpos(int x, int y)
{
	float tempX = (112.0f + map_chip_space) * x;
	float tempY = (64.0f + map_chip_space) * y;

	return Vector2(tempX + 112.0f, tempY + 64.0f);
}

// �w�肵�����W���ǂ̃}�b�v�ɑ����Ă��邩�𔻒肷��
Vector2 MapGenerater::get_pos_vector(Vector2 & position)
{
	// ���W�����p
	Vector2 mapVector{};

	// �}�b�v�̍���E���̍��W�Ǝ����̍��W�S�Ĕ�ׂ�
	for(int i = 0; i < map_X; ++i)
	{
		for (int j = 0; j < map_Y; ++j) {

			if (up_left_get_pos(i, j).x <= position.x && position.x <= down_right_get_pos(i, j).x &&
				up_left_get_pos(i, j).y <= position.y && position.y <= down_right_get_pos(i, j).y) {

				// �����ɓ��Ă͂܂���������
				mapVector = up_left_get_pos(i, j);
			}
			else {
				// �Ȃɂ����Ă͂܂�Ȃ��Ȃ��ԋ߂����W��Ԃ�
				return get_near_pos(position);
			}
		}
	}
	return mapVector;
}

// ���ׂ������W������΂��̍��W�̔z��ԍ����Ԃ��Ă���
Vector2 MapGenerater::get_pos_numver(const Vector2 & position)
{
	// ���W�����p
	Vector2 mapVector{};

	// �}�b�v�̍���E���̍��W�Ǝ����̍��W�S�Ĕ�ׂ�
	for (int i = 0; i < map_X; ++i)
	{
		for (int j = 0; j < map_Y; ++j) {
			if (up_left_get_pos(i, j).x <= position.x && position.x <= down_right_get_pos(i, j).x &&
				up_left_get_pos(i, j).y <= position.y && position.y <= down_right_get_pos(i, j).y) {

				// �����ɓ��Ă͂܂���������5
				mapVector = Vector2(i, j);
			}
			else {
				// ���Ă͂܂�Ȃ��Ȃ�for�����X�L�b�v
				continue;
			}
		}
	}
	return mapVector;
}

ToufuID MapGenerater::get_toufu_id(int x, int y)
{
	return toufu_map[y][x];
}

Vector3 MapGenerater::get_toufuPos_and_id(int x, int y)
{
	return Vector3(up_left_get_pos(x, y).x, up_left_get_pos(x, y).y, static_cast<int>(toufu_map[y][x]));
}

// �񎟌��z���x, y���w�肵�āA�ς������l�ɕς���(�l��MapChip)
void MapGenerater::set_map_Texture(int x, int y, Texture value) {
	if (x < 0 || y < 0 || x >= map_X || y >= map_Y) { return; }
	else { map[y][x] = value; }
}
// �񎟌��z���x, y���w�肵�āA�ς������l�ɕς���(���Vector2�o�[�W����)
void MapGenerater::set_map_Texture(const Vector2& position, Texture value) {
	if (get_pos_numver(position).x < 0 || get_pos_numver(position).y < 0 || get_pos_numver(position).x >= map_X || get_pos_numver(position).y >= map_Y) { return; }
	else { map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] = value; }
}

// �񎟌��z���x, y���w�肵�āA�ς������l�ɕς���(�l��int�^)
void MapGenerater::set_map_Int(int x, int y, int value) {

	// x�̒l��0��菬���� || y�̒l��0��菬�����@|| x�̒l��map_X�̗v�f�����傫�� || y�̒l��map_Y�̗v�f�����傫��
	if (x < 0 || y < 0 || x > map_X || y > map_Y) {
		// �X�L�b�v
		return;
	}
	// ���v�Ȃ�MapChip�ɕϊ����ē����
	map[y][x] = static_cast<Texture>(value);
}

// ���ڔz��̔Ԓn���w�肷��
void MapGenerater::set_map_toufu(int x, int y, ToufuID value)
{
	if (x < 0 || y < 0 || x > map_X || y > map_Y) {
		// �X�L�b�v
		return;
	}
	// ���v�Ȃ瓤�������Ă�t���O�����Ă���܂�����
	toufu_map[y][x] = value;
}

// �w�肵�����W�ɓ������d����
void MapGenerater::set_map_toufu(const Vector2 & position, ToufuID value)
{
	int numverX = static_cast<int>(get_pos_numver(position).x);
	int numverY = static_cast<int>(get_pos_numver(position).y);
	toufu_map[numverY][numverX] = value;
}

int MapGenerater::get_toufu_value() {
	int value{};
	for (int i = 0; i < map_Y; ++i) {
		for (int j = 0; j < map_X; ++j) {
			if (toufu_map[i][j] == ToufuID::Normal) {
				++value;
			}
		}
	}

	return value;
}

// ���ׂ��}�X�������ǂ����𒲂ׂ�
bool MapGenerater::check_hole(int x, int y) {
	return map[y][x] == Texture::Hole;
}

// ���ׂ��}�X�������ǂ����𒲂ׂ�
bool MapGenerater::check_hole(const Vector2& position) {
	return map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] == Texture::Hole;
}

bool MapGenerater::check_holeAndMetal(const Vector2& position) {
	return map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] == Texture::Hole ||
		   map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] == Texture::MetalToufuTile;
}

// ���������͓�������������true
bool MapGenerater::check_holeAndtoufu(int x, int y) {
	return map[y][x] == Texture::Hole || toufu_map[y][x] != ToufuID::None;
}

bool MapGenerater::check_toufu(int x, int y) {
	x = Math::Clamp(x, 0, 7);
	y = Math::Clamp(y, 0, 7);
	return toufu_map[y][x] != ToufuID::None;
}

void MapGenerater::clear_toufu()
{
	for (int i = 0; i < map_Y; ++i) {
		for (int j = 0; j < map_X; ++j) {
			toufu_map[i][j] = ToufuID::None;
		}
	}
}




// CSVLoader��������
int loader{ 0 };