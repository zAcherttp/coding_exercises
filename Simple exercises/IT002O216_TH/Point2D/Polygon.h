#pragma once
#include "Point2D.h"
#include "Vector2D.h"
class Polygon {
private:
    int size;
    Point2D *vertex;
    Point2D G;

public:
    Polygon(int _size);
    ~Polygon();
    void setValue();
    void translate(Vector2D &v);
    void rotate(Point2D &P, float angle);
    void resize(float scale);
};
