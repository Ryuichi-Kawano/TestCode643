#include "Geometry.h"
#include<cmath>

float 
Rect::Left()const {
	return center.x - w;
}

float
Rect::Top()const {
	return center.y - h;
}
float
Rect::Right()const {
	return center.x + w;
}
float
Rect::Bottom()const {
	return center.y + h;
}


float 
Rect::Width()const {
	return 2.0f * w;
}
float 
Rect::Height()const {
	return 2.0f * h;
}

float 
Vector2::Magnitude()const {
	return std::hypot(x, y);
}
float 
Vector2::SQMagnitude()const {
	return x * x + y * y;
}

void 
Vector2::Normalize() {
	auto mag = Magnitude();
	x /= mag;
	y /= mag;
}
//ベクトルを正規化したベクトルを返す
Vector2 
Vector2::Normalized()const {
	auto mag = Magnitude();
	return Vector2(x / mag, y / mag);
}

void 
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void 
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}


Vector2 operator+(const Vector2& lval, const Vector2& rval) {
	return Vector2(lval.x + rval.x, lval.y + rval.y);
}

Vector2 operator-(const Vector2& lval, const Vector2& rval) {
	return Vector2(lval.x - rval.x, lval.y - rval.y);
}

//ベクトルのスカラー倍(n倍のこと)nV=(na,nb)
Vector2 operator*(const Vector2& lval, float scale) {
	return Vector2(scale * lval.x, scale * lval.y);
}

//ベクトルのスカラー割(nで割ったこと)V/n=(a/n,b/n)
Vector2 operator/(const Vector2& lval, float div) {
	return Vector2(lval.x / div, lval.y / div);
}
