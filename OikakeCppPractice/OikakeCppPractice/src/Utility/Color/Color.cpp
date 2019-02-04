#include"Color.h"

const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);


Color::Color()
	:Color(1.0f, 1.0f, 1.0f, 1.0f) {
}

Color Color::Lerp(const Color & color, float lerpTime)const
{
	return Lerp(*this, color, lerpTime);
}

Color Color::Lerp(const Color & color1, const Color & color2, float t)
{
	if (t < 0.0f)
		return color1;
	if (t > 1.0f)
		return color2;

	float r_ = Math::Lerp<float>(color1.r, color2.r, t);
	float g_ = Math::Lerp<float>(color1.g, color2.g, t);
	float b_ = Math::Lerp<float>(color1.b, color2.b, t);
	float a_ = Math::Lerp<float>(color1.a, color2.a, t);
	return Color(r_, g_, b_, a_);
}
