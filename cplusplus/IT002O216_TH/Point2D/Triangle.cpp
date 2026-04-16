#include "Triangle.h"

Triangle::Triangle(Point2D _A, Point2D _B, Point2D _C) : A(_A), B(_B), C(_C), G() {
    this->G.setValue((A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3);
}

Triangle::~Triangle() {
}

void Triangle::setValue(Point2D _A, Point2D _B, Point2D _C) {
    this->A = _A;
    this->B = _B;
    this->C = _C;
    this->G.setValue((A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3);
}

void Triangle::translate(Vector2D &v) {
    this->A.translate(v);
    this->B.translate(v);
    this->C.translate(v);
    this->G.translate(v);
}

void Triangle::rotate(Point2D &P, float angle) {
    this->A.setValue(P.x + (this->A.x - P.x) * cos(angle) + (this->A.y - P.y) * sin(angle),
                     P.y - (this->A.x - P.x) * sin(angle) + (this->A.y - P.y) * cos(angle));
    this->B.setValue(P.x + (this->B.x - P.x) * cos(angle) + (this->B.y - P.y) * sin(angle),
                     P.y - (this->B.x - P.x) * sin(angle) + (this->B.y - P.y) * cos(angle));
    this->C.setValue(P.x + (this->C.x - P.x) * cos(angle) + (this->C.y - P.y) * sin(angle),
                     P.y - (this->C.x - P.x) * sin(angle) + (this->C.y - P.y) * cos(angle));
    this->G.setValue(P.x + (this->G.x - P.x) * cos(angle) + (this->G.y - P.y) * sin(angle),
                     P.y - (this->G.x - P.x) * sin(angle) + (this->G.y - P.y) * cos(angle));
}

void Triangle::resize(float scale) {
    this->A = this->G + (this->A - this->G) * scale;
    this->B = this->G + (this->B - this->G) * scale;
    this->C = this->G + (this->C - this->G) * scale;
}
