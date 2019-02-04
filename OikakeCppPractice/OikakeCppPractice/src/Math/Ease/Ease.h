#pragma once

/*
* Robert Penner's easing functions.
*
* See the following to learn more about these famous functions:
* http://www.robertpenner.com/easing/
*
* License:
* http://www.robertpenner.com/easing_terms_of_use.html
*/

/**
 * @file Ease.h
 * @brief 補間をまとめたクラスの定義ファイル
 * @author 阿曽
 * @date Unknown
 */


#include"Math/Math.h"
#include<cmath>

/*! @class Easing
 *   @brief  補間クラス
 */
class Easeing {
public:
	static float InBack(float t, float s = Difference) {
		return t * t * ((s + 1) * t - s);
	}
	static float InBounce(float t) {
		t = 1.0f - t;
		if (t < 1 / 2.75f) {
			return 1.0f - (7.5625f * t * t);
		}
		if (t < 2.0f / 2.75f) {
			t -= 1.5f / 2.75f;
			return 1.0f - (7.5625f * t * t + 0.75f);
		}
		if (t < 2.5f / 2.75f) {
			t -= 2.25f / 2.75f;
			return 1.0f - (7.5625f * t * t + 0.9375f);
		}
		t -= 2.625f / 2.75f;
		return 1.0f - (7.5625f * t * t + 0.984375f);
	}
	static float InCirc(float t) {
		return -Math::SquareRoot((1.0f - t * t) - 1.0f);
	}
	static float InCubic(float t) {
		return t * t * t;
	}
	static float InElastic(float t, float s = Difference) {
		float p = 0.3f;
		float a = 1.0f;
		if (t == 0.0f) {
			return 0.0f;
		}
		if (t == 1.0f) {
			return 1.0f;
		}
		if (a < 1.0f) {
			a = 1.0f;
			s = p / 4.0f;
		}
		else {
			s = p / (2.0f * Math::PI) * std::asin(1.0f / a);
		}
		t -= 1.0f;
		return -(a * std::pow(2.0f, 10.0f * t) * std::sin((t - s) * (2.0f * Math::PI) / p));
	}
	static float InExpo(float t) {
		return (t == 0) ? 0.0f : std::pow(2.0f, 10.0f * (t - 1.0f));
	}
	static float InQuad(float t) {
		return t * t;
	}
	static float InQuart(float t) {
		return t * t * t * t;
	}
	static float InSine(float t) {
		return -std::cos(t * (Math::PI / 2.0f)) + 1.0f;
	}

	static float  OutBack(float t, float s = Difference)
	{
		t -= 1.0f;
		return t * t * ((s + 1.0f) * t + s) + 1.0f;
	}

	static float  OutBounce(float t)
	{
		if (t < 1.0f / 2.75f) {
			return 7.5625f * t * t;
		}
		if (t < 2.0f / 2.75f) {
			t -= 1.5f / 2.75f;
			return 7.5625f * t * t + 0.75f;
		}
		if (t < 2.5f / 2.75f) {
			t -= 2.25f / 2.75f;
			return 7.5625f * t * t + 0.9375f;
		}
		t -= 2.625f / 2.75f;
		return 7.5625 * t * t + 0.984375;
	}

	static float  OutCirc(float t)
	{
		t -= 1.0f;
		return std::sqrt(1.0f - t * t);
	}

	static float  OutCubic(float t)
	{
		t -= 1.0f;
		return t * t * t + 1.0f;
	}

	static float  OutElastic(float t, float s = Difference)
	{
		float p = 0.3f;
		float a = 1.0f;
		if (t == 0.0f) {
			return 0.0f;
		}
		if (t == 1.0f) {
			return 1.0f;
		}
		if (a < 1.0f) {
			a = 1.0f;
			s = p / 4.0f;
		}
		else {
			s = p / (2.0f * Math::PI) * std::asin(1.0f / a);
		}
		return a * std::pow(2.0f, -10.0f * t) * sin((t - s) * (2.0f * Math::PI) / p) + 1.0f;
	}

