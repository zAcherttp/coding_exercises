#include "Vector2D.h"
#include "Point2D.h"
#include <iostream>
using namespace std;
Vector2D Point2D::operator-(const Point2D &p) const
{
    return Vector2D(x - p.x, y - p.y);
}

void Vector2D::invert()
{
    x = -x;
    y = -y;
}

float Vector2D::magnitude() const
{
    return sqrt(x * x + y * y);
}

float Vector2D::squareMagnitude() const
{
    return x * x + y * y;
}

void Vector2D::operator*=(float value)
{
    x *= value;
    y *= value;
}

void Vector2D::normalize()
{
    float l = magnitude();
    if (l > 0)
    {
        (*this) *= ((float)1) / l;
    }
}

Vector2D Vector2D::operator*(float value) const
{
    return Vector2D(x * value, y * value);
}

void Vector2D::operator+=(const Vector2D &v)
{
    x += v.x;
    y += v.y;
}

Vector2D Vector2D::operator+(const Vector2D &v) const
{
    return Vector2D(x + v.x, y + v.y);
}

Point2D Vector2D::operator+(const Point2D &p) const
{
    return Point2D(p.x + x, p.y + y);
}

void Vector2D::operator-=(const Vector2D &v)
{
    x -= v.x;
    y -= v.y;
}

Vector2D Vector2D::operator-(const Vector2D &v) const
{
    return Vector2D(x - v.x, y - v.y);
}

void Vector2D::addScaledVector(const Vector2D &v, float scale)
{
    x += v.x * scale;
    y += v.y * scale;
}

// tich vo huong
float Vector2D::scalarProduct(const Vector2D &vector) const
{
    return x * vector.x + y * vector.y;
}

// tich vo huong
float Vector2D::operator*(const Vector2D &vector) const
{
    return x * vector.x + y * vector.y;
}