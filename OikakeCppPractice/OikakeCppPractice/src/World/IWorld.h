#pragma once

/**
 * @file IWorld.h
 * @brief アクターが共有するインターフェースクラス
 * @author 阿曽
 * @date 2015/09/12
 */

#include "Actor/Base/ActorPtr.h"
#include<string>

enum class ActorGroup;
enum class EventMessage;
struct SceneShareValue;

/*! @class IWorld
*	@brief  アクターが共有するインターフェースクラス
*/
class IWorld {
public:		
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IWorld() {}
	/// <summary>
	/// 前にアクターを追加する
	/// </summary>
	/// <param name="group">追加するグループ</param>
	/// <param name="actor">追加するアクターポインタ</param>
	virtual void AddActor_Front(ActorGroup group, const ActorPtr& actor) = 0;
	/// <summary>
	/// 後ろにアクターを追加する
	/// </summary>
	/// <param name="group">追加するグループ</param>
	/// <param name="actor">追加するアクターポインタ</param>
	virtual void AddActor_Back(ActorGroup group, const ActorPtr& actor) = 0;
	/// <summary>
	/// アクターを検索する
	/// </summary>
	/// <param name="name">検索するアクターの名前</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(const std::string& name) = 0;
	/// <summary>
	/// アクターを検索する
	/// </summary>
	/// <param name="group">検索するアクターのグループ</param>
	/// <param name="name">検索するアクターの名前</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr FindActor(ActorGroup group, const std::string& name) = 0;
	/// <summary>
	/// グループの親のポインタを取得する
	/// </summary>
	/// <param name="group">アクターのグループ</param>
	/// <returns>[true ActorPtr] : [false nullptr]</returns>
	virtual ActorPtr GetRoot(ActorGroup group) = 0;
	/// <summary>
	/// 全アクターにイベントメッセージを送信
	/// </summary>
	/// <param name="message">登録したイベントメッセージ</param>
	/// <param name="param">イベントと一緒に送る変数</param>
	virtual void SendEventMessage(EventMessage message, void* param = nullptr) = 0;
	/// <summary>
	/// シーン間で共有する変数を取得
	/// </summary>
	/// <returns>シーン間で共有する変数</returns>
	virtual SceneShareValue& GetSceneShareValue() = 0;
};
