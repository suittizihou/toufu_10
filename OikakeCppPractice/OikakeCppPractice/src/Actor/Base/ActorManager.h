#pragma once

#include "ActorPtr.h"
#include "ActorBase.h"
#include <unordered_map>
#include <functional>

enum class ActorGroup;
class Renderer;

/************************************************************
* File Name	: ActorManager.h
* Description	: アクター管理クラス
*																Date		:	2015-09-12.
*															  Author	:	阿曽
*************************************************************/
class ActorManager {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ActorManager();

	/// <summary>
	/// 初期化　
	/// </summary>
	void Initialize();

	void FirstUpdate(float deltaTime);

	/// <summary>
	/// 更新　
	/// </summary>
	void Update(float deltaTime);

	/// <summary>
	/// 描画
	/// 　</summary>
	void Draw(Renderer& renderer);

	/// <summary>
	/// 終了　
	/// </summary>
	void Finalize();

	/// <summary>
	/// 前に追加
	/// </summary>
	/// <param name="group">登録するアクターグループ</param>
	/// <param name="actor">登録するアクター</param>
	void AddActor_Front(ActorGroup group, const ActorPtr& actor);
	/// <summary>
	/// 後ろに追加
	/// </summary>
	/// <param name="group">登録するアクターグループ</param>
	/// <param name="actor">登録するアクター</param>
	void AddActor_Back(ActorGroup group, const ActorPtr& actor);

	/// <summary>
	/// アクターグループを追加する
	/// </summary>
	/// <param name="group">追加するアクターグループ</param>
	/// <param name="name">アクターグループの大本のアクターの名前</param>
	/// <param name="actor">アクターグループの大本のアクター</param>
	void AddGroup(ActorGroup group, const std::string& name = "none", const ActorPtr& actor = nullptr);

	/// <summary>
	/// 全アクターにメッセージを送信
	/// </summary>
	/// <param name="message">メッセージの種類</param>
	/// <param name="param">メッセージと一緒に送る変数</param>
	void HandleMessage(EventMessage message, void* param);
	/// <summary>
	/// 全アクターから名前で対象のアクターを探す
	/// </summary>
	/// <param name="name">アクターの名前</param>
	/// <returns>最初に名前と一致したアクターのポインタ</returns>
	ActorPtr FindActor(const std::string& name);
	/// <summary>
	/// グループから名前で対象のアクターを探す
	/// </summary>
	/// <param name="group">アクターグループ</param>
	/// <param name="name">アクターの名前</param>
	/// <returns>最初に名前と一致したアクターのポインタ</returns>
	ActorPtr FindActor(ActorGroup group, const std::string& name);
	/// <summary>
	/// グループの大本のアクターを取得
	/// </summary>
	/// <param name="group">アクターグループ</param>
	/// <returns>グループの大本のアクター</returns>
	ActorPtr GetRoot(ActorGroup group);
	/// <summary>
	/// 登録したアクターを全部削除
	/// </summary>
	void Clear();

	void sort(ActorGroup group);

private:
	/// <summary>
	/// グループを追加
	/// </summary>
	void RegisterGroup();
	/// <summary>
	/// 当たり判定をするグループを登録
	/// </summary>
	void Collide();

private:
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	//全アクターの大本
	ActorBase root;
	//グループ別に登録するアクター配列
	std::unordered_map<ActorGroup, ActorPtr> actors;

	int a = 0;
};