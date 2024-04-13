#pragma once
#include <cmath>
class Point2D;

class Vector2D
{
public:
    float x;
    float y;

public:
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    void invert();
    float magnitude() const;
    float squareMagnitude() const;
    void normalize();

    void operator*=(float value);
    Vector2D operator*(float value) const;

    void operator+=(const Vector2D &v);
    Vector2D operator+(const Vector2D &v) const;
    Point2D operator+(const Point2D &p) const;

    void operator-=(const Vector2D &v);
    Vector2D operator-(const Vector2D &v) const;

    void addScaledVector(const Vector2D &v, float scale);
    float scalarProduct(const Vector2D &vector) const;

    float operator*(const Vector2D &vector) const;
};
