#include "Convert.h"

#include"Math/Vector2/Vector2.h"
#include"Math/Vector3/Vector3.h"
#include"Math/Matrix4/Matrix4.h"

VECTOR Convert::ToVECTOR(const Vector2 & vector)
{
	VECTOR v;
	v.x = vector.x;
	v.y = vector.y;
	v.z = 0.0f;
	return v;
}

VECTOR Convert::ToVECTOR(const Vector3 & vector)
{
	VECTOR v;
	v.x = vector.x;
	v.y = vector.y;
	v.z = vector.z;
	return v;
}

MATRIX Convert::ToMATRIX(const Matrix4 & matrix)
{
	MATRIX m;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m.m[i][j] = matrix.m[i][j];
		}
	}
	return m;
}

Vector2 Convert::ToVector2(const VECTOR & vector)
{
	return Vector2(vector.x, vector.y);
}

Vector2 Convert::ToVector2(const Vector3 & vector)
{
	return Vector2(vector.x, vector.y);
}

Vector3 Convert::ToVector3(const VECTOR & vector)
{
	return Vector3(vector.x, vector.y, vector.z);
}

Vector3 Convert::ToVector3_xz(const Vector2 & vector)
{
	return Vector3(vector.x,0.0f,vector.y);
}

Matrix4 Convert::ToMatrix4(const MATRIX & matrix)
{
	Matrix4 m;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m.m[i][j] = matrix.m[i][j];
		}
	}
	return m;
}