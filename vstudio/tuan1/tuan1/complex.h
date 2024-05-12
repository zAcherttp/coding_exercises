#pragma once
class complex {
private:
    float r;
    float i;

public:
    complex(float _real = 0.0, float _im = 1.0);
    ~complex();

    void Nhap();
    void Xuat() const;

    const float getIm();
    const float getReal();
};
