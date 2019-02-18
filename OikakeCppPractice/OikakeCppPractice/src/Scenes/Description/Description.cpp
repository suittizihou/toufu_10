#include "Description.h"
#include"Renderer/Renderer.h"
#include "Scenes/Base/Scene.h"
#include"Input/Input.h"

Description::Description(WorldPtr & world)
	: isEnd(false)
	, world(world)
	, renderer(Renderer::GetInstance())
{
}

Description::~Description()
{
}

void Description::LoadAssets()
{
	renderer.LoadTexture(Assets::Texture::tutorial1, "tutorial/tutorial1.png");
	renderer.LoadTexture(Assets::Texture::tutorial2, "tutorial/tutorial2.png");
}

void Description::Initialize()
{
	isEnd = false;
	seSh = LoadSoundMem("asset/BGM&SE/tutorial_se.mp3");
}

void Description::FirstUpdate(float deltaTime)
{
}

void Description::Update(float deltaTime)
{
	Input::GetInstance().Update();
	/*
	A(enter)を押すと次の説明へ
	SEを鳴らす
	スタートかスペースで選択画面に移行
	*/
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_SPACE) || Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Start))
	{
		isEnd = true;
	}
	if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_RETURN) || Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::A))
	{
		PlaySoundMem(seSh, DX_PLAYTYPE_BACK);
		if (!isEnd)drawtex = false;
	}
}

void Description::Draw() const
{
	if(drawtex)renderer.DrawTexture(Assets::Texture::tutorial1);
	else renderer.DrawTexture(Assets::Texture::tutorial2);
}

bool Description::IsEnd() const
{
	return isEnd;
}

Scene Description::Next() const
{
	return Scene::CharacterSelect;
}

void Description::Finalize()
{
	renderer.Clear();
}

void Description::HandleMessage(EventMessage message, void * param)
{
}
