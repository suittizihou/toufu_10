#include "Input/Input.h"
#include "ResultMenu.h"
#include "Renderer/Renderer.h"

ResultMenu::ResultMenu(IWorld* world)
	: Actor2D(world, "ResultButton", Vector2::Zero, nullptr, 0)
{
	status = Status::Active;
}

ResultMenu::~ResultMenu() {

}

void ResultMenu::OnInitialize() {
	texture = static_cast<int>(Assets::Texture::Result_Menu1);
	select = 0;
}

void ResultMenu::OnUpdate(float deltaTime) {
	//if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_UP)) {
	//	--select;
	//}
	//if (Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_DOWN)) {
	//	++select;
	//}
	if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Up) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_UP)) {
		--select;
	}
	if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Down) || Input::GetInstance().GetKeyBoard().IsDown(KEY_INPUT_DOWN)) {
		++select;
	}

	// �Z���N�g�̒��g�͂O�`�Q�̊ԂɂƂǂ߂�
	select = Math::Clamp(select, 0, 2);

	// ���I�����Ă��郁�j���[���Z�b�g
	ResultManager::SetSelect(select);
}

void ResultMenu::OnDraw(Renderer & renderer) {
	// �I������Ă��郁�j���[�ɍ��킹�ĉ摜��؂�ւ���
	renderer.DrawTexture(static_cast<Assets::Texture>(texture + select));
}