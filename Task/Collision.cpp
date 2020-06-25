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

//‰~‘Îü•ª‚Ì”»’è
bool Collision::Circle_LineCollision
(Vector2D &pc, float r, Vector2D& p1, Vector2D& p2)
{
	Vector2D vecSC = pc - p1;
	Vector2D VecEC = pc - p2;
	Vector2D VecSE = p2 - p1;

	float dist = vecSC.x * VecSE.Normalize().y - VecSE.Normalize().x*vecSC.y;


	float dot1 = vecSC.x*VecSE.x + vecSC.y*VecSE.y;
	float dot2 = VecEC.x*VecSE.x + VecEC.y*VecSE.y;

	if (fabs(dist) < r)
	{
		if (dot1*dot2 <= 0.0f)
		{
			if ((vecSC.Normalize().x < r&&vecSC.Normalize().y < r) || (VecEC.Normalize().x < r&&VecEC.Normalize().y < r))
			{
				return true;
			}
		}
	}
	return false;
}



