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
// 724 181
void CharacterSelect::Initialize()
{
	isEnd = false;
}

void CharacterSelect::FirstUpdate(float deltaTime)
{
}

void CharacterSelect::Update(float deltaTime)
{
	Input::GetInstance().Update();

	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_A) || 
		LeftButton(awd))x = true;

	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_D) || 
		RightButton(awd))x = false;
	
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_W) || 
		UpButton(awd))y = true;
	
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_S) || 
		DownButton(awd))y = false;

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
				break;
			case Assets::Texture::choose2_walk:
				CharacterManager::SetCharacterP2(Character::Kakutouka);
				break;
			case Assets::Texture::choose3_walk:
				CharacterManager::SetCharacterP2(Character::Ninja);
				break;
			case Assets::Texture::choose4_walk:
				CharacterManager::SetCharacterP2(Character::Yoroi);
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
				break;
			case Assets::Texture::choose2_walk:
				CharacterManager::SetCharacterP1(Character::Kakutouka);
				break;
			case Assets::Texture::choose3_walk:
				CharacterManager::SetCharacterP1(Character::Ninja);
				break;
			case Assets::Texture::choose4_walk:
				CharacterManager::SetCharacterP1(Character::Yoroi);
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
		a++;
		time = 0;
		if (a == 4)a = 0;
	}
}

void CharacterSelect::Draw() const
{
	//�w�i
	renderer.DrawTexture(Assets::Texture::choosebase);
	//�L�����P
	if ( x &&  y)renderer.DrawTexture(Assets::Texture::choose1, Vector2(-60, -60), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else { renderer.DrawTexture(Assets::Texture::choose1); }
	//�L�����Q
	if (!x &&  y)renderer.DrawTexture(Assets::Texture::choose2, Vector2(-120, -60), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else { renderer.DrawTexture(Assets::Texture::choose2); }
	//�L�����R
	if ( x && !y)renderer.DrawTexture(Assets::Texture::choose3, Vector2(-60, -100), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else { renderer.DrawTexture(Assets::Texture::choose3); }
	//�L�����S
	if (!x && !y)renderer.DrawTexture(Assets::Texture::choose4, Vector2(-120, -110), Vector2(0, 0), Vector2(1.2f, 1.2f));
	else{ renderer.DrawTexture(Assets::Texture::choose4); }
	//�L�����̃A�j���[�V����
	renderer.DrawRectangle(tex_enum_p1, Vector2(874, 210), Rect(Vector2(181*a, 0),Vector2(181,181)));
	if(!awd) renderer.DrawRectangle(tex_enum_p2, Vector2(1035, 505), Rect(Vector2(181 * a, 0), Vector2(181, 181)));
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
