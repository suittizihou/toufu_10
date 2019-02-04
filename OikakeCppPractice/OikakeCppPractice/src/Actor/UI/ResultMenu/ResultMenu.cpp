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
	if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Up)) {
		--select;
	}
	if (Input::GetInstance().GetXBoxController().IsButtonDown(XboxGamePad::Dpad_Down)) {
		++select;
	}

	// セレクトの中身は０～２の間にとどめる
	select = Math::Clamp(select, 0, 2);

	// 今選択しているメニューをセット
	ResultManager::SetSelect(select);
}

void ResultMenu::OnDraw(Renderer & renderer) {
	// 選択されているメニューに合わせて画像を切り替える
	renderer.DrawTexture(static_cast<Assets::Texture>(texture + select));
}