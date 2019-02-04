#pragma once
enum class Character {
	None,
	Ninja,
	Kinniku,
	Yoroi,
	Kakutouka,
};

class CharacterManager {
public:
	CharacterManager()	{};
	~CharacterManager() {};

	static void SetCharacterP1(Character character);
	static void SetCharacterP2(Character character);

	static Character GetCharacterP1();
	static Character GetCharacterP2();
	
private:
	static Character chara[2];
};