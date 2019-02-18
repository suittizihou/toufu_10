#pragma once

#include "Scenes/Base/IScene.h"
#include"World/IWorld.h"
#include"World/WorldPtr.h"
#include "Actor/UI/ResultMenu/ResultMenu.h"
#include "Actor/UI/ResultCharacter/ResultCharacter.h"
#include "../FadeManager/FadeManager.h"

#include "ResultManager.h"

class Renderer;
enum class EventMessage;

/*! @class GameMainScene
*   @brief  ゲームメインシーン
*/
class Result : public IScene {
public:
	/**
	* @brief コンストラクタ
	* @param world ワールドポインタ
	*/
	explicit Result(WorldPtr& world);
	/**
	* @brief デストラクタ
	*/
	virtual ~Result();
	/**
	* @brief アセットを読み込む
	*/
	virtual void LoadAssets() override;
	/**
	* @brief 初期化
	*/
	virtual void Initialize() override;

	virtual void FirstUpdate(float deltaTime);

	/**
	* @brief 更新
	* @param deltaTime １秒
	*/
	virtual void Update(float deltaTime)override;
	/**
	* @brief 描画
	*/
	virtual void Draw() const override;
	/**
	* @brief シーンが終了か判定
	* @return [true 終了] : [false まだ終了していない]
	*/
	virtual bool IsEnd() const override;
	/**
	* @brief 次に移動するシーンを取得
	* @return 次に移動するシーン
	*/
	virtual Scene Next()const override;
	/**
	* @brief 終了
	*/
	virtual void Finalize() override;

private:
	/**
	* @brief イベントメッセージを受け取る
	* @param message 登録したイベントメッセージ
	* @param param イベントと一緒に送る変数
	*/
	void HandleMessage(EventMessage message, void* param);

private:
	//!ワールドポインタ
	WorldPtr world;
	//!描画クラス
	Renderer& renderer;
	// リザルトマネージャー
	//ResultManager resultManager;
	// フェードアウトさせるための
	FadeManager fadeManager;
	//!シーンが終了したか判定用
	bool isEnd{};
	// ゲーム終了のフェードさせるための
	bool checkGameEnd{};
	// 現在選ばれているメニューの番号を入れるよう
	int select{};

	int bgmSh{};
};
