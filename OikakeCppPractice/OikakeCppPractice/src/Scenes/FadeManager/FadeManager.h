/**
* @file FadeManager.h
* @brief ゲームメインシーン定義ファイル
* @author 本山
* @date 2017/11/17
*
*/



#ifndef FADEMANAGER_H_
#define FADEMANAGER_H_

#include "Utility/Color/Color.h"

enum class FadeType{
	FadeInWait,	// フェードイン待
	FadeIn,		// フェードイン
	FadeOutWait,// フェードアウト待
	FadeOut,	// フェードアウト
};

class FadeManager{
public:
	FadeManager();
	void Update(float deltaTime);
	void Draw()const;
	void FadeIn(float fadetime = 1.0f);
	void FadeOut(float fadetime = 1.0f, const Color& color = Color::Black);

	Color GetFadeColor() const;
	FadeType GetFadeType() const;

private:
	bool IsWaitFade()const;
	bool IsEndFade()const;
	void ChangeType();
	void ChangeAlpha(float deltaTime);

private:
	FadeType fadeType;
	Color fadeColor;
	float fadeAlpha;
	float fadeSpeed;
};

#endif