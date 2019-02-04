#pragma once

/**
 * @file World.h
 * @brief アクターが共有するクラス
 * @author 阿曽
 * @date 2015/9/12
 */

#include "IWorld.h"
#include "Actor/Base/ActorManager.h"
#include"SceneShareValue/SceneShareValue.h"

class Renderer;

/*! @class World
*   @brief  アクターが共有するクラス
*/
class World : public IWorld {
public:
	/// <summary>
	 /// コンストラクタ<see cref="World"/>
	 /// </summary>
	World();	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~World();	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();	

	void FirstUpdate(float deltaTime);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">1秒</param>
	void Update(float deltaTime);	
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="renderer">描画クラス</param>
	void Draw(Renderer& renderer);	
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();	
	/// <summary>
	/// 登録したアクターを全削除
	/// </summary>
	void Clear();
	/// <summary>
	/// 前にアクターを追加する
	/// </summary>
	/// <param name="group">追加するグループ</param>
	/// <param name="actor">追加するアクターポインタ</param>
	virtual void AddActor_Front(ActorGroup group, const ActorPtr& actor) override;
	/// <summary>
	/// 後ろにアクターを追加する
	/// </summary>
	/// <param name="group">追加するグループ</param>
	/// <param name="actor">追加するアクターポインタ</param>
	virtual void AddActor_Back(ActorGroup group, const ActorPtr& actor) override;
	/// <summary>
	/// アクターを検索する
	/// </summary>
	/// <param name="name">検索するアクターの名前</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(const std::string& name) override;
	/// <summary>
	/// アクターを検索する
	/// </summary>
	/// <param name="group">検索するアクターのグループ</param>
	/// <param name="name">検索するアクターの名前</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(ActorGroup group, const std::string& name) override;
	/// <summary>
	/// グループの親のポインタを取得する
	/// </summary>
	/// <param name="group">アクターのグループ</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr GetRoot(ActorGroup group) override;
	/// <summary>
	/// 全アクターにイベントメッセージを送信
	/// </summary>
	/// <param name="message">登録したイベントメッセージ</param>
	/// <param name="param">イベントと一緒に送る変数</param>
	virtual void SendEventMessage(EventMessage message, void* param = nullptr) override;

	/// <summary>
	/// シーン間で共有する変数を取得
	/// </summary>
	/// <returns>シーン間で共有する変数</returns>
	virtual SceneShareValue& GetSceneShareValue() override;


	/// <summary>
	 /// EventMessageを受け取る関数を登録 主にアクター以外が登録する
	 /// </summary>
	 /// <param name="listener">EventMessageを受け取る関数</param>
	void AddEventMessageListener(std::function<void(EventMessage, void*)> listener);
private:
	//!アクター管理クラス
	ActorManager actorManager;
	//!リスナー用の関数
	std::function<void(EventMessage, void*)> listener;
	//!シーン間で共有する変数
	SceneShareValue sceneShareValue;
};
