#include <iostream>
#include <math.h>
#include <chrono>
#include <iomanip>
using namespace std;

////// a. b. c.

class PhanSo
{
public:
    int tu;
    int mau;

public:
    PhanSo() : tu(1), mau(1) {}
    PhanSo(const int x, const int y) : tu(x), mau(y) {}

    void nhapPhanSo()
    {
        cout << "nhap tu va mau: ";
        cin >> tu;
        cin >> mau;
        while (mau == 0)
        {
            cout << tu << "/";
            cin >> mau;
        }
    }

    void xuatPhanSo()
    {
        if ((double)tu / mau > 0)
        {
            tu = abs(tu);
            mau = abs(mau);
        }
        cout << tu << "/" << mau << endl;
    }

    double getValue()
    {
        return (double)tu / mau;
    }

    void rutGon()
    {
        // Euclidean algorithm
        int gcd = abs(tu);
        int temp = abs(mau);

        while (temp != 0)
        {
            int remainder = gcd % temp;
            gcd = temp;
            temp = remainder;
        }

        if (gcd != 0)
        {
            tu /= gcd;
            mau /= gcd;
        }
    }

    PhanSo operator+(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.mau + mau * ps.tu, mau * ps.mau);
    }

    PhanSo operator-(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.mau - mau * ps.tu, mau * ps.mau);
    }

    PhanSo operator*(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.tu, mau * ps.mau);
    }

    PhanSo operator/(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.mau, mau * ps.tu);
    }
};

////// d.

void xuatNgayKeTiep(int dd, int mm, int yyyy)
{
    tm InputTime;
    InputTime.tm_sec = 0;
    InputTime.tm_min = 0;
    InputTime.tm_hour = 0;
    InputTime.tm_mday = dd;
    InputTime.tm_mon = mm - 1;
    InputTime.tm_year = yyyy - 1900;

    time_t epochTime = mktime(&InputTime);
    epochTime += (60 * 60 * 24);
    tm *localTime = localtime(&epochTime);

    cout << "ngay tiep theo la: " << put_time(localTime, "%d/%m/%Y") << endl;
}

int main()
{
    char cau;
    cout << "chon cau (a, b, c, d): ";
    cin >> cau;
    PhanSo A, B, C, D, E, F;
    switch (cau)
    {
    case 'a':
        cout << "nhap phan so (tu mau): ";
        A.nhapPhanSo();
        A.rutGon();
        A.xuatPhanSo();
        cout << endl;
        cout << A.getValue();
        break;
    case 'b':
        cout << "nhap phan so (tu mau): ";
        A.nhapPhanSo();
        cout << "nhap phan so (tu mau): ";
        B.nhapPhanSo();
        (A.getValue() > B.getValue()) ? A.xuatPhanSo() : B.xuatPhanSo();
        break;
    case 'c':
        cout << "nhap phan so (tu mau): ";
        A.nhapPhanSo();
        cout << "nhap phan so (tu mau): ";
        B.nhapPhanSo();
        C = A + B;
        C.xuatPhanSo();
        D = A - B;
        D.xuatPhanSo();
        E = A * B;
        E.xuatPhanSo();
        F = A / B;
        F.xuatPhanSo();
        break;
    case 'd':
        int dd, mm, yyyy;
        cout << "nhap ngay thang nam (dd mm yyyy): ";
        cin >> dd >> mm >> yyyy;
        xuatNgayKeTiep(dd, mm, yyyy);
        break;
    }
    return 0;
}