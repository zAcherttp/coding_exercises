// 1. Viết chương trình nhập họ tên, điểm toán, điểm văn
// của một học sinh. Tính điểm trung bình, xếp loại và
// xuất kết quả.
//// check ✓

// 2. Viết chương trình nhập tọa độ tâm và bán kính của
// đường tròn. Tính diện tích và chu vi của đường tròn.
//// check ✓

// 3. Viết chương trình nhập vào tọa độ 2 điểm trong mặt
// phẳng Oxy. Tính khoảng cách giữa chúng và xuất kết
// quả.
//// check ✓

// 4. Cài đặt lớp cArray để biểu diễn mảng một chiều các
// số nguyên cho phép thực hiện các yêu cầu sau:
// ▪ Tạo lập mảng gồm n số nguyên ngẫu nhiên bằng
// constructor
//// check ✓
// ▪ Xuất mảng ra màn hình
//// check ✓
// ▪ Tìm số âm lớn nhất
//// check ✓
// ▪ Đếm lần xuất hiện của một số nguyên x
//// check ✓
// ▪ Kiểm tra mảng có giảm dần không
//// check ✓
// ▪ Sắp xếp mảng tăng dần
//// check ✓

// 5. Định nghĩa lớp cHocSinh gồm các thuộc tính:
// mã, họ tên, giới tính, năm sinh, điểm trung bình và
// các phương thức cần thiết.
//// check ✓
// Viết chương trình cho phép người dùng nhập thông
// tin 2 học sinh.
//// check ✓
// - Cho biết học sinh nào có điểm trung bình cao hơn.
//// check ✓
// - Cho biết học sinh nào có tuổi nhỏ hơn
//// check ✓

// 6. Cài đặt lớp số phức để biểu diễn khái niệm số phức (một
// số phức bao gồm hai thành phần: phần ảo, phần thực).
// Cho phép thực hiên các thao tác sau:
// - Tạo lập số phức khi biết phần thực và ảo
//// check ✓
// - Thay đổi phần thực, phần ảo
//// check ✓
// - Lấy giá trị phần thực, phần ảo
//// check ✓
// - Nhập số phức
//// check ✓
// - Xuất số phức
//// check ✓
// - Công hai số phức.
//// check ✓
// ▪ Viết chương trình minh họa
//   các chức năng của
//   lớp số phức
//// check ✓

#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

#define name(var) #var

/////////////////////////// cau 1.
struct DiemSo
{
    double Toan, Van;
    double DTB;
};

struct Student
{
    string HoTen;
    DiemSo diemSo;
    string XepLoai;
};

void NhapThongTinHocSinh(Student &A)
{
    cout << "Nhap Ho Ten: ";
    cin.ignore();
    getline(cin, A.HoTen);

    cout << "Nhap diem Toan: ";
    cin >> A.diemSo.Toan;
    cout << "Nhap diem Van: ";
    cin >> A.diemSo.Van;

    A.diemSo.DTB = round((A.diemSo.Toan + A.diemSo.Van) / 2 * 100) / 100;

    if (A.diemSo.DTB > 10)
    {
        A.XepLoai = "undefined";
        return;
    }

    static const char *xeploai[] = {"Xuat Sac", "Gioi", "Kha", "TB Kha", "TB", "Yeu", "Kem"};
    int i = 9 - int(A.diemSo.DTB);
    A.XepLoai = xeploai[i >= 0 && i < (sizeof(xeploai) / sizeof(xeploai[0])) ? i : 6];
}

void XuatThongTinHocSinh(Student &A)
{
    cout << "Ho Ten: " << A.HoTen << endl;
    cout << "Diem Trung Binh: " << fixed << setprecision(2) << A.diemSo.DTB << endl;
    cout << "Xep Loai: " << A.XepLoai << endl;
}

/////////////////////////// cau 2 + 3.
class point2D
{
private:
    int x;
    int y;

public:
    point2D(const int _x = 0, const int _y = 0) : x(_x), y(_y) {}

