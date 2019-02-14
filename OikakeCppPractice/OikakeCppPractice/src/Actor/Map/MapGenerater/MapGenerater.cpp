#include "MapGenerater.h"
#include "Actor/Base/ActorGroup.h"
#include "../MapChip/MapChip.h"
#include "World/World.h"
#include "Math/Math.h"

using namespace Assets;

Assets::Texture MapGenerater::map[map_Y][map_X]{};
ToufuID MapGenerater::toufu_map[map_Y][map_X]{};

// コンストラクタ
MapGenerater::MapGenerater(WorldPtr& world) 
	: world(world){
	// CSVファイルの読み込み
	CSVLoader loader("map.csv");

	// マップデータをコピー
	for (int i = 0; i < map_Y; ++i) {
		for (int j = 0; j < map_X; ++j) {
			map[i][j] = static_cast<Texture>(loader.GetDataInt(j, i));
		}
	}
}

// 登録
void MapGenerater::AddMapChip() {
	for (int i = 0; i < map_Y; i++)
	{
		for (int j = 0; j < map_X; j++)
		{
			world->AddActor_Back(ActorGroup::BackGround, std::make_shared<MapChip>(world.get(), map[i][j], up_left_get_pos(j, i), 0));
		}
	}
}

// 指定した配列番号のマップタイルの情報を取得(戻り値はTexture)
Texture MapGenerater::get_mapChip(int x, int y) {
	//if (x < 0 || y < 0 || x >= map_X || y >= map_Y) { return Texture::None; }
	return map[y][x];
}
// Vector2バージョン
Texture MapGenerater::get_mapChip(const Vector2& position) {
	//if (x < 0 || y < 0 || x >= map_X || y >= map_Y) { return Texture::None; }
	return map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)];
}

// 最初のx, yには座標が入り、zにはマップの種類が入ります
Vector3 MapGenerater::get_posAndChip(int x, int y) {
	// 知りたい座標のマップチップ情報をint型に変換
	int tempChip = static_cast<int>(map[y][x]);

	float  tempX = 112.0f * x;
	float tempY = 64.0f * y;

	// Yは上が２マス空いているため
	tempX += map_spaceX;
	tempY += map_spaceY;

	return Vector3(tempX, tempY, static_cast<float>(tempChip));
}

// 今いる座標から一番近いタイルの座標を取得
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

// 知りたいマスのx、yを指定するとそこの左上座標が返ってくる
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

// 知りたいマスのx、yを指定するとそこの左上座標が返ってくる
Vector2 MapGenerater::up_left_get_localpos(int x, int y) {

		float tempX = (112.0f + map_chip_space) * x;
		float tempY = (64.0f + map_chip_space) * y;

		return Vector2(tempX, tempY);
}

// 右下の座標
Vector2 MapGenerater::down_right_get_pos(int x, int y)
{
	float tempX = (112.0f + map_chip_space) * x;
	float tempY = (64.0f + map_chip_space) * y;

	tempX += map_spaceX;
	tempY += map_spaceY;

	return Vector2(tempX + 112.0f, tempY + 64.0f);
}

// 右上の座標
Vector2 MapGenerater::down_right_get_localpos(int x, int y)
{
	float tempX = (112.0f + map_chip_space) * x;
	float tempY = (64.0f + map_chip_space) * y;

	return Vector2(tempX + 112.0f, tempY + 64.0f);
}

// 指定した座標がどのマップに属しているかを判定する
Vector2 MapGenerater::get_pos_vector(Vector2 & position)
{
	// 座標入れる用
	Vector2 mapVector{};

	// マップの左上右下の座標と自分の座標全て比べる
	for(int i = 0; i < map_X; ++i)
	{
		for (int j = 0; j < map_Y; ++j) {

			if (up_left_get_pos(i, j).x <= position.x && position.x <= down_right_get_pos(i, j).x &&
				up_left_get_pos(i, j).y <= position.y && position.y <= down_right_get_pos(i, j).y) {

				// 条件に当てはまったら入れる
				mapVector = up_left_get_pos(i, j);
			}
			else {
				// なにも当てはまらないなら一番近い座標を返す
				return get_near_pos(position);
			}
		}
	}
	return mapVector;
}

