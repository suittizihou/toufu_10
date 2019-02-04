#include "Matrix4.h"
#include"Math/Vector3/Vector3.h"
#include"Math/Math.h"
#include"Math/Quaternion/Quaternion.h"

const Matrix4 Matrix4::IdentityMatrix = Matrix4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

Matrix4::Matrix4()
{
	*this = Matrix4::IdentityMatrix;
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
	m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
	m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
	m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
}

Matrix4::Matrix4(const Quaternion & q)
{
	*this = Quaternion(q).ToRotateMatrix();
}


Matrix4::~Matrix4()
{
}

Matrix4 Matrix4::Scale(float x, float y, float z)
{
	Matrix4 matrix;
	matrix.m[0][0] = x;
	matrix.m[1][1] = y;
	matrix.m[2][2] = z;
	return matrix;
}

Matrix4 Matrix4::Scale(const Vector3 & scale)
{
	Matrix4 matrix;
	matrix.m[0][0] = scale.x;
	matrix.m[1][1] = scale.y;
	matrix.m[2][2] = scale.z;
	return matrix;
}

Matrix4& Matrix4::SetScale(float x, float y, float z)
{
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return *this;
}

Matrix4& Matrix4::SetScale(const Vector3 & scale)
{
	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
	return *this;
}

Vector3 Matrix4::GetScale() const
{
	return Vector3(GetLeft().Length(), GetUp().Length(), GetFront().Length());
}

Matrix4& Matrix4::SetPosition(float x, float y, float z)
{
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	return *this;
}

Matrix4& Matrix4::SetPosition(const Vector3 & position)
{
	m[3][0] = position.x;
	m[3][1] = position.y;
	m[3][2] = position.z;
	return *this;
}

Vector3 Matrix4::GetPosition() const
{
	return Vector3(m[3][0], m[3][1], m[3][2]);
}

Matrix4 Matrix4::RotateX(float angle)
{
	float cos = Math::Cos(angle);
	float sin = Math::Sin(angle);
	Matrix4 matrix;
	matrix.m[1][1] = cos;  matrix.m[1][2] = sin;
	matrix.m[2][1] = -sin; matrix.m[2][2] = cos;
	return matrix;
}

Matrix4 Matrix4::RotateY(float angle)
{
	float cos = Math::Cos(angle);
	float sin = Math::Sin(angle);
	Matrix4 matrix;
	matrix.m[0][0] = cos; matrix.m[0][2] = -sin;
	matrix.m[2][0] = sin; matrix.m[2][2] = cos;
	return matrix;
}

Matrix4 Matrix4::RotateZ(float angle)
{
	float cos = Math::Cos(angle);
	float sin = Math::Sin(angle);
	Matrix4 matrix;
	matrix.m[0][0] = cos;  matrix.m[0][1] = sin;
	matrix.m[1][0] = -sin; matrix.m[1][1] = cos;
	return matrix;
}

Matrix4 & Matrix4::SetRotateX(float angle)
{
	float cos = Math::Cos(angle);
	float sin = Math::Sin(angle);
	m[1][1] = cos;  m[1][2] = sin;
	m[2][1] = -sin; m[2][2] = cos;
	return *this;
}

Matrix4 & Matrix4::SetRotateY(float angle)
{
	float cos = Math::Cos(angle);
	float sin = Math::Sin(angle);
	m[0][0] = cos; m[0][2] = -sin;
	m[2][0] = sin; m[2][2] = cos;
	return *this;
}

Matrix4 & Matrix4::SetRotateZ(float angle)
{
	float cos = Math::Cos(angle);
	float sin = Math::Sin(angle);
	m[0][0] = cos;  m[0][1] = sin;
	m[1][0] = -sin; m[1][1] = cos;
	return *this;
}

Quaternion Matrix4::GetRotation() const
{
	return Quaternion(GetNormalizeRotationMatrix());
}

Matrix4 Matrix4::GetRotationMatrix() const
{
	return Matrix4(*this).SetPosition(Vector3::Zero);
}

