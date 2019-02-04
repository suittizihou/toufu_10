#include "Vector3.h"
#include "Math\Math.h"
#include"Math/Matrix4/Matrix4.h"
#include<iostream>
#include<cassert>

const Vector3 Vector3::Up = Vector3(0, 1, 0);
const Vector3 Vector3::Down = Vector3(0, -1, 0);
const Vector3 Vector3::Left = Vector3(-1, 0, 0);
const Vector3 Vector3::Right = Vector3(1, 0, 0);
const Vector3 Vector3::Backward = Vector3(0, 0, -1);
const Vector3 Vector3::Forward = Vector3(0, 0, 1);
const Vector3 Vector3::UnitX = Vector3(1, 0, 0);
const Vector3 Vector3::UnitY = Vector3(0, 1, 0);
const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);
const Vector3 Vector3::One = Vector3(1, 1, 1);
const Vector3 Vector3::Zero = Vector3(0, 0, 0);

Vector3::Vector3(float x, float y, float z)
	:x(x)
	, y(y)
	, z(z) {
}

Vector3::Vector3(const Vector3 & vector)
	: x(vector.x)
	, y(vector.y)
	, z(vector.z) {
}

Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0) {
}

Vector3::~Vector3() {
}


void Vector3::Normalize()
{
	*this /= Length();
}


Vector3 Vector3::GetNormal() const
{
	float length = Length();
	return Vector3(x / length, y / length, z / length);
}


float Vector3::Length() const
{
	return Math::SquareRoot(x * x + y * y + z * z);
}


float Vector3::SquareLength() const
{
	return x * x + y * y + z * z;
}


void Vector3::Print()
{
	std::cout << "Vector3 : [ X = " << x << " ] [ Y = " << y << " ] [ Z = " << z << "]" << std::endl;
}


void Vector3::Clamp(const Vector3 & min, const Vector3 & max)
{
	x = Math::Clamp(x, min.x, max.x);
	y = Math::Clamp(y, min.y, max.y);
	z = Math::Clamp(z, min.z, max.z);
}


float Vector3::Distance(const Vector3 & vec) const
{
	return (vec - Vector3(x, y, z)).Length();
}


float Vector3::DistanceSquare(const Vector3 & vec) const
{
	return (vec - Vector3(x, y, z)).SquareLength();
}


float Vector3::Angle(const Vector3 & vec) const
{
	float dot = GetNormal().Dot(vec.GetNormal());
	return Math::ArcCos(Math::Clamp(dot, -1.0f, 1.0f));
}



float Vector3::Dot(const Vector3 & vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}


Vector3 Vector3::Cross(const Vector3 & vec)
{
	return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}


Vector3 Vector3::Lerp(const Vector3 & vec, float lerpTime)
{
	return Vector3(
		Math::Lerp<float>(x, vec.x, lerpTime),
		Math::Lerp<float>(y, vec.y, lerpTime),
		Math::Lerp<float>(z, vec.z, lerpTime)
		);
}


Vector3 Vector3::Transform(const Matrix4 & matrix)
{
	return matrix.Transform(*this);
}


Vector3 Vector3::TransformNormal(const Matrix4 & matrix) const
{
	float _x = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0];
	float _y = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1];
	float _z = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2];
	return Vector3(_x, _y, _z);
}


Vector3 Vector3::CreateFromYawPitch(float yaw, float pitch)
{
	float _x = Math::Cos(pitch) * Math::Sin(yaw);
	float _y = -Math::Sin(pitch);
	float _z = Math::Cos(pitch) * Math::Cos(yaw);
	return Vector3(_x, _y, _z);
}


float Vector3::Pitch() const
{
	float length = Length();
	if (length == 0.0f) {
		assert(!"ï™ïÍÇ™0Ç≈Ç∑ÅB");
		return 0.0f;
	}
	return Math::ArcSin(-y / length);
}




float Vector3::Yaw() const
{
	if (Length() == 0.0f) {
		return 0.0f;
	}
	return Math::ArcTan(x, z);
}

Vector3 Vector3::operator+()
{
	return *this;
}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3 & vector) const
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator-(const Vector3 & vector) const
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(float scalar) const
{
	if (scalar == 0.0f) {
		assert(!"ï™ïÍÇ™0Ç≈Ç∑ÅB");
		return Vector3();
	}

	return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator+=(const Vector3 & vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3 & vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3& Vector3::operator/=(float scalar)
{
	if (scalar == 0.0f) {
		assert(!"ï™ïÍÇ™0Ç≈Ç∑ÅB");
		return *this;
	}

	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}