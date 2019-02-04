#pragma once
#include "Scenes/Base/IScene.h"

// ゲームを終了するためだけのシーン
class GameEnd : public IScene {
public:
	explicit GameEnd();
	virtual ~GameEnd();
	virtual void LoadAssets() override;
	virtual void Initialize()override;
	virtual void FirstUpdate(float deltaTime);
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void Finalize() override;
};