#include "Math.h"

const float Math::PI = 3.141592f;
const float Math::toDegree = 180.0f / PI;
const float Math::toRadian = PI / 180.0f;
const float Math::Epsilon = 1.192092896f;

float Math::SquareRoot(float value) {
	return static_cast<float>(std::sqrt(value));
}

float Math::Sin(float angle)
{
	return std::sinf(angle * toRadian);
}

float Math::Cos(float angle)
{
	return std::cosf(angle * toRadian);
}

float Math::Tan(float angle)
{
	return std::tanf(angle * toRadian);
}

float Math::ArcSin(float sin)
{
	return std::asinf(sin) * toDegree;
}

float Math::ArcCos(float cos)
{
	return std::acosf(cos) * toDegree;
}

float Math::ArcTan(float y, float x)
{
	return std::atan2f(y, x) * toDegree;
}

float Math::ArcTan(float tan)
{
	return std::atanf(tan) * toDegree;
}
