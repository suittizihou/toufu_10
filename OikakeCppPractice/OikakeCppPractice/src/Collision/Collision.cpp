#include"Collision.h"

#include"Collision/Collision2D/Box/Box.h"
#include"Collision/Collision2D/Circle/Circle.h"

#include<DxLib.h>

bool Collision2D::Box_Box(const Box & box1, const Box & box2, HitInfo & hitInfo)
{
	//TODO@ÚG“_‚ð‹‚ß‚éB
	bool collisionX = box1.min.x + box1.size.x >= box2.min.x && box2.min.x + box2.size.x >= box1.min.x;
	bool collisionY = box1.min.y + box1.size.y >= box2.min.y && box2.min.y + box2.size.y >= box1.min.y;
	return collisionX && collisionY;
}

bool Collision2D::Circle_Circle(const Circle & circle1, const Circle & circle2, HitInfo & hitInfo)
{
	return (circle1.center - circle2.center).Length() <= (circle1.radius + circle2.radius);
}

bool Collision2D::Box_Circle(const Box & box, const Circle & circle, HitInfo & hitInfo)
{
	return false;
}