// 調べたい座標を入れればその座標の配列番号が返ってくる
Vector2 MapGenerater::get_pos_numver(const Vector2 & position)
{
	// 座標入れる用
	Vector2 mapVector{};

	// マップの左上右下の座標と自分の座標全て比べる
	for (int i = 0; i < map_X; ++i)
	{
		for (int j = 0; j < map_Y; ++j) {
			if (up_left_get_pos(i, j).x <= position.x && position.x <= down_right_get_pos(i, j).x &&
				up_left_get_pos(i, j).y <= position.y && position.y <= down_right_get_pos(i, j).y) {

				// 条件に当てはまったら入れる
				mapVector = Vector2(i, j);
			}
			else {
				// 当てはまらないならfor文をスキップ
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

ToufuID MapGenerater::get_toufu_id(const Vector2& position)
{
	return toufu_map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)];
}

Vector3 MapGenerater::get_toufuPos_and_id(int x, int y)
{
	return Vector3(up_left_get_pos(x, y).x, up_left_get_pos(x, y).y, static_cast<int>(toufu_map[y][x]));
}

// 二次元配列のx, yを指定して、変えたい値に変える(値がMapChip)
void MapGenerater::set_map_Texture(int x, int y, Texture value) {
	if (x < 0 || y < 0 || x >= map_X || y >= map_Y) { return; }
	else { map[y][x] = value; }
}
// 二次元配列のx, yを指定して、変えたい値に変える(上のVector2バージョン)
void MapGenerater::set_map_Texture(const Vector2& position, Texture value) {
	if (get_pos_numver(position).x < 0 || get_pos_numver(position).y < 0 || get_pos_numver(position).x >= map_X || get_pos_numver(position).y >= map_Y) { return; }
	else { map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] = value; }
}

// 二次元配列のx, yを指定して、変えたい値に変える(値がint型)
void MapGenerater::set_map_Int(int x, int y, int value) {

	// xの値が0より小さい || yの値が0より小さい　|| xの値がmap_Xの要素数より大きい || yの値がmap_Yの要素数より大きい
	if (x < 0 || y < 0 || x > map_X || y > map_Y) {
		// スキップ
		return;
	}
	// 大丈夫ならMapChipに変換して入れる
	map[y][x] = static_cast<Texture>(value);
}

// 直接配列の番地を指定する
void MapGenerater::set_map_toufu(int x, int y, ToufuID value)
{
	if (x < 0 || y < 0 || x > map_X || y > map_Y) {
		// スキップ
		return;
	}
	// 大丈夫なら豆腐入ってるフラグを建てたり折ったり
	toufu_map[y][x] = value;
}

// 指定した座標に豆腐を仕込む
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

// 調べたマスが穴かどうかを調べる
bool MapGenerater::check_hole(int x, int y) {
	return map[y][x] == Texture::Hole;
}

// 調べたマスが穴かどうかを調べる
bool MapGenerater::check_hole(const Vector2& position) {
	return map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] == Texture::Hole;
}

bool MapGenerater::check_holeAndMetal(const Vector2& position) {
	return map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] == Texture::Hole ||
		   map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] == Texture::MetalToufuTile;
}

// 穴もしくは豆腐があったらtrue
bool MapGenerater::check_holeAndtoufu(int x, int y) {
	return map[y][x] == Texture::Hole || toufu_map[y][x] != ToufuID::None;
}

bool MapGenerater::check_toufu(int x, int y) {
	x = Math::Clamp(x, 0, 7);
	y = Math::Clamp(y, 0, 7);
	return toufu_map[y][x] != ToufuID::None;
}

bool MapGenerater::check_toufu(const Vector2& position)
{	
	return toufu_map[static_cast<int>(get_pos_numver(position).y)][static_cast<int>(get_pos_numver(position).x)] != ToufuID::None;
}

void MapGenerater::clear_toufu()
{
	for (int i = 0; i < map_Y; ++i) {
		for (int j = 0; j < map_X; ++j) {
			toufu_map[i][j] = ToufuID::None;
		}
	}
}




// CSVLoaderを初期化
int loader{ 0 };