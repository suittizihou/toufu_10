/**
* @file FadeManager.h
* @brief �Q�[�����C���V�[����`�t�@�C��
* @author �{�R
* @date 2017/11/17
*
*/



#ifndef FADEMANAGER_H_
#define FADEMANAGER_H_

#include "Utility/Color/Color.h"

enum class FadeType{
	FadeInWait,	// �t�F�[�h�C����
	FadeIn,		// �t�F�[�h�C��
	FadeOutWait,// �t�F�[�h�A�E�g��
	FadeOut,	// �t�F�[�h�A�E�g
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