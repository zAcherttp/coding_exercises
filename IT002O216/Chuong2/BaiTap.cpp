#include <iostream>
#include <math.h>
using namespace std;

class PhanSo
{
public:
    int tu;
    int mau;

public:
    PhanSo(const int x = 1, const int y = 1) : tu(x), mau(y) {}

    friend std::ostream &operator<<(std::ostream &os, const PhanSo &ps)
    {
        os << "(" << ps.tu << "/" << ps.mau << ")";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, PhanSo &ps)
    {
        is >> ps.tu >> ps.mau;
        return is;
    }

    double getValue()
    {
        return (double)tu / mau;
    }

    PhanSo rutGon()
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
            return PhanSo(tu /= gcd, mau /= gcd);
        }
        return PhanSo(tu, mau);
    }

    PhanSo operator+(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.mau + mau * ps.tu, mau * ps.mau);
    }
    PhanSo operator+=(const PhanSo &ps)
    {
        tu *= ps.mau;
        tu += mau * ps.tu;
        mau *= ps.mau;
        return *this;
    }

    PhanSo operator-(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.mau - mau * ps.tu, mau * ps.mau);
    }
    PhanSo operator-=(const PhanSo &ps)
    {
        tu *= ps.mau;
        tu -= mau * ps.tu;
        mau *= ps.mau;
        return *this;
    }

    PhanSo operator*(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.tu, mau * ps.mau);
    }
    PhanSo operator*=(const PhanSo &ps)
    {
        tu *= ps.tu;
        mau *= ps.mau;
        return *this;
    }

    PhanSo operator/(const PhanSo &ps) const
    {
        return PhanSo(tu * ps.mau, mau * ps.tu);
    }
    PhanSo operator/=(const PhanSo &ps)
    {
        tu *= ps.mau;
        mau *= ps.tu;
        return *this;
    }
};

struct DiemSo
{
    double Toan, Ly, Hoa;
    double DTB;
};

struct Student
{
    int MaHocSinh;
    string HoTen;
    string GioiTinh;
    DiemSo DiemSo;
};

void NhapThongTinHocSinh(Student &A)
{
    cout << "Nhap Ma Hoc Sinh: ";
    cin >> A.MaHocSinh;

    cout << "Nhap Ho Ten: ";
    cin.ignore();
    getline(cin, A.HoTen);

    cout << "Nhap Gioi Tinh: ";
    cin >> A.GioiTinh;

    cout << "Nhap diem Toan: ";
    cin >> A.DiemSo.Toan;
    cout << "Nhap diem Ly: ";
    cin >> A.DiemSo.Ly;
    cout << "Nhap diem Hoa: ";
    cin >> A.DiemSo.Hoa;
    A.DiemSo.DTB = round((A.DiemSo.Toan + A.DiemSo.Ly + A.DiemSo.Hoa) / 3 * 100) / 100;
}
void XuatThongTinHocSinh(Student &A)
{
    cout << "Ma Hoc Sinh: " << A.MaHocSinh << endl;
    cout << "Ho Ten: " << A.HoTen << endl;
    cout << "Gioi Tinh: " << A.GioiTinh << endl;
    cout << "Diem Trung Binh: " << A.DiemSo.DTB << endl;
}

int main()
{
    int cau;
    cout << "chon cau (1, 2, 3, 4): ";
    cin >> cau;
    switch (cau)
    {
    case 1:
    {
        PhanSo A, B;
        cin >> A >> B;

        cout << "tong = " << (A + B).rutGon();
        cout << "hieu = " << (A - B).rutGon();
        cout << "tich = " << (A * B).rutGon();
        cout << "thuong = " << (A / B).rutGon();
        break;
    }

    case 2:
    {
        int n;
        cout << "nhap kich thuoc day phan so: ";
        cin >> n;
        PhanSo day[n];
        PhanSo max = PhanSo(0, 1);
        PhanSo sum = PhanSo(0, 1);
        for (int i = 0; i < n; i++)
        {
            cin >> day[i];
            if (max.getValue() < day[i].getValue())
                max = day[i];
            sum += day[i];
        }
        cout << "phan so lon nhat: " << max << endl;
        cout << "tong day phan so: " << sum << endl;
        break;
    }

    case 3:
    { // nhap ma tran thu nhat
        int m;
        int n;
        cout << "Nhap so dong ma tran A: ";
        cin >> m;
        cout << "Nhap so cot ma tran A: ";
        cin >> n;
        int matA[m][n];
        cout << "Nhap ma tran A: " << endl;
        ;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cin >> matA[i][j];
        }
        // nhap ma tran B
        int a;
        int b;
        cout << "Nhap so dong ma tran B: ";
        cin >> a;
        cout << "Nhap so cot ma tran B: ";
        cin >> b;
        int matB[a][b];
        cout << "Nhap ma tran B: " << endl;
        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < b; j++)
                cin >> matB[i][j];
        }
        // tinh tong hieu
        if (a == m && b == n)
        {
            // tong
            cout << "Tong hai ma tran la: " << endl;
            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    cout << matA[i][j] + matB[i][j] << " ";
                }
                cout << endl;
            }
            // A-B
            cout << "Hieu hai ma tran A-B la: " << endl;
            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    cout << matA[i][j] - matB[i][j] << " ";
                }
                cout << endl;
            }
            // B-A
            cout << "Hieu hai ma tran B-A la: " << endl;
            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    cout << matB[i][j] - matA[i][j] << " ";
                }
                cout << endl;
            }
        }
        else
            cout << "Hai ma tran khong cung kich thuoc nen khong the tinh tong hieu." << endl;

        if (a == n && b == m)
        {
            // tich A*B
            int temp;
            cout << "Tich A*B la: " << endl;
            for (int i = 0; i < m; i++)
            { // dòng của A
                for (int k = 0; k < b; k++)
                { // cột của B
                    temp = 0;
                    for (int j = 0; j < n; j++)
                    { // cột của A & dòng của B
                        temp += matA[i][j] * matB[j][k];
                    }
                    cout << temp << " ";
                }
                cout << endl;
            }
            // tich B*A
            cout << "Tich B*A la: " << endl;
            for (int i = 0; i < a; i++)
            { // dòng của A
                for (int k = 0; k < n; k++)
                { // cột của B
                    temp = 0;
                    for (int j = 0; j < b; j++)
                    { // cột của A & dòng của B
                        temp += matB[i][j] * matA[j][k];
                    }
                    cout << temp << " ";
                }
                cout << endl;
            }
        }
        else
            cout << "Khong the tinh tich cua hai ma tran do khong thoa man dieu kien ve kich thuoc.";
        break;
    }

    case 4:
    {
        Student st;
        NhapThongTinHocSinh(st);
        XuatThongTinHocSinh(st);
        break;
    }

    default:
        break;
    }
    return 0;
}