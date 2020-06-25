#include "Vector2D.h"

//�R���X�g���N�^
Vector2D::Vector2D() :x(0), y(0)
{
}

//�����t���R���X�g���N�^
Vector2D::Vector2D(float x, float y) : x(x), y(y)
{
}

//���Z�q�I�[�o�[���[�h�u+�v
Vector2D Vector2D::operator+(const Vector2D&vec) {
	Vector2D t(this->x + vec.x, this->y + vec.y);

	return t;
}

//���Z�q�I�[�o�[���[�h�u+=�v
Vector2D & Vector2D::operator+=(const Vector2D & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

//���Z�q�I�[�o�[���[�h�u-�v
Vector2D Vector2D::operator-(const Vector2D & vec)
{
	Vector2D t(this->x - vec.x, this->y - vec.y);

	return t;
}

//���Z�q�I�[�o�[���[�h�u-=�v
Vector2D &Vector2D::operator-=(const Vector2D & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

//���Z�q�I�[�o�[���[�h�u*�v
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



//���Z�q�I�[�o�[���[�h�u/�v
Vector2D Vector2D::operator/(const float scale)
{
	Vector2D t(this->x / scale, this->y / scale);

	return t;
}

//����
float Vector2D::Dot(const Vector2D & vec)
{
	return this->x*vec.y + this->y*vec.x;
}

//�O��
float Vector2D::Cross(const Vector2D & vec)
{
	return this->x*vec.y - this->y*vec.x;
}

//����
float Vector2D::Length()
{
	return sqrt(x * x + y * y);
}

float Vector2D::LengthSqrt()
{
	return this->Length()*this->Length();
}

//���K��
Vector2D Vector2D::Normalize()
{
	Vector2D t(0, 0);
	t.x = x / Length();
	t.y = y / Length();

	return t;
}


