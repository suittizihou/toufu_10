#include "CharacterSelect.h"
#include"Renderer/Renderer.h"
#include "Scenes/Base/Scene.h"
#include"Input/Input.h"
#include "CharacterManager.h"

CharacterSelect::CharacterSelect(WorldPtr & world)
	: isEnd(false)
	, world(world)
	, renderer(Renderer::GetInstance())
{
}

CharacterSelect::~CharacterSelect()
{
}

void CharacterSelect::LoadAssets()
{
	renderer.LoadTexture(Assets::Texture::choosebase, "choose/choose.png");
	renderer.LoadTexture(Assets::Texture::choose1, "choose/choose_1.png");
	renderer.LoadTexture(Assets::Texture::choose2, "choose/choose_2.png");
	renderer.LoadTexture(Assets::Texture::choose3,"choose/choose_4.png");
	renderer.LoadTexture(Assets::Texture::choose4, "choose/choose_3.png");

	renderer.LoadTexture(Assets::Texture::choose1_walk, "choose/player1_anime_walk.png");
	renderer.LoadTexture(Assets::Texture::choose2_walk, "choose/player2_anime_walk.png");
	renderer.LoadTexture(Assets::Texture::choose3_walk, "choose/player3_anime_walk.png");
	renderer.LoadTexture(Assets::Texture::choose4_walk, "choose/player4_anime_walk.png");


}
void CharacterSelect::Initialize()
{
	isEnd = false;
	sceneBGM = LoadSoundMem("asset/BGM&SE/choose_bgm.mp3");
	cursorSound = LoadSoundMem("asset/BGM&SE/choose_se.mp3");
	enterSound = LoadSoundMem("asset/BGM&SE/choosed_se.mp3");
	PlaySoundMem(sceneBGM, DX_PLAYTYPE_LOOP, true);
	tex_enum = Assets::Texture::None;
	tex_enum_p1 = Assets::Texture::None;
	tex_enum_p2 = Assets::Texture::None;

	awd = true;
	time = 0;
	timeCount = 0;
}

void CharacterSelect::FirstUpdate(float deltaTime)
{
	
}

void CharacterSelect::Update(float deltaTime)
{
	Input::GetInstance().Update();

	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_A) ||
		LeftButton(awd)) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
		x = true;
	}
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_D) ||
		RightButton(awd)) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
		x = false;
	}
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_W) ||
		UpButton(awd)) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
		y = true;
	}
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_S) ||
		DownButton(awd)) {
		PlaySoundMem(cursorSound, DX_PLAYTYPE_BACK);
		y = false;
	}
	if (x  &&  y)tex_enum = Assets::Texture::choose1_walk;
	if (!x &&  y)tex_enum = Assets::Texture::choose2_walk;
	if (x && !y)tex_enum = Assets::Texture::choose4_walk;
	if (!x && !y)tex_enum = Assets::Texture::choose3_walk;


	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_RETURN) || AButton(awd))
	{
		if (!awd)
		{

			switch (tex_enum)
			{
			case Assets::Texture::choose1_walk:
				CharacterManager::SetCharacterP2(Character::Kinniku);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			case Assets::Texture::choose2_walk:
				CharacterManager::SetCharacterP2(Character::Kakutouka);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			case Assets::Texture::choose3_walk:
				CharacterManager::SetCharacterP2(Character::Ninja);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			case Assets::Texture::choose4_walk:
				CharacterManager::SetCharacterP2(Character::Yoroi);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			}
			isEnd = true;
		}
		else
		{
			switch (tex_enum)
			{
			case Assets::Texture::choose1_walk:
				CharacterManager::SetCharacterP1(Character::Kinniku);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			case Assets::Texture::choose2_walk:
				CharacterManager::SetCharacterP1(Character::Kakutouka);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			case Assets::Texture::choose3_walk:
				CharacterManager::SetCharacterP1(Character::Ninja);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			case Assets::Texture::choose4_walk:
				CharacterManager::SetCharacterP1(Character::Yoroi);
				PlaySoundMem(enterSound, DX_PLAYTYPE_BACK);
				break;
			}
			awd = false;
		}
	}


	if (awd)tex_enum_p1 = tex_enum;
	if(!awd)tex_enum_p2 = tex_enum;
	time++;
	if (time > 5)
	{
		timeCount++;
		time = 0;
		if (timeCount == 4)timeCount = 0;
	}
}

void CharacterSelect::Draw() const
{
	//îwåi
	renderer.DrawTexture(Assets::Texture::choosebase);
	//ÉLÉÉÉâÇP
	if ( x &&  y)renderer.DrawTexture(Assets::Texture::choose1, Vector2(-60, -60), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else { renderer.DrawTexture(Assets::Texture::choose1); }
	//ÉLÉÉÉâÇQ
	if (!x &&  y)renderer.DrawTexture(Assets::Texture::choose2, Vector2(-120, -60), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else { renderer.DrawTexture(Assets::Texture::choose2); }
	//ÉLÉÉÉâÇR
	if ( x && !y)renderer.DrawTexture(Assets::Texture::choose3, Vector2(-60, -100), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else { renderer.DrawTexture(Assets::Texture::choose3); }
	//ÉLÉÉÉâÇS
	if (!x && !y)renderer.DrawTexture(Assets::Texture::choose4, Vector2(-120, -110), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else{ renderer.DrawTexture(Assets::Texture::choose4); }
	//ÉLÉÉÉâÇÃÉAÉjÉÅÅ[ÉVÉáÉì
	renderer.DrawRectangle(tex_enum_p1, Vector2(874, 210), Rect(Vector2(181*timeCount, 0),Vector2(181,181)));
	if(!awd) renderer.DrawRectangle(tex_enum_p2, Vector2(1035, 505), Rect(Vector2(181 * timeCount, 0), Vector2(181, 181)));
}

bool CharacterSelect::IsEnd() const
{
	return isEnd;
}

Scene CharacterSelect::Next() const
{
	return Scene::GameMain;
}

void CharacterSelect::Finalize()
{
	renderer.Clear();
	StopSoundMem(sceneBGM);
}

void CharacterSelect::HandleMessage(EventMessage message, void * param)
{
}

bool CharacterSelect::UpButton(bool p1select)
{
	if (p1select) {
		return Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Up);
	}
	else {
		return Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::Dpad_Up);
	}
}

bool CharacterSelect::DownButton(bool p1select)
{
	if (p1select) {
		return Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Down);
	}
	else {
		return Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::Dpad_Down);
	}
}

bool CharacterSelect::LeftButton(bool p1select)
{
	if (p1select) {
		return Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Left);
	}
	else {
		return Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::Dpad_Left);
	}
}

bool CharacterSelect::RightButton(bool p1select)
{
	if (p1select) {
		return Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Right);
	}
	else {
		return Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::Dpad_Right);
	}
}

bool CharacterSelect::AButton(bool p1select)
{
	if (p1select) {
		return Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::A);
	}
	else {
		return Input::GetInstance().GetXBoxController().IsButtonDown2(XboxGamePad::A);
	}
}
