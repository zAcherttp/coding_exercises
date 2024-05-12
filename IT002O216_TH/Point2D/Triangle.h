#pragma once
#include "Point2D.h"
#include "Vector2D.h"
class Triangle {
private:
    Point2D A;
    Point2D B;
    Point2D C;
    Point2D G;

public:
    Triangle(Point2D _A, Point2D _B, Point2D _C);
    ~Triangle();
    void setValue(Point2D _A, Point2D _B, Point2D _C);
    void translate(Vector2D &v);
    void rotate(Point2D &P, float angle);
    void resize(float scale);
};
