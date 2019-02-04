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
	// �������v���C���[�̃e�N�X�`����`��
	renderer.DrawTexture(PlayerManager::GetWiner());

	// �������v���C���[�̃e�N�X�`����`��
	renderer.DrawTexture(PlayerManager::GetLoser());
}
