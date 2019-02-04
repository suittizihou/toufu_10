#include "Title.h"
#include"Renderer/Renderer.h"
#include "Scenes/Base/Scene.h"
#include"Input/Input.h"




Title::Title(WorldPtr & world)
	: isEnd(false)
	, world(world)
	, renderer(Renderer::GetInstance())
{
}

Title::~Title()
{
}

void Title::LoadAssets()
{
	renderer.LoadTexture(Assets::Texture::Title1, "title/title1.png");
	renderer.LoadTexture(Assets::Texture::Title2, "title/title2.png");
	renderer.LoadTexture(Assets::Texture::Title3, "title/title3.png");
	renderer.LoadTexture(Assets::Texture::Title4, "title/title4.png");
	renderer.LoadTexture(Assets::Texture::White, "title/white.png");
}

void Title::Initialize()
{
	isEnd = false;

	t1_pos.x = 1280.0f;
	t1_pos.y = 720.0f;
	t2_pos.x = -1280.0f;
	t2_pos.y = -720.0f;
	t3_pos.x = 1280.0f;

	t4_pos.x = -1280.0f;
	t4_pos.y = 720.0f;

	animeCount = 0;
	alpha = 0;
	count = 0;
	flashStart = true;
}

void Title::FirstUpdate(float deltaTime)
{
}

void Title::Update(float deltaTime)
{
	Input::GetInstance().Update();

	if ((Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_SPACE) || Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Start)) && 
		 animeCount == 5) {
 		isEnd = true;
	}

	TitleAnimation();


}

void Title::Draw() const
{
	//�ŏ��Ɏg�p����摜�S����`��
	renderer.DrawTexture(Assets::Texture::Title1,t1_pos);
	renderer.DrawTexture(Assets::Texture::Title2,t2_pos);
	renderer.DrawTexture(Assets::Texture::Title3, t3_pos);
	renderer.DrawTexture(Assets::Texture::Title4,t4_pos);
	renderer.DrawTexture(Assets::Texture::White, Vector2::Zero, Vector2(0,0), Vector2(1,1), NULL, Color(1.0f, 1.0f, 1.0f, alpha));
	

}

bool Title::IsEnd() const
{
	return isEnd;
}

Scene Title::Next() const
{
	return Scene::Description;
}

void Title::Finalize()
{
	renderer.Clear();
}

void Title::HandleMessage(EventMessage message, void * param)
{
}




void Title::TitleAnimation() {
	//�J�E���g�ɉ����ĉ摜���ړ�
//�^�C�g���P����
	if (animeCount == 0) {
		if (t1_pos.x > 0) {
			t1_pos.x -= 19.2f;
		}
		if (t1_pos.y > 0) {
			t1_pos.y -= 10.8f;
		}

		if (t1_pos.x < 0 && t1_pos.y < 0) {

			t1_pos.x = 0;
			t1_pos.y = 0;

			animeCount += 1;
		}
	}

	//�^�C�g���Q����
	if (animeCount == 1) {
		if (t2_pos.x < 0) {
			t2_pos.x += 19.2f;
		}
		if (t2_pos.y < 0) {
			t2_pos.y += 10.8f;
		}

		if (t2_pos.x > 0 && t2_pos.y > 0) {

			t2_pos.x = 0;
			t2_pos.y = 0;

			animeCount += 1;
		}
	}

	//�^�C�g���R����
	if (animeCount == 2) {
		if (t3_pos.x > 128) {
			t3_pos.x -= 37.2f;
		}

		if (t3_pos.x < 128) {

			t3_pos.x = 89.6f;
			animeCount += 1;
		}
	}

	//�^�C�g���S����
	if (animeCount == 3) {
		if (t4_pos.x < 0) {
			t4_pos.x += 25.6f;
		}
		if (t4_pos.y > 0) {
			t4_pos.y -= 14.4f;
		}

		if (t4_pos.x > 0) {
			t4_pos.x = 0;
		}
		if (t4_pos.y < 0) {
			t4_pos.y = 0;
		}

		if (t4_pos.x == 0 && t4_pos.y == 0) {
			animeCount += 1;
		}
	}

	//�t���b�V���I���i�Q���߁j
	if (!flashStart) {
		if (alpha != 0.0f) {
			alpha -= 0.1f;
			Draw();
		}
		if (alpha <= 0.0f) {
			alpha = 0.0f;
			animeCount = 5;
		}
	}


	//�t���b�V���n�܂�
	if (animeCount == 4 && flashStart) {

		if (alpha != 1.0f) {

			alpha += 0.1f;
			count = 0;
			Draw();

		}
		if (alpha >= 1.0f) {
			alpha = 1.0f;
			flashStart = false;
		}
	}



	//�X�y�[�X�L�[�ł��ׂẲ摜����C�ɕ\��
	if (animeCount < 4 && Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_SPACE) 
		|| Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Start)
		|| Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::A)) {
		t1_pos.x = 0.0f;
		t1_pos.y = 0.0f;
		t2_pos.x = 0.0f;
		t2_pos.y = 0.0f;
		t3_pos.x = 89.6f;
		t4_pos.x = 0.0f;
		t4_pos.y = 0.0f;

		animeCount = 4;
	}

}
