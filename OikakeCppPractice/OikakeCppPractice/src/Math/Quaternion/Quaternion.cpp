#include "Quaternion.h"
#include"Math/Math.h"
#include"Math/Vector3/Vector3.h"
#include"Math/Matrix4/Matrix4.h"
#include<cassert>

Quaternion::Quaternion(float x, float y, float z, float w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{
}

Quaternion::Quaternion(const Vector3 & axis, float angle)
{
	float sin = Math::Sin(angle / 2.0f);
	x = sin * axis.x;
	y = sin * axis.y;
	z = sin * axis.z;
	w = Math::Cos(angle / 2.0f);
}

Quaternion::Quaternion(const Matrix4 & m)
{
	float tr = m.m[0][0] + m.m[1][1] + m.m[2][2] + m.m[3][3];
	if (tr >= 1.0f) {
		float fourD = 2.0f * Math::SquareRoot(tr);
		x = (m.m[1][2] - m.m[2][1]) / fourD;
		y = (m.m[2][0] - m.m[0][2]) / fourD;
		z = (m.m[0][1] - m.m[1][0]) / fourD;
		w = fourD / 4.0f;
		return;
	}

	int i = 0;
	if (m.m[0][0] <= m.m[1][1]) {
		i = 1;
	}
	if (m.m[2][2] > m.m[i][i]) {
		i = 2;
	}

	int j = (i + 1) % 3;
	int k = (j + 1) % 3;

	tr = m.m[i][i] - m.m[j][j] - m.m[k][k] + 1.0f;
	float fourD = 2.0f * Math::SquareRoot(tr);
	float qa[4];

	qa[i] = fourD / 4.0f;
	qa[j] = (m.m[j][i] + m.m[i][j]) / fourD;
	qa[k] = (m.m[k][i] + m.m[i][k]) / fourD;
	qa[3] = (m.m[j][k] - m.m[k][j]) / fourD;

	x = qa[0];
	y = qa[1];
	z = qa[2];
	w = qa[3];
}

Quaternion::~Quaternion()
{
}

Quaternion & Quaternion::Normalize()
{
	float length = Length();

	if (length == 0.0f) {
		assert(!"ï™ïÍÇ™0Ç≈Ç∑ÅB");
		return *this;
	}

	*this /= length;

	return *this;
}

Quaternion Quaternion::GetNormal()
{
	return Quaternion(*this).Normalize();
}

float Quaternion::Dot(const Quaternion & q)
{
	return (x * q.x) + (y * q.y) + (z * q.z) + (w * q.w);
}

float Quaternion::Length()
{
	return Math::SquareRoot(this->Dot(*this));
}

Quaternion Quaternion::Slerp(const Quaternion & q, float amount)
{
	float cos_ = this->Dot(q);
	Quaternion t2 = q;
	if (cos_ < 0.0f) {
		cos_ = -cos_;
		t2 = -Quaternion(q);
	}

	float k0 = 1.0f - amount;
	float k1 = amount;

	if ((1.0f - cos_) > 0.001f) {
		float theta = std::acos(cos_);
		k0 = std::sin(theta*k0) / std::sin(theta);
		k1 = std::sin(theta*k1) / std::sin(theta);
	}

	return *this * k0 + t2 * k1;
}

Matrix4 Quaternion::ToRotateMatrix()
{
	float xx = x * x * 2.0f;
	float yy = y * y * 2.0f;
	float zz = z * z * 2.0f;
	float xy = x * y * 2.0f;
	float xz = x * z * 2.0f;
	float yz = y * z * 2.0f;
	float wx = w * x * 2.0f;
	float wy = w * y * 2.0f;
	float wz = w * z * 2.0f;

	return Matrix4(
		1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
		xy - wz, 1.0f - xx - zz, yz + wx, 0.0f,
		xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
}

Quaternion Quaternion::CreateFromRotationMatrix(const Matrix4 & m)
{
	return Quaternion(m);
}

Quaternion Quaternion::operator-()
{
	return Quaternion(-x, -y, -z, -w);
}

Quaternion & Quaternion::operator+=(const Quaternion & q)
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
	return *this;
}

Quaternion & Quaternion::operator-=(const Quaternion & q)
{
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;
	return *this;
}

Quaternion & Quaternion::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Quaternion & Quaternion::operator*=(const Quaternion & q)
{
	*this = Mul(*this, q);
	return *this;
}

Quaternion & Quaternion::operator/=(float scalar)
{
	if (scalar == 0.0f) {
		assert(!"ï™ïÍÇ™0Ç≈Ç∑ÅB");
		return *this;
	}

	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

Quaternion Quaternion::operator+(const Quaternion & q)
{
	return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion & q)
{
	return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion Quaternion::operator*(const Quaternion & q)
{
	return Mul(*this, q);
}

Quaternion Quaternion::operator*(float scalar)
{
	return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
}

Quaternion Quaternion::operator/(float scalar)
{
	if (scalar == 0.0f) {
		assert(!"ï™ïÍÇ™0Ç≈Ç∑ÅB");
		return Quaternion();
	}
	return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
}

Quaternion Quaternion::Mul(const Quaternion & q1, const Quaternion & q2)
{
	float x_ = q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x;
	float y_ = -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y;
	float z_ = q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z;
	float w_ = -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w;

	return Quaternion(x_, y_, z_, w_);
}