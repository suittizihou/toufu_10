#pragma once

/**
 * @file SceneNull.h
 * @brief ヌルポインタでエラーを吐かせないようにするデフォルトシーンの定義ファイル
 * @author 阿曽
 * @date Unknown
 */

#include "IScene.h"

 /*! @class SceneNull
 *   @brief  ヌルポインタでエラーを吐かせないようにするデフォルトシーン
 */
class SceneNull : public IScene {
public:
	virtual void LoadAssets() override;
	virtual void Initialize() override;
	virtual void FirstUpdate(float deltaTime);
	virtual void Update(float deltaTime)override;
	virtual void Draw() const override;
	virtual bool IsEnd() const override;
	virtual Scene Next() const override;
	virtual void Finalize() override;
};
