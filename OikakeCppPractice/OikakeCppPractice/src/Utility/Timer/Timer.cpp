#include "Timer.h"
#include"Application/FPS/FPS.h"

Timer::Timer(float setTime, std::function<void(void)> func)
	: maxTime(setTime)
	, timer(setTime)
	, func(func){
}

Timer::~Timer() {
}

void Timer::Initialize() {
	//!リセット　もう一回計測するため
	timer = maxTime;
}

void Timer::Update(float deltaTime) {
	timer = Math::Max(timer - (deltaTime / FPS::fps), 0.0f);

	// 0秒でイベントメッセージを飛ばしてゲームエンドする
	if (timer <= 0.0f) {
		func();
	}

}

bool Timer::IsTimeUp() const {
	return timer <= 0.0f;
}

float Timer::GetSecond() const {
	return timer;
}

float Timer::GetMaxTime() const {
	return maxTime;
}
