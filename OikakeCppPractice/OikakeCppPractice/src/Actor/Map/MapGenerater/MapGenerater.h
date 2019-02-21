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

	// コンストラクタ
	MapGenerater(WorldPtr& world);
	~MapGenerater() {};

	void AddMapChip();

	// マップゲッター(タイル)
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
	static Vector2 down_right_get_pos(const Vector2& position);
	static Vector2 down_right_get_localpos(int x, int y);
	static Vector2 get_pos_vector(Vector2 & position);
	static Vector2 get_pos_numver(const Vector2 & position);

	// ゲッター(豆腐)
	static ToufuID get_toufu_id(int x, int y);
	static ToufuID get_toufu_id(const Vector2& position);
	static ToufuID get_toufu_id(const Vector2& position, int x, int y);
	static Vector3 get_toufuPos_and_id(int x, int y);

	// マップセッター(タイル)
	static void set_map_Texture(int x, int y, Assets::Texture value);
	// 上のVector2バージョン
	static void set_map_Texture(const Vector2& position, Assets::Texture value);
	static void set_map_Int(int x, int y, int value);

	// マップセッター(豆腐)
	static void set_map_toufu(int x, int y, ToufuID value);
	static void set_map_toufu(const Vector2 & position, ToufuID value);


	static int get_toufu_value();
	// 調べたマスが穴かどうか調べる(穴ならtrue)
	static bool check_hole(int x, int y);
	// 調べたマスが穴かどうか(Vector2)
	static bool check_hole(const Vector2& position);
	// 調べたマスが穴か、もしくは鉄タイルかを調べる
	static bool check_holeAndMetal(const Vector2& position);
	// 穴もしくは豆腐が無いかチェック
	static bool check_holeAndtoufu(int x, int y);
	// 調べたマスに豆腐があるか調べる(あったらtrue)
	static bool check_toufu(int x, int y);
	static bool check_toufu(const Vector2& position);
	static bool check_toufu(const Vector2& position, int x, int y);

	// 豆腐をリセット
	static void clear_toufu();

	static const int map_spaceX{ 178 };
	static const int map_spaceY{ 85 };
private:
	static const int map_X{ 8 };					// マップが横に何マスあるか
	static const int map_Y{ 8 };					// マップが縦に何マスあるか	
	static const int map_chip_space{ 4 };			// １マス１マスの間の隙間(ドット換算)
	static Assets::Texture map[map_Y][map_X];		// マップの種類とテクスチャ兼用
	static ToufuID toufu_map[map_Y][map_X];
	WorldPtr world;
	Vector3 mapPosition_And_Chip{ {0}, {0}, {0} };	// 最初のx,yには座標が入り、zにはマップの種類(Textureのint型)が入る
};