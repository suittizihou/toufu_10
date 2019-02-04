#include "Bezier.h"
#include"Math/Convert/Convert.h"

#include<DxLib.h>
#include"Utility/Color/Color.h"

Bezier::Bezier()
	: start()
	, control()
	, end()
{
}

Bezier::Bezier(const Vector3 & start, const Vector3 & control, const Vector3 & end)
	: start(start)
	, control(control)
	, end(end)
{
}

Bezier::Bezier(const Vector2 & start, const Vector2 & control, const Vector2 & end)
	: start(Vector3(start.x,start.y,0.0f))
	, control(Vector3(control.x, control.y, 0.0f))
	, end(Vector3(end.x, end.y, 0.0f))
{
}

Bezier::~Bezier()
{
}

void Bezier::Set(const Vector3 & start, const Vector3 & control, const Vector3 & end)
{
	this->start = start;
	this->control = control;
	this->end = end;
}

void Bezier::Set(const Vector2 & start, const Vector2 & control, const Vector2 & end)
{
	this->start = Vector3(start.x, start.y, 0.0f);
	this->control = Vector3(control.x, control.y, 0.0f);
	this->end = Vector3(end.x, end.y, 0.0f);
}

Vector3 Bezier::GetPointVec3(float t) const
{
	return (1.0f - t) * (1.0f - t) * start + 
		2.0f * (1.0f - t) * t * control + 
		t * t * end;
}

Vector2 Bezier::GetPointVec2(float t) const
{
	Vector3 result = (1.0f - t) * (1.0f - t) * start +
		2.0f * (1.0f - t) * t * control +
		t * t * end;
	return Vector2(result.x, result.y);
}

void Bezier::Draw() const
{
	for (float t = 0.0f; t <= 1.0f; t += 0.1f) {
		DrawLine3D(Convert::ToVECTOR(GetPointVec3(t)), Convert::ToVECTOR(GetPointVec3(t + 0.1f)), Color::Green.ToCOLOR());
	}
}
