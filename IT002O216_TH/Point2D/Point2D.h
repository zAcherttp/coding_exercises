#pragma once
class Vector2D;
class Point2D
{
public:
	float x;
	float y;

public:
	Point2D(float _x = 0, float _y = 0) : x(_x), y(_y) {}
	~Point2D() {}
	float getX();
	float getY();
	void translate(Vector2D &v);
	Vector2D operator-(const Point2D &p) const;
	Point2D operator+(const Vector2D &v) const;
	void setValue(float _x, float _y);
	void print();
};
