#include "FadeManager.h"
#include "Application/Window/Window.h"
#include "Application\FPS\FPS.h"

FadeManager::FadeManager()
: fadeType(FadeType::FadeInWait)
, fadeAlpha(1.0f)
, fadeSpeed(1.0f / FPS::fps)
, fadeColor(Color::Black){

}

void FadeManager::Update(float deltaTime){
	ChangeAlpha(deltaTime);
	ChangeType();
#ifdef _DEBUG
	//printfDx("FadeAlpha:%f\n", m_Color.a);
#endif
}

void FadeManager::Draw()const{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, COLORTOINT(fadeColor.a));
	DrawBox(0, 0, Window::width,Window::height, fadeColor.ToCOLOR(), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FadeManager::FadeIn(float fadetime){
	fadeType = FadeType::FadeIn;
	fadeSpeed = -((1.0f / fadetime) /  FPS::fps);
	fadeColor.a = 1.0f;
}

void FadeManager::FadeOut(float fadetime, const Color& color){
	fadeType = FadeType::FadeOut;
	fadeSpeed = (1.0f / fadetime) / FPS::fps;
	fadeColor = color;
	fadeColor.a = 0.0f;
}

FadeType FadeManager::GetFadeType()const{
	return fadeType;
}

Color FadeManager::GetFadeColor() const{
	return fadeColor;
}


bool FadeManager::IsWaitFade()const{
	return fadeType == FadeType::FadeInWait || fadeType == FadeType::FadeOutWait;
}

bool FadeManager::IsEndFade() const
{
	if (fadeType == FadeType::FadeIn) {
		return fadeColor.a <= 0.0f;
	}
	if (fadeType == FadeType::FadeOut) {
		return fadeColor.a >= 1.0f;
	}
	return false;
}

void FadeManager::ChangeType(){
	// ï‚ä‘Ç™èIÇÌÇ¡ÇƒÇ¢ÇΩÇÁë“ã@èÛë‘Ç…ïœçX
	if (IsEndFade() && !IsWaitFade()){
		fadeType = fadeType == FadeType::FadeOut ? FadeType::FadeInWait : FadeType::FadeOutWait;
	}
}

void FadeManager::ChangeAlpha(float deltaTime){
	if (IsWaitFade()) return;
	fadeColor.a = Math::Max(0.0f, Math::Min(fadeColor.a + fadeSpeed * deltaTime, 1.0f));
}