Vector3 Matrix4::GetRotateAngle_Radian() const
{
	return CalculateAngleFromRotate() * Math::toRadian;
}

Vector3 Matrix4::GetRotateAngle_Degree() const
{
	return CalculateAngleFromRotate();
}

Matrix4 Matrix4::CreateWorld(const Vector3 & scale, const Quaternion & rotate, const Vector3 & translate)
{
	return Scale(scale) * CreateFromQuaternion(rotate) * Translate(translate);
}

Matrix4 Matrix4::CreateWorld(const Vector3 & scale, const Matrix4 & rotate, const Vector3 & translate)
{
	return Scale(scale) * rotate * Translate(translate);
}

Matrix4 Matrix4::CreateLookAt(const Vector3 & position, const Vector3 & forward, const Vector3 & up)
{
	Vector3 l = Vector3(up).Cross(forward).GetNormal();
	Vector3 u = Vector3(forward).Cross(l).GetNormal();
	Vector3 f = l.Cross(u);
	Matrix4 matrix;
	matrix.SetFront(f);
	matrix.SetUp(u);
	matrix.SetLeft(l);
	matrix.SetPosition(position);
	return matrix;
}

Matrix4 Matrix4::CreatePerspective(float fov, float aspect, float near_, float far_)
{
	float ys = 1.0f / Math::Tan(fov / 2.0f);
	float xs = ys / aspect;

	return Matrix4(
		xs,0.0f,0.0f,0.0f,
		0.0f,ys,0.0f,0.0f,
		0.0f,0.0f,(far_ + near_)/(near_ - far_),-1.0f,
		0.0f,0.0f,(2.0f*far_*near_)/(near_-far_),0.0f
		);
}

Matrix4 Matrix4::CreateView(const Vector3 & position, const Vector3 & target, const Vector3 & up)
{
	Vector3 z = (position - target).GetNormal();
	Vector3 x = Vector3(up).Cross(z).GetNormal();
	Vector3 y = z.Cross(x);

	return Matrix4(
		x.x,y.x,z.x,0.0f,
		x.y,y.y,z.y,0.0f,
		x.z,y.z,z.z,0.0f,
		-Vector3(position).Dot(x), -Vector3(position).Dot(y), -Vector3(position).Dot(z),1.0f
		);
}

Matrix4 Matrix4::CreateFromAxisAngle(const Vector3 & axis, float angle)
{
	return Quaternion(axis, angle).ToRotateMatrix();
}

Matrix4 Matrix4::CreateFromQuaternion(const Quaternion & rotate)
{
	return Quaternion(rotate).ToRotateMatrix();
}

Matrix4 Matrix4::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	return RotateZ(roll) * RotateY(pitch) * RotateX(yaw);
}

Vector3 Matrix4::CreateProjection(const Vector3 & position, const Matrix4 & screen, const Matrix4 & perspective, const Matrix4 & view, const Matrix4 & world)
{
	return position * world * view * perspective * screen;
}

Vector3 Matrix4::CreateUnProjection(const Vector3 & position, const Matrix4 & screen, const Matrix4 & perspective, const Matrix4 & view, const Matrix4 & world)
{
	Matrix4 inverce = world * view * perspective * screen;
	return position * inverce.Inverse();
}

Matrix4 Matrix4::CreateScreenDirectX(const Vector2 & position, float width, float height)
{
	float w = width / 2.0f;
	float h = height / 2.0f;

	return Matrix4(
		w,0,0,0,
		0,-h,0,0,
		0,0,1,0,
		w + position.x, h + position.y,0,1
		);
}

Matrix4 Matrix4::CreateScreenOpenGL(const Vector2 & position, float width, float height)
{
	float w = width / 2.0f;
	float h = height / 2.0f;

	return Matrix4(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, 1, 0,
		w + position.x, h + position.y, 0, 1
		);
}


Matrix4 Matrix4::Transpose()
{
	return Matrix4(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]
		);
}