    friend ostream &operator<<(ostream &os, const point2D &p)
    {
        os << '(' << p.x << ", " << p.y << ')';
        return os;
    }
    friend istream &operator>>(istream &is, point2D &p)
    {
        cout << "x" << '\t' << "= ";
        is >> p.x;
        cout << "y" << '\t' << "= ";
        is >> p.y;
        return is;
    }

    float distance(point2D &A)
    {
        return sqrt(pow((A.x - x), 2) + pow((A.y - y), 2));
    }
};

/////////////////////////// cau 4.
#define randomRange 100

class cArray
{
private:
    int size;
    int *array;

public:
    cArray(int _size) : size(_size), array(new int[_size])
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(-randomRange, randomRange);
        for (int i = 0; i < _size; i++)
        {
            array[i] = distribution(gen);
        }
    }

    friend ostream &operator<<(ostream &os, const cArray &obj)
    {
        os << '{';
        for (int i = 0; i < obj.size - 1; i++)
        {
            os << obj.array[i] << ", ";
        }
        os << obj.array[obj.size - 1] << '}';
        return os;
    }

    int getSize()
    {
        return size;
    }

    const int *getArray()
    {
        return array;
    }

    int soAmLonNhat()
    {
        vector<int> negArr;
        for (int i = 0; i < size; i++)
        {
            if (array[i] < 0)
            {
                negArr.push_back(array[i]);
            }
        }
        if (!negArr.empty())
        {
            int maxNeg = negArr[0];
            for (int i = 0; i < negArr.size(); i++)
            {
                if (negArr[i] > maxNeg)
                {
                    maxNeg = negArr[i];
                }
            }
            return maxNeg;
        }
        else
        {
            return numeric_limits<int>::min();
        }
    }

    int soLanXuatHienCua(const int n)
    {
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (n == array[i])
            {
                count++;
            }
        }
        return count;
    }

    bool mangCoGiamDanKhong()
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    void sortArr()
    {
        sort(array, array + size);
    }
};

/////////////////////////// cau 5.
class cHocSinh
{
private:
    int MaHocSinh;
    string HoTen;
    string GioiTinh;
    int NamSinh;
    float DiemTrungBinh;

public:
    cHocSinh()
    {
        MaHocSinh = 0;
        HoTen = "";
        GioiTinh = "";
        NamSinh = 0;
        DiemTrungBinh = 0.0;
    }

    friend ostream &operator<<(ostream &os, const cHocSinh &st)
    {
        os << "Ma Hoc Sinh: " << st.MaHocSinh << endl;
        os << "Ho Ten: " << st.HoTen << endl;
        os << "Gioi Tinh: " << st.GioiTinh << endl;
        os << "Nam Sinh: " << st.NamSinh << endl;
        os << "Diem Trung Binh: " << st.DiemTrungBinh << endl;
        return os;
    }

    friend istream &operator>>(istream &is, cHocSinh &st)
    {
        cout << "Ma Hoc Sinh: ";
        is >> st.MaHocSinh;
        cout << "Ho Ten: ";
        is.ignore();
        getline(is, st.HoTen);
        cout << "Gioi Tinh: ";
        is >> st.GioiTinh;
        cout << "Nam Sinh: ";
        is >> st.NamSinh;
        cout << "Diem Trung Binh: ";
        is >> st.DiemTrungBinh;
        return is;
    }

    void setMaHocSinh(int _maHocSinh)
    {
        MaHocSinh = _maHocSinh;
    }

    void setHoTen(const string &_hoTen)
    {
        HoTen = _hoTen;
    }

    void setGioiTinh(const string &_gioiTinh)
    {
        GioiTinh = _gioiTinh;
    }

    void setNamSinh(int _namSinh)
    {
        NamSinh = _namSinh;
    }

    void setDiemTrungBinh(float _diemTrungBinh)
    {
        DiemTrungBinh = _diemTrungBinh;
    }

    int getMaHocSinh() const
    {
        return MaHocSinh;
    }