	static float  OutExpo(float t)
	{
		return (t == 1.0f) ? 1.0f : (-std::pow(2.0f, -10.0f * t) + 1.0f);
	}

	static float  OutQuad(float t)
	{
		return -t * (t - 2.0f);
	}

	static float  OutQuart(float t)
	{
		t -= 1.0f;
		return 1.0 - t * t * t * t;
	}

	static float  OutQuint(float t)
	{
		t -= 1.0f;
		return t * t * t * t * t + 1.0f;
	}

	static float  OutSine(float t)
	{
		return std::sin(t * (Math::PI / 2.0f));
	}

	static float  InOutBack(float t, float s = Difference)
	{
		float k = 1.525f;
		t *= 2.0f;
		s *= k;
		if (t < 1) {
			return 0.5 * (t * t * ((s + 1) * t - s));
		}
		t -= 2;
		return 0.5 * (t * t * ((s + 1) * t + s) + 2);
	}

	static float  InOutBounce(float t)
	{
		return (t < 0.5f)
			? (InBounce(t * 2.0f) * 0.5f)
			: (OutBounce(t * 2.0f - 1.0f) * 0.5f + 0.5f);
	}

	static float  InOutCirc(float t)
	{
		t *= 2.0f;
		if (t < 1.0f) {
			return -0.5f * (Math::SquareRoot(1.0f - t * t) - 1.0f);
		}
		t -= 2.0f;
		return 0.5f * (Math::SquareRoot(1 - t * t) + 1);
	}

	static float  InOutCubic(float t)
	{
		t *= 2.0f;
		if (t < 1.0f) {
			return 0.5f * t * t * t;
		}
		t -= 2.0f;
		return 0.5f * (t * t * t + 2.0f);
	}

	static float  InOutElastic(float t, float s = Difference)
	{
		float p = 0.3f * 1.5f;
		float a = 1.0f;
		if (t == 0.0f) {
			return 0.0f;
		}
		if (t == 1.0f) {
			return 1.0f;
		}
		if (a < 1.0f) {
			a = 1.0f;
			s = p / 4.0f;
		}
		else {
			s = p / (2.0f * Math::PI) * std::asin(1.0f / a);
		}
		if (t < 1.0f) {
			t -= 1.0f;
			return -0.5f * (a * std::pow(2.0f, 10.0f * t) * std::sin((t - s) * (2.0f * Math::PI) / p));
		}
		t -= 1.0f;
		return a * std::pow(2.0f, -10.0f * t) * std::sin((t - s) * (2.0f * Math::PI) / p) * 0.5f + 1.0f;
	}

	static float  InOutExpo(float t)
	{
		if (t == 0.0f) {
			return 0.0f;
		}
		if (t == 1.0f) {
			return 1.0f;
		}
		t *= 2.0f;
		if (t < 1.0f) {
			return 0.5f * std::pow(2.0f, 10.0f * (t - 1.0f));
		}
		t -= 1.0f;
		return 0.5f * (-std::pow(2.0f, -10.0f * t) + 2.0f);
	}

	static float  InOutQuad(float t)
	{
		t *= 2.0f;
		if (t < 1.0f) {
			return 0.5f * t * t;
		}
		t -= 1.0f;
		return -0.5f * (t * (t - 2.0f) - 1.0f);
	}

	static float  InOutQuart(float t)
	{
		t *= 2.0f;
		if (t < 1.0f) {
			return 0.5f * t * t * t * t;
		}
		t -= 2.0f;
		return -0.5f * (t * t * t * t - 2.0f);
	}

	static float  InOutQuint(float t)
	{
		t *= 2.0f;
		if (t < 1.0f) {
			return 0.5f * t * t * t * t * t;
		}
		t -= 2.0f;
		return 0.5f * (t * t * t * t * t + 2.0f);
	}

	static float  InOutSine(float t)
	{
		return -0.5f * (std::cos(Math::PI * t) - 1.0f);
	}

private:
	/// <summary>行き過ぎた時の始値と終値の差分　</summary>
	static constexpr float Difference = 1.70158f;
};