Matrix4 Matrix4::Lerp(const Matrix4 & matrix, float amount)
{
	Vector3 scale = GetScale().Lerp(matrix.GetScale(), amount);
	Quaternion rotate = GetRotation().Slerp(matrix.GetRotation(), amount);
	Vector3 translation = GetPosition().Lerp(matrix.GetPosition(), amount);
	return Matrix4::CreateWorld(scale, rotate, translation);
}

void Matrix4::Decompose(Vector3 & scale, Quaternion & rotation, Vector3 & translation) const
{
	scale = GetScale();
	rotation = GetRotation();
	translation = GetPosition();
}

Matrix4& Matrix4::SetLeft(const Vector3 & left)
{
	Vector3 n = left.GetNormal();
	m[0][0] = n.x;
	m[0][1] = n.y;
	m[0][2] = n.z;
	return *this;
}

Matrix4& Matrix4::SetUp(const Vector3 & up)
{
	Vector3 n = up.GetNormal();
	m[1][0] = n.x;
	m[1][1] = n.y;
	m[1][2] = n.z;
	return *this;
}

Matrix4& Matrix4::SetFront(const Vector3 & front)
{
	Vector3 n = front.GetNormal();
	m[2][0] = n.x;
	m[2][1] = n.y;
	m[2][2] = n.z;
	return *this;
}

Vector3 Matrix4::GetLeft() const
{
	return Vector3(m[0][0], m[0][1], m[0][2]);
}

Vector3 Matrix4::GetUp() const
{
	return Vector3(m[1][0], m[1][1], m[1][2]);
}

Vector3 Matrix4::GetFront() const
{
	return Vector3(m[2][0], m[2][1], m[2][2]);
}

Matrix4 Matrix4::Translate(float x, float y, float z) 
{
	Matrix4 matrix;
	return matrix.SetPosition(x, y, z);
}

Matrix4 Matrix4::Translate(const Vector3 & translate)
{
	Matrix4 matrix;
	return 	matrix.SetPosition(translate);
}


Vector3 Matrix4::Transform(const Vector3 & vector) const
{
	//À•W•ÏŠ·
	float w = vector.x * m[0][3] + vector.y * m[1][3] + vector.z * m[2][3] + m[3][3];
	float x = (vector.x * m[0][0] + vector.y * m[1][0] + vector.z * m[2][0] + m[3][0]) / w;
	float y = (vector.x * m[0][1] + vector.y * m[1][1] + vector.z * m[2][1] + m[3][1]) / w;
	float z = (vector.x * m[0][2] + vector.y * m[1][2] + vector.z * m[2][2] + m[3][2]) / w;
	return Vector3(x, y, z);
}

Matrix4& Matrix4::Identity()
{
	*this = Matrix4::IdentityMatrix;
	return *this;
}

Matrix4 Matrix4::Inverse() const
{
	float a0 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	float a1 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
	float a2 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
	float a3 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
	float a4 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
	float a5 = m[0][2] * m[1][3] - m[0][3] * m[1][2];
	float b0 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
	float b1 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
	float b2 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
	float b3 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
	float b4 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
	float b5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
	float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	if (det == 0.0f) {
		return Matrix4(); // ‹ts—ñ‚ª‘¶Ý‚µ‚È‚¢I
	}
	float invDet = 1.0f / det;
	Matrix4 result = {
		(m[1][1] * b5 - m[1][2] * b4 + m[1][3] * b3) * invDet,
		(-m[0][1] * b5 + m[0][2] * b4 - m[0][3] * b3) * invDet,
		(m[3][1] * a5 - m[3][2] * a4 + m[3][3] * a3) * invDet,
		(-m[2][1] * a5 + m[2][2] * a4 - m[2][3] * a3) * invDet,
		(-m[1][0] * b5 + m[1][2] * b2 - m[1][3] * b1) * invDet,
		(m[0][0] * b5 - m[0][2] * b2 + m[0][3] * b1) * invDet,
		(-m[3][0] * a5 + m[3][2] * a2 - m[3][3] * a1) * invDet,
		(m[2][0] * a5 - m[2][2] * a2 + m[2][3] * a1) * invDet,
		(m[1][0] * b4 - m[1][1] * b2 + m[1][3] * b0) * invDet,
		(-m[0][0] * b4 + m[0][1] * b2 - m[0][3] * b0) * invDet,
		(m[3][0] * a4 - m[3][1] * a2 + m[3][3] * a0) * invDet,
		(-m[2][0] * a4 + m[2][1] * a2 - m[2][3] * a0) * invDet,
		(-m[1][0] * b3 + m[1][1] * b1 - m[1][2] * b0) * invDet,
		(m[0][0] * b3 - m[0][1] * b1 + m[0][2] * b0) * invDet,
		(-m[3][0] * a3 + m[3][1] * a1 - m[3][2] * a0) * invDet,
		(m[2][0] * a3 - m[2][1] * a1 + m[2][2] * a0) * invDet
	};
	return result;
}

