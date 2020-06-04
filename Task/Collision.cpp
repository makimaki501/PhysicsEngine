#include "Collision.h"
#include<cmath>

//	‰~‘Î‰~‚Ì”»’è
bool Collision::CircleCollision(const Vector2D& circleA, float aradius, const Vector2D& circleB, float  bradius)
{
	auto x = abs((circleA.x + aradius) - (circleB.x + bradius));
	auto y = abs((circleA.y + aradius) - (circleB.y + bradius));

	return (sqrt(x * x + y * y) <= aradius + bradius);
}

//	‹éŒ`‘Î‹éŒ`‚Ì”»’è
bool Collision::RectCollision(const Vector2D& rectPosA, const Vector2D& rectSizeA, const Vector2D& rectPosB, const Vector2D& rectSizeB)
{
	auto dx = abs((rectPosA.x + rectSizeA.x / 2) - (rectPosB.x + rectSizeB.x / 2));
	auto dy = abs((rectPosA.y + rectSizeA.y / 2) - (rectPosB.y + rectSizeB.y / 2));

	return (dx < (rectSizeA.x + rectSizeB.x) / 2 && dy < (rectSizeA.y + rectSizeA.y) / 2);
}

