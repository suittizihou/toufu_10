#pragma once

#include"Application/GameApplication/GameApplication.h"

/**
 * @file GameFrame.h
 * @brief ゲームフレームワーク定義ファイル
 * @author 阿曽
 * @date Unknown
 */

#include"Scenes/Base/SceneManager.h"
#include"World/WorldPtr.h"

 /*! @class GameFrame
 *   @brief  ゲームフレームワーク
 */
class GameFrame : public GameApplication {
public:	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameFrame();	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameFrame();

private:	
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() override;	
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">1秒</param>
	virtual void Update(float deltaTime) override;
	
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() override;

	virtual void Reset() override;
	
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() override;
private:
	//!アクターで共有するワールドのポインタ
	WorldPtr world;
	//!シーン管理クラス
	SceneManager sceneManager;
};