Matrix4 Matrix4::InverseFast() const
{
	Matrix4 inverse_rotation = this->GetRotationMatrix().Transpose();
	Vector3 inverse_translate = inverse_rotation.Transform(-(*this).GetPosition());

	return inverse_rotation.Translate(inverse_translate);
}


Matrix4 Matrix4::GetNormalizeRotationMatrix() const
{
	return Matrix4(*this).NormalizeRotationMatrix();
}

Matrix4 & Matrix4::NormalizeRotationMatrix()
{
	Vector3 l = GetUp().Cross(GetFront()).GetNormal();
	Vector3 u = GetFront().Cross(l).GetNormal();
	Vector3 f = l.Cross(u);
	return SetFront(f).SetUp(u).SetLeft(l);
}

Vector3 Matrix4::CalculateAngleFromRotate() const
{
	//‚µ‚«‚¢’l
	static const float threshold = 0.001f;

	Vector3 angle;
	
	//m[2][1] = sin(x) = 1‚ÌŽž
	if (Math::Abs(m[2][1] - 1.0f) < threshold) {
		angle.x = Math::PI / 2.0f;
		angle.y = 0.0f;
		angle.z = Math::ArcTan(m[1][0], m[0][0]);
	}
	//m[2][1] = sin(x) = -1‚ÌŽž
	else if (Math::Abs(m[2][1] + 1.0f) < threshold) {
		angle.x = -(Math::PI / 2.0f);
		angle.y = 0.0f;
		angle.z = Math::ArcTan(m[1][0], m[0][0]);
	}
	//m[2][1] = sin(x) = -1 ` 1‚ÌŽž
	else {
		angle.x = Math::ArcSin(m[2][1]);
		angle.y = Math::ArcTan(-m[2][0], m[2][2]);
		angle.z = Math::ArcTan(-m[0][1], m[1][1]);
	}
	return angle;
}

Matrix4 Matrix4::operator*(const Matrix4 & matrix)
{
	return Multiply(*this, matrix);
}

Vector3 Matrix4::operator*(const Vector3 & vector)
{
	return Multiply(vector, *this);
}

Matrix4 & Matrix4::operator*=(const Matrix4 & matrix)
{
	*this = Multiply(*this, matrix);
	return *this;
}

Matrix4 Matrix4::Multiply(const Matrix4 & a, const Matrix4 & b)
{
	Matrix4 result;
	result.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0];
	result.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1];
	result.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2];
	result.m[0][3] = a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3];

	result.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0];
	result.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1];
	result.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2];
	result.m[1][3] = a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3];

	result.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0];
	result.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1];
	result.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2];
	result.m[2][3] = a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3];

	result.m[3][0] = a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0];
	result.m[3][1] = a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1];
	result.m[3][2] = a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2];
	result.m[3][3] = a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3];

	return result;
}

Vector3 Matrix4::Multiply(const Vector3 & vector, const Matrix4 & matrix)
{
	return Transform(vector);
}