#include "ResultCharacter.h"
#include "Actor/PlayerManager/PlayerManager.h"
#include "Renderer/Renderer.h"

ResultCharacter::ResultCharacter(IWorld * world)
	: Actor2D(world, "ResultCharacter", Vector2::Zero, nullptr, 0)
{
}

ResultCharacter::~ResultCharacter()
{
}

void ResultCharacter::OnInitialize()
{
}

void ResultCharacter::OnUpdate(float deltaTime)
{
}

void ResultCharacter::OnDraw(Renderer & renderer)
{
	// 勝ったプレイヤーのテクスチャを描画
	renderer.DrawTexture(PlayerManager::GetWiner());

	// 負けたプレイヤーのテクスチャを描画
	renderer.DrawTexture(PlayerManager::GetLoser());
}
