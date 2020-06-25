#include "Vector2D.h"

//コンストラクタ
Vector2D::Vector2D() :x(0), y(0)
{
}

//引数付きコンストラクタ
Vector2D::Vector2D(float x, float y) : x(x), y(y)
{
}

//演算子オーバーロード「+」
Vector2D Vector2D::operator+(const Vector2D&vec) {
	Vector2D t(this->x + vec.x, this->y + vec.y);

	return t;
}

//演算子オーバーロード「+=」
Vector2D & Vector2D::operator+=(const Vector2D & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

//演算子オーバーロード「-」
Vector2D Vector2D::operator-(const Vector2D & vec)
{
	Vector2D t(this->x - vec.x, this->y - vec.y);

	return t;
}

//演算子オーバーロード「-=」
Vector2D &Vector2D::operator-=(const Vector2D & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

//演算子オーバーロード「*」
Vector2D Vector2D::operator*(const float scale)
{
	Vector2D t(this->x * scale, this->y * scale);

	return t;
}

Vector2D Vector2D::operator*(const Vector2D & vec)
{
	Vector2D t(this->x * vec.x, this->y * vec.y);
	return t;
}



//演算子オーバーロード「/」
Vector2D Vector2D::operator/(const float scale)
{
	Vector2D t(this->x / scale, this->y / scale);

	return t;
}

//内積
float Vector2D::Dot(const Vector2D & vec)
{
	return this->x*vec.y + this->y*vec.x;
}

//外積
float Vector2D::Cross(const Vector2D & vec)
{
	return this->x*vec.y - this->y*vec.x;
}

//長さ
float Vector2D::Length()
{
	return sqrt(x * x + y * y);
}

float Vector2D::LengthSqrt()
{
	return this->Length()*this->Length();
}

//正規化
Vector2D Vector2D::Normalize()
{
	Vector2D t(0, 0);
	t.x = x / Length();
	t.y = y / Length();

	return t;
}


