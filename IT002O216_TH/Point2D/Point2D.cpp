#include "Point2D.h"
#include "Vector2D.h"
#include <iostream>
using namespace std;
float Point2D::getX()
{
    return this->x;
}

float Point2D::getY()
{
    return this->y;
}

void Point2D::translate(Vector2D &v)
{
    *this = *this + v;
}

void Point2D::setValue(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}

void Point2D::print()
{
    cout << "( " << this->x << ", " << this->y << ")";
}

Point2D Point2D::operator+(const Vector2D &v) const
{
    return Point2D(x + v.x, y + v.y);
}