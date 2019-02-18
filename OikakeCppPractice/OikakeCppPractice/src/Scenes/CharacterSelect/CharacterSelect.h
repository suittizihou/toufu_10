#pragma once


#include "Scenes/Base/IScene.h"
#include"World/IWorld.h"
#include"World/WorldPtr.h"
#include"Utility/Assets.h"

class Renderer;
enum class EventMessage;

/*! @class GameMainScene
*   @brief  ゲームメインシーン
*/
class CharacterSelect : public IScene
{
public:
	/**
	* @brief コンストラクタ
	* @param world ワールドポインタ
	*/
	explicit CharacterSelect(WorldPtr& world);
	/**
	* @brief デストラクタ
	*/
	virtual ~CharacterSelect();
	/**
	* @brief アセットを読み込む
	*/
	virtual void LoadAssets() override;
	/**
	* @brief 初期化
	*/
	virtual void Initialize() override;

	virtual void FirstUpdate(float deltaTime) override;

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
	bool UpButton(bool p1select);
	bool DownButton(bool p1select);
	bool LeftButton(bool p1select);
	bool RightButton(bool p1select);
	bool AButton(bool p1select);

private:
	//!ワールドポインタ
	WorldPtr world;
	//!描画クラス
	Renderer& renderer;
	//!シーンが終了したか判定用
	bool isEnd;

	bool x = true;
	bool y = true;
	Assets::Texture tex_enum;
	Assets::Texture tex_enum_p1;
	Assets::Texture tex_enum_p2;

	bool awd = true;
	int time = 0;
	int timeCount = 0;

	int sceneBGM = 0;
	int cursorSound = 0;
	int enterSound = 0;
};
