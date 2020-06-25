#pragma once
#include "Vector2D.h"

//衝突クラス
class Collision
{
public:

	//	円対円の判定
	bool CircleCollision(const  Vector2D& circleA, float aradius,
		const Vector2D& circleB, float bradius);

	//	矩形対矩形の判定
	bool RectCollision(const Vector2D& rectPosA, const Vector2D& rectSizeA,
		const Vector2D& rectPosB, const Vector2D& rectSizeB);

	//円対線分の判定
	bool Circle_LineCollision(Vector2D& circle,float circleRadius
		, Vector2D& v1,Vector2D& v2);

};