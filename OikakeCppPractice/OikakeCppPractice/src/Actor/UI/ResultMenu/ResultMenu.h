#pragma once
#include "Actor/Base/Actor2D.h"
#include "Utility/Assets.h"
#include "Scenes/Result/ResultManager.h"

class ResultMenu : public Actor2D {
public:
	ResultMenu(IWorld* world);
	~ResultMenu();

private:
	virtual void OnInitialize() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw(Renderer& renderer)override;

private:
	int select{};
	int texture{ static_cast<int>(Assets::Texture::Result_Menu1) };
};