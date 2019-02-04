#include "Vector2.h"

#include"Math\Math.h"

#include<iostream>
#include<cassert>

const Vector2 Vector2::Up(0.0f, 1.0f);
const Vector2 Vector2::Down(0.0f, -1.0f);
const Vector2 Vector2::Left(-1.0f, 0.0f);
const Vector2 Vector2::Right(1.0f, 0.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::Zero(0.0f, 0.0f);

Vector2::Vector2()
	: x(0.0f)
	, y(0.0f) {
}


Vector2::Vector2(float x, float y)
	: x(x)
	, y(y) {
}


Vector2::Vector2(const Vector2& vector)
	: x(vector.x)
	, y(vector.y) {
}

Vector2::~Vector2() {
}


float Vector2::Length() const
{
	return Math::SquareRoot(x * x + y * y);
}


float Vector2::SquareLength() const
{
	return x * x + y * y;
}


void Vector2::Normalize()
{
	*this / Length();
}


Vector2 Vector2::GetNormal() const
{
	float length = Length();
	return Vector2(x / length, y / length);
}


void Vector2::Print() const {
	std::cout << "Vector2 : [ X = " << x << " ] [ Y = " << y << " ]" << std::endl;
}


float Vector2::Dot(const Vector2 & vector)
{
	return x * vector.x + y * vector.y;
}


float Vector2::Cross(const Vector2 & vector)
{
	return x * vector.y - y * vector.x;
}


float Vector2::Distance(const Vector2 & vector)
{
	return (vector - Vector2(x, y)).Length();
}


bool Vector2::Clamp(const Vector2& min, const Vector2& max)
{
	float f_x = x;
	float f_y = y;
	x = Math::Clamp(x, min.x, max.x);
	y = Math::Clamp(y, min.y, max.y);
	return f_x < min.x || f_x > max.x|| f_y < min.y || f_y > max.y;
}

float Vector2::Angle(const Vector2 & vector)
{
	// θ = acos( vector1・vector2　 / |vector1| * |vector2|);
	// vector1とvector2が単位ベクトルの場合
	// 分母が１なので、分子のみの計算(内積)で済む
	return Math::ArcCos(Dot(vector.GetNormal()));
}

Vector2 Vector2::Lerp(const Vector2& vector, float lerpTime)
{
	if (lerpTime < 0.0f)
		return Vector2(x, y);
	if (lerpTime > 1.0f)
		return vector;

	return Vector2(x, y) * (1.0f - lerpTime) + vector * lerpTime;
}


Vector2 Vector2::Rotate(float angle)
{
	//
	//ベクトル回転　＝ [cosθ  -sinθ] [x]
	//				   [sinθ   cosθ] [y]

	float X = x * Math::Cos(angle) - y * Math::Sin(angle);
	float Y = x * Math::Sin(angle) + y * Math::Cos(angle);
	return Vector2(X, Y);
}

Vector2 Vector2::operator+()
{
	return *this;
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2 & vector) const
{
	return Vector2(x + vector.x, y + vector.y);
}

Vector2 Vector2::operator-(const Vector2 & vector) const
{
	return Vector2(x - vector.x, y - vector.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
	if (scalar == 0.0f) {
		assert(!"分母が0です。");
		return Vector2();
	}

	return Vector2(x / scalar, y / scalar);
}

Vector2& Vector2::operator+=(const Vector2 & vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 & vector)
{
	x -= vector.x;
	y -= vector.y;
	return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}


Vector2& Vector2::operator/=(float scalar)
{
	if (scalar == 0.0f) {
		assert(!"分母が0です。");
		return *this;
	}

	x /= scalar;
	y /= scalar;
	return *this;
}
