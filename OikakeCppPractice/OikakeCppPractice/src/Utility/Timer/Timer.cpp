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
	//!���Z�b�g�@�������v�����邽��
	timer = maxTime;
}

void Timer::Update(float deltaTime) {
	timer = Math::Max(timer - (deltaTime / FPS::fps), 0.0f);

	// 0�b�ŃC�x���g���b�Z�[�W���΂��ăQ�[���G���h����
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
