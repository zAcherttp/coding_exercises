#pragma once
class PhanSo {
public:
    int tu;
    int mau;

public:
    PhanSo(const int x, const int y);
    ~PhanSo();

    friend std::istream &operator>>(std::istream &is, PhanSo &ps);
    friend std::ostream &operator<<(std::ostream &os, const PhanSo &ps);

    PhanSo rutGon();

    double getValue();

    PhanSo operator+(const PhanSo &ps) const;
    PhanSo operator+=(const PhanSo &ps);

    PhanSo operator-(const PhanSo &ps) const;
    PhanSo operator-=(const PhanSo &ps);

    PhanSo operator*(const PhanSo &ps) const;
    PhanSo operator*=(const PhanSo &ps);

    PhanSo operator/(const PhanSo &ps) const;
    PhanSo operator/=(const PhanSo &ps);
};
