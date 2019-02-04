#include "MapChip.h"
#include "Renderer/Renderer.h"
#include "Collision/Collision2D/Box/Box.h"

#define STR(var) #var	// 引数にした変数を変数名を示す文字列リテラルとして返すマクロ関数

MapChip::MapChip(IWorld* world, Assets::Texture mapChip, const Vector2& position, const int& _number)
	: Actor2D(world, STR(mapChip), position, std::make_shared<Box>(Vector2::Zero, Vector2(106.0f, 50.0f)), _number)
	//, map(mapChip)
{
	status = Status::DrawOnly;
	body->isActive = false;
}

MapChip::~MapChip() {

}

void MapChip::OnDraw(Renderer& renderer) {

	renderer.DrawTexture(MapGenerater::get_mapChip(Average_Pos()), position, Vector2{ 0.0f, 0.0f }, Vector2{ 1.0f, 1.0f }, 0.0f, Color(255.0f, 255.0f, 255.0f, 1.0f));
}

Vector2 MapChip::Average_Pos() {
	Vector2 pos{ position.x + position.x + 112, position.y + position.y + 64 };
	return Vector2(pos.x / 2, pos.y / 2);
}