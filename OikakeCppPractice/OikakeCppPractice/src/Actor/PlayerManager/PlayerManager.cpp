#include "PlayerManager.h"

int PlayerManager::p1hp{};
int PlayerManager::p2hp{};

Character PlayerManager::p1chara{};
Character PlayerManager::p2chara{};

Character PlayerManager::winer_chara{};
Character PlayerManager::loser_chara{};

void PlayerManager::SetP1Hp(int hp, Character chara)
{
	p1hp = hp;
	p1chara = chara;
}

void PlayerManager::SetP2Hp(int hp, Character chara)
{
	p2hp = hp;
	p2chara = chara;
}

int PlayerManager::GetP1Hp()
{
	return p1hp;
}

int PlayerManager::GetP2Hp()
{
	return p2hp;
}

void PlayerManager::Judge() {
	if (p1hp < p2hp) {
		winer_chara = p2chara;
		loser_chara = p1chara;
	}
	else if(p1hp > p2hp) {
		winer_chara = p1chara;
		loser_chara = p2chara;
	}
}

Assets::Texture PlayerManager::GetWiner()
{
	Judge();

	if (winer_chara == Character::Ninja) {
		return Assets::Texture::Result_Winner3;
	}
	else if (winer_chara == Character::Kinniku) {
		return Assets::Texture::Result_Winner1;
	}
	else if (winer_chara == Character::Kakutouka) {
		return Assets::Texture::Result_Winner2;
	}
	else if(winer_chara == Character::Yoroi){
		return Assets::Texture::Result_Winner4;
	}
	else {
		Assets::Texture::None;
	}
}

Assets::Texture PlayerManager::GetLoser()
{
	Judge();

	if (loser_chara == Character::Ninja) {
		return Assets::Texture::Result_Loser3;
	}
	else if (loser_chara == Character::Kinniku) {
		return Assets::Texture::Result_Loser1;
	}
	else if (loser_chara == Character::Kakutouka) {
		return Assets::Texture::Result_Loser2;
	}
	else if(loser_chara == Character::Yoroi) {
		return Assets::Texture::Result_Loser4;
	}
	else {
		return Assets::Texture::None;
	}
}
