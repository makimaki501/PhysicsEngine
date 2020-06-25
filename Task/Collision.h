#pragma once
#include "Vector2D.h"

//�Փ˃N���X
class Collision
{
public:

	//	�~�Ή~�̔���
	bool CircleCollision(const  Vector2D& circleA, float aradius,
		const Vector2D& circleB, float bradius);

	//	��`�΋�`�̔���
	bool RectCollision(const Vector2D& rectPosA, const Vector2D& rectSizeA,
		const Vector2D& rectPosB, const Vector2D& rectSizeB);

	//�~�ΐ����̔���
	bool Circle_LineCollision(Vector2D& circle,float circleRadius
		, Vector2D& v1,Vector2D& v2);

};