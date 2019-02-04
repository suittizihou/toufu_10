#pragma once

#include"Utility/Color/Color.h"

/**
 * @file FPS.h
 * @brief ゲームのFPSを管理するクラス定義ファイル
 * @author 阿曽
 * @date Unknown
 */

 /*! @class FPS
 *   @brief ゲームのFPSを管理するクラス
 *   @detail (参考　http://dixq.net/g/03_14.html)
 */
class FPS {
public:	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FPS();	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~FPS();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// デバッグ用のFPS表示
	/// </summary>
	/// <param name="color">色</param>
	void Draw(const Color& color = Color::White);
	/// <summary>
	/// 今のフレーム(0.0　～　60.0)を取得
	/// </summary>
	/// <returns>今のフレーム</returns>
	float GetdeltaTime();
	/// <summary>
	/// 設定したFPSを超えたら待機する
	/// </summary>
	void Wait();

public:
	//!ゲームのFPS
	static const float fps;

private:
	//!平均を取るサンプル数
	const int AverageCount;
	//!fps
	float deltaTime;
	//!カウンタ
	int counter;
	//!測定開始時刻
	int startTime;
};