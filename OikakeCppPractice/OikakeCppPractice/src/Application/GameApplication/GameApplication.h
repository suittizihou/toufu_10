#pragma once

#include<string>
#include"Application\FPS\FPS.h"

/************************************************************
* File Name	: GameApplication.h
* Description	: ゲームフレームワークのベースクラス
*																Date		:	Unknown
*															  Author	:	阿曽
*************************************************************/

/**
 * @file GameApplication.h
 * @brief ゲームフレームワークのベースクラス定義ファイル
 * @author 阿曽
 * @date Unknown
 */

 /*! @class GameApplication
 *   @brief  ゲームフレームワークのベースクラス
 */
class GameApplication {
public:	
	/// <summary>
	/// ゲームを実行
	/// </summary>
	/// <returns>[0 正常終了: -1 起動失敗]</returns>
	int Run();	
	/// <summary>
	/// ウィンドウをシャットダウンする
	/// </summary>
	static void ShutDown();

protected:	
	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	GameApplication();
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~GameApplication();	
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() {};	

	virtual void FirstUpdate(float deltaTime) { static_cast<void>(deltaTime); };

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">1秒</param>
	virtual void Update(float deltaTime) { static_cast<void>(deltaTime); };	
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() {};	

	virtual void Reset() {};

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() {};

private:
	/// <summary>
	/// DXLIBの初期化	
	/// </summary>
	/// <returns>[true 初期化成功: false 初期化失敗]</returns>
	bool DxLibInit();	
	/// <summary>
	/// DXLIBの終了	
	/// </summary>
	void DxLibEnd();
	/// <summary>
	/// ウィンドウを閉じるかどうか？	
	/// </summary>
	/// <returns>
	/// [true 閉じる: false まだ閉じない]
	/// </returns>
	bool IsShutDown();

private:
	GameApplication(const GameApplication&) = delete;
	GameApplication& operator = (const GameApplication&) = delete;

private:
	//!ゲームのFPSを管理するクラス
	FPS fps;
	//!シャットダウンするかどうか
	static bool isShutDown;
	//TODO:修正　マウス情報だけもつのはおかしい
	int isMouseShow;
};