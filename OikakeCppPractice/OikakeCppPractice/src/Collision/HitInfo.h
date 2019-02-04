#pragma once

#include"Math/Vector3/Vector3.h"
#include"Actor/Base/ActorBase.h"
#include<vector>

/**
 * @file HitInfo.h
 * @brief あたり判定の情報をまとめた構造体定義ファイル
 * @author 阿曽
 * @date Unknown
 */


/*! @class HitInfo
 * @brief  あたり判定の情報をまとめた構造体
 */
class HitInfo {
public:
	/*! @struct CollideContent
	* @brief  1vs1の当たり判定をまとめた構造体
	*/
	struct CollideContent {
		//!接触した自分の当たり判定の番号
		int bodyID;
		//!接触した相手のActorBaseポインタ
		ActorBase* collideActor;
		//!接触点
		Vector3 intersect;
	};
public:	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	HitInfo()
		: contents(0)
		, collideActor(nullptr)
	{
	}
public:
	//!接触したアクターを保存しておく配列
	std::vector<CollideContent> contents;
	ActorBase* collideActor;

};
