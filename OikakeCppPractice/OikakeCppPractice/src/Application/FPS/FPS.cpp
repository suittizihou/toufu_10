#include "FPS.h"
#include<DxLib.h>

const float FPS::fps = 60.0f;

FPS::FPS()
	: AverageCount(fps)
	, deltaTime(0.0f)
	, counter(0)
	, startTime(0)
{
}

FPS::~FPS()
{
}

void FPS::Update()
{
	//1フレーム目なら時刻を記憶
	if (counter == 0) {
		startTime = GetNowCount();
	}
	//設定した平均フレーム目なら平均を計算
	if (counter == AverageCount) {
		int t = GetNowCount();
		deltaTime = 1000.0f/*[ms]*/ / ((t - startTime) / static_cast<float>(AverageCount));
		counter = 0;
		startTime = t;
	}
	++counter;
}

void FPS::Draw(const Color& color)
{
	DrawFormatString(0, 0, color.ToCOLOR(), "SetFPS = %.1f : NowFPS = %.1f : deltaTime = %.3f", fps, deltaTime, deltaTime / fps);
}

float FPS::GetdeltaTime()
{
	return deltaTime / fps;
}

void FPS::Wait()
{
	//かかった時間
	int tookTime = GetNowCount() - startTime;	
	//待つべき時間
	int waitTime = counter * 1000/*[ms]*/ / fps - tookTime;	
	if (waitTime > 0) {
		//待機
		Sleep(waitTime);	
	}
}