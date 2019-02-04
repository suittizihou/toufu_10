#pragma once

#include"Math/Vector3/Vector3.h"
#include"Math/Vector2/Vector2.h"

/*
* éQçlÅFhttp://devmag.org.za/2011/04/05/bzier-curves-a-tutorial/
*/

class Bezier {
public:
	Bezier();
	Bezier(const Vector3& start, const Vector3& control, const Vector3& end);
	Bezier(const Vector2& start, const Vector2& control, const Vector2& end);
	~Bezier();
	void Set(const Vector3& start, const Vector3& control, const Vector3& end);
	void Set(const Vector2& start, const Vector2& control, const Vector2& end);
	Vector3 GetPointVec3(float t)const;
	Vector2 GetPointVec2(float t)const;
	void Draw() const;
private:
	Vector3 start;
	Vector3 control;
	Vector3 end;
};