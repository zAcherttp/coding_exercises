#include "Polygon.h"
#include <iostream>
using namespace std;

Polygon::Polygon(int _size) : size(_size) {
    float x, y;
    this->vertex = new Point2D[_size];
    for (int i = 0; i < _size; i++) {
        cout << "Nhap toa do diem thu " << i << ":";
        cin >> x >> y;
        vertex[i].setValue(x, y);
    }

    float x_ = 0, y_ = 0;

    for (int i = 0; i < _size; i++) {
        x_ += this->vertex[i].x;
        y_ += this->vertex[i].y;
    }
    this->G.setValue(x_ / _size, y_ / _size);
}

Polygon::~Polygon() {
    delete[] this->vertex;
}

void Polygon::setValue() {
    float x, y;
    for (int i = 0; i < this->size; i++) {
        cout << "Nhap toa do diem thu " << i << ":";
        cin >> x >> y;
        vertex[i].setValue(x, y);
    }

    float x_ = 0, y_ = 0;
    for (int i = 0; i < this->size; i++) {
        x_ += this->vertex[i].x;
        y_ += this->vertex[i].y;
    }
    this->G.setValue(x_ / this->size, y_ / this->size);
}

void Polygon::translate(Vector2D &v) {
    for (int i = 0; i < this->size; i++) {
        this->vertex[i] = this->vertex[i] + v;
    }
}

void Polygon::rotate(Point2D &P, float angle) {
    for (int i = 0; i < this->size; i++) {
        this->vertex[i].setValue(
            P.x + (this->vertex[i].x - P.x) * cos(angle) + (this->vertex[i].y - P.y) * sin(angle),
            P.y - (this->vertex[i].x - P.x) * sin(angle) + (this->vertex[i].y - P.y) * cos(angle));
    }
}

void Polygon::resize(float scale) {
    for (int i = 0; i < this->size; i++) {
        this->vertex[i] = this->G + (this->vertex[i] - this->G) * scale;
    }
}
