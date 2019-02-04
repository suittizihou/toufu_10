#pragma once


#include "Scenes/Base/IScene.h"
#include"World/IWorld.h"
#include"World/WorldPtr.h"
#include"Math\Vector2\Vector2.h"

class Renderer;
enum class EventMessage;



/*! @class GameMainScene
*   @brief  ゲームメインシーン
*/
class Title : public IScene {
public:
	/**
	* @brief コンストラクタ
	* @param world ワールドポインタ
	*/
	explicit Title(WorldPtr& world);
	/**
	* @brief デストラクタ
	*/
	virtual ~Title();
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

	virtual void TitleAnimation();

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
	//!シーンが終了したか判定用
	bool isEnd;

private:
	Vector2 t1_pos;
	Vector2 t2_pos;
	Vector2 t3_pos;
	Vector2 t4_pos;


	//アニメーションもどき用カウント変数
	int animeCount;

	float alpha;
	int count;

	bool flashStart;
};
