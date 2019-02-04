#include "CharacterManager.h"

Character CharacterManager::chara[2]{};

void CharacterManager::SetCharacterP1(Character character)
{
	chara[0] = character;
}

void CharacterManager::SetCharacterP2(Character character)
{
	chara[1] = character;
}

Character CharacterManager::GetCharacterP1()
{
	return chara[0];
}

Character CharacterManager::GetCharacterP2()
{
	return chara[1];
}
