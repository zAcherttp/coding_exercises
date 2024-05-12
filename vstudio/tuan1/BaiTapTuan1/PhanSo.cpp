#include "PhanSo.h"
#include <iostream>

PhanSo::PhanSo(const int x = 1, const int y = 1) : tu(x), mau(y) {}
PhanSo::~PhanSo() {}

std::istream &operator>>(std::istream &is, PhanSo &ps) {
    std::cout << "nhap tu: ";
    is >> ps.tu;
    std::cout << "nhap mau: ";
    is >> ps.mau;
    return is;
}
std::ostream &operator<<(std::ostream &os, const PhanSo &ps) {
    os << ps.tu << "/" << ps.mau;
    return os;
}

PhanSo PhanSo::rutGon() {
    int gcd = abs(tu);
    int temp = abs(mau);

    while (temp != 0) {
        int remainder = gcd % temp;
        gcd = temp;
        temp = remainder;
    }

    if (gcd != 0) {
        return PhanSo(tu /= gcd, mau /= gcd);
    }
    return PhanSo(tu, mau);
}

double PhanSo::getValue() {
    return (double)this->tu / this->mau;
}

PhanSo PhanSo::operator+(const PhanSo &ps) const {
    return PhanSo(tu * ps.mau + mau * ps.tu, mau * ps.mau);
}
PhanSo PhanSo::operator+=(const PhanSo &ps) {
    this->tu *= ps.mau;
    this->tu += mau * ps.tu;
    this->mau *= ps.mau;
}

PhanSo PhanSo::operator-(const PhanSo &ps) const {
    return PhanSo(tu * ps.mau - mau * ps.tu, mau * ps.mau);
}
PhanSo PhanSo::operator-=(const PhanSo &ps) {
    this->tu *= ps.mau;
    this->tu -= mau * ps.tu;
    this->mau *= ps.mau;
}

PhanSo PhanSo::operator*(const PhanSo &ps) const {
    return PhanSo(tu * ps.tu, mau * ps.mau);
}
PhanSo PhanSo::operator*=(const PhanSo &ps) {
    this->tu *= ps.tu;
    this->mau *= ps.mau;
}

PhanSo PhanSo::operator/(const PhanSo &ps) const {
    return PhanSo(tu * ps.mau, mau * ps.tu);
}
PhanSo PhanSo::operator/=(const PhanSo &ps) {
    this->tu *= ps.mau;
    this->mau *= ps.tu;
}