    string getHoTen() const
    {
        return HoTen;
    }

    string getGioiTinh() const
    {
        return GioiTinh;
    }

    int getNamSinh() const
    {
        return NamSinh;
    }

    float getDiemTrungBinh() const
    {
        return DiemTrungBinh;
    }
};

/////////////////////////// cau 6.

class complex
{
private:
    float r;
    float i;

public:
    complex(float _real = 0.0, float _im = 1.0) : r(_real), i(_im) {}

    friend ostream &operator<<(ostream &os, const complex &c)
    {
        os << '(' << c.r << " + " << c.i << "i" << ')';
        return os;
    }

    friend istream &operator>>(istream &is, complex &c)
    {
        cout << "nhap a + bi (a  b): ";
        is >> c.r >> c.i;
        return is;
    }

    void setReal(float _r)
    {
        r = _r;
    }

    const float getReal()
    {
        return r;
    }

    void setIm(float _i)
    {
        i = _i;
    }

    const float getIm()
    {
        return i;
    }

    complex operator+(const complex &c)
    {
        return complex(r + c.r, i + c.i);
    }

    complex operator-(const complex &c)
    {
        return complex(r - c.r, i - c.i);
    }

    complex operator*(const complex &c)
    {
        return complex(r * i - c.r * c.i, r * c.i + c.r * i);
    }

    complex operator/(const complex &c)
    {
        return complex((r * i + c.r * c.i) / (i * i + c.i * c.i), (c.r * i - r * c.i) / (i * i + c.i * c.i));
    }
};

/////////////////////////// main().
int main()
{
    int cau;
    cout << "chon cau: ";
    cin >> cau;
    switch (cau)
    {
    case 1:
    {
        Student A;
        NhapThongTinHocSinh(A);
        XuatThongTinHocSinh(A);
        break;
    }
    case 2:
    {
        float r;
        point2D A;
        cout << name(A) << ':';
        cin >> A;
        cout << "ban kinh r = ";
        cin >> r;
        cout << " • dien tich = " << fixed << setprecision(2) << r * r * M_PI << endl;
        cout << " • chu vi    = " << fixed << setprecision(2) << 2 * r * M_PI << endl;
        break;
    }
    case 3:
    {
        point2D A, B;
        cout << name(A) << ':';
        cin >> A;
        cout << name(B) << ':';
        cin >> B;
        cout << name(A) << A << endl;
        cout << name(B) << B << endl;
        cout << "> d(A, B) = " << fixed << setprecision(2) << A.distance(B);
        break;
    }
    case 4:
    {
        int size;
        cout << "nhap kich co cArray: ";
        cin >> size;
        cArray alpha(size);
        cout << "> " << name(alpha) << " = " << alpha << endl;
        cout << "> so am lon nhat trong day la: " << alpha.soAmLonNhat() << endl;
        int soCanTim;
        cout << "nhap so can dem: ";
        cin >> soCanTim;
        cout << "> so " << soCanTim << " xuat hien " << alpha.soLanXuatHienCua(soCanTim) << " lan trong day" << endl;
        cout << "> mang " << (alpha.mangCoGiamDanKhong() ? "co " : "khong ") << "giam dan " << endl;
        alpha.sortArr();
        cout << "> " << name(alpha) << " = " << alpha << endl;
        break;
    }
    case 5:
    {
        cHocSinh A, B;
        cin >> A >> B;
        (A.getDiemTrungBinh() > B.getDiemTrungBinh()) ? cout << name(A) : cout << name(B) << endl;
        (A.getNamSinh() < B.getNamSinh()) ? cout << name(A) : cout << name(B) << endl;
    }
    case 6:
    {
        complex a, b;
        cin >> a >> b;
        cout << a << " + " << b << " = " << a + b << endl;
        cout << a << " - " << b << " = " << a - b << endl;
        cout << a << " * " << b << " = " << a * b << endl;
        cout << a << " / " << b << " = " << a / b << endl;
    }
    default:
        break;
    }
    return 0;
}