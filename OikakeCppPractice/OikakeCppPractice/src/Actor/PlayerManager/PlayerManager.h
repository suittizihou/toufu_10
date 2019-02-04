#pragma once
#include "Scenes/CharacterSelect/CharacterManager.h"
#include "Utility/Assets.h"

class PlayerManager {
public:
	static void SetP1Hp(int hp, Character chara);
	static void SetP2Hp(int hp, Character chara);

	static int GetP1Hp();
	static int GetP2Hp();

	static Assets::Texture GetWiner();
	static Assets::Texture GetLoser();

	static void Judge();

private :
	static int p1hp;
	static int p2hp;

	static Character p1chara;
	static Character p2chara;

	static Character winer_chara;
	static Character loser_chara;
};