// 1. Khai báo và định nghĩa lớp mảng một chiều(lớp cArray) để lưu trữ danh sách các số nguyên,
//    hỗ trợ các thao tác sau :
// ▪ Nhập dãy số nguyên gồm n phần tử.
//// check ✓
// ▪ Xuất dãy số nguyên của mảng.
//// check ✓
// ▪ Tạo dãy gồm n số nguyên ngẫu nhiên.
//// check ✓
// ▪ Đếm số lần xuất hiện của x trong mảng.
//// check ✓
// ▪ Kiểm tra dãy số nguyên có tăng dần hay không.
//// check ✓
// ▪ Tìm phần tử lẻ nhỏ nhất trong dãy số nguyên.
//// check ✓
// ▪ Sắp xếp các số nguyên trong dãy tăng dần.
//// check ✓

// 2. Cài đặt lớp arrPhanSo cho phép lưu trữ và thực hiện
//    các thao tác trên mảng các phân số:
// ▪ Nhập các phân số
//// check ✓
// ▪ Xuất danh sách các phân số
//// check ✓
// ▪ Tạo n phân số ngẫu nhiên
//// check ✓
// ▪ Tìm phân số có giá trị lớn nhất
//// check ✓
// ▪ Đếm xem có bao nhiêu phân số có tử là số nguyên tố
//// check ✓
// ▪ Sắp xếp các phân số trong mang theo thứ tự tăng dần.
//// check ✓

// 3. Cài đặt lớp Đơn thức biểu diễn khái niệm đơn thức(P(x) = ax^b) cho phép thực hiện các yêu cầu sau:
// ▪ Tạo lập đơn thức
//// check ✓
// ▪ Nhập thông tin cho đơn thức, thay đổi thông tin đơn thức
//// check ✓
// ▪ Xuất đơn thức ra màn hình
//// check ✓
// ▪ Tính giá trị của đơn thức khi biết x
//// check ✓
// ▪ Tính đạo hàm của đơn thức
//// check ✓
// ▪ Tính tổng hai đơn thức(hai đơn thức cùng bậc)
//// check ✓
// ▪ Viết chương trình cho phép nhập vào 2 đơn thức,
//   tính tổng hai đơn thức và xuất kế quả ra màn hình.
//// check ✓

// 4. Xét đa thức theo biến x (đa thức một biến) bậc n có dạng như sau:
//
//        P(X) = a1.x^(n) + a2.x^(n-1) + a3.x^(n-2)+ … + aj
//
//    Trong đó: n là bậc của đa thức. a1, a2 , a3, …, aj
//    là các hệ số tương ứng với từng bậc của đa thức.
// Xây dựng lớp DaThuc biểu diễn khái niệm đa thức với các thao tác sau:
// ▪ Khởi tạo một đa thức có bậc bằng 0 hoặc bậc n.
//// check ✓
// ▪ Tính giá trị của đa thức khi biết giá trị của x
//// check ✓
// ▪ Nhập đa thức
//// check ✓
// ▪ Xuất đa thức
//// check ✓
// ▪ Cộng hai đa thức
//// check ✓
// ▪ Trừ hai đa thức
//// check ✓
// ▪ Viết chương trình cho phép người dùng nhập vào hai đa thức rồi xuất các
//   đa thức ra màn hình. Sau đó tính tổng hai đa thức và xuất kết quả ra màn
//   hình.
//// check ✓

// 5. Giả sử mỗi đối tượng sách trong hệ thống thư viện có các thuộc tính sau:
//    Mã sách, Tên sách, Năm xuất bản, Tổng số trang.
// Hãy xây dựng lớp cBook với các thuộc tính như trên và các phương thức cần thiết sau:
// ▪ Thiết lập thông tin sách
//// check ✓
// ▪ Nhập thông tin cho đối tượng sách từ bàn phím
//// check ✓
// ▪ Xuất thông tin đối tượng sách ra màn hình
//// check ✓
// ▪ Truy vấn và cập nhật thông tin Xây dựng lớp cListBook để quản lý danh sách các đối tượng sách và thực hiện các yêu cầu sau:
// ▪ Nhập danh sách các đối tượng sách
//// check ✓
// ▪ Xuất danh sách các đối tượng sách
//// check ✓
// ▪ Cho biết thông tin sách nào được xuất bản gần đây nhất
//// check ✓

#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

/////////////////////////// cau 1.
#define randomRange 100

class cArray
{
private:
    int size;
    int *array;

public:
    // cArray(size, pre_filled_with_random_nums_or_not)
    cArray(int _size = 1, bool _pre_fill = 0) : size(_size), array(new int[_size])
    {
        if (_pre_fill)
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distribution(-randomRange, randomRange);
            for (int i = 0; i < _size; i++)
            {
                array[i] = distribution(gen);
            }
        }
        else
        {
            array = {0};
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

    friend istream &operator>>(istream &is, cArray &obj)
    {
        cout << "nhap kich co array: ";
        is >> obj.size;

        obj.array = new int[obj.size];
        cout << "nhap array: ";

        for (int i = 0; i < obj.size; i++)
        {
            is >> obj.array[i];
        }

        return is;
    }

    int getSize()
    {
        return size;
    }

    const int *getArray()
    {
        return array;
    }

    int count(const int n)
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

    bool isAscending()
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (array[i] < array[i + 1])
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

    int minOddNum()
    {
        int min = randomRange & 0 ? randomRange + 1 : randomRange;
        vector<int> odd;
        for (int i = 0; i < size; i++)
        {
            if (array[i] & 1 && array[i] < min)
            {
                min = array[i];
            }
        }
        return min;
    }

    cArray sortedArr()
    {
        sort(array, array + size);
        return *this;
    }
};

/////////////////////////// cau 2.
bool isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

class PhanSo
{
public:
    int tu;
    int mau;

public:
    PhanSo(const int x = 1, const int y = 1) : tu(x), mau(y) {}

    friend ostream &operator<<(ostream &os, const PhanSo &ps)
    {
        os << "(" << ps.tu << "/" << ps.mau << ")";
        return os;
    }

    friend istream &operator>>(istream &is, PhanSo &ps)
    {
        is >> ps.tu >> ps.mau;
        return is;
    }

    double getValue() const
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

    bool operator<(const PhanSo &ps) const
    {
        return this->getValue() < ps.getValue();
    }

    bool operator<=(const PhanSo &ps) const
    {
        return this->getValue() <= ps.getValue();
    }

    bool operator>(const PhanSo &ps) const
    {
        return this->getValue() > ps.getValue();
    }

    bool operator>=(const PhanSo &ps) const
    {
        return this->getValue() >= ps.getValue();
    }
};

class arrPhanSo
{
private:
    int size;
    PhanSo *array;

public:
    // arrPhanSo(size, pre_filled_with_random_nums_or_not)
    arrPhanSo(int _size = 1, int _pre_fill = 0) : size(_size), array(new PhanSo[_size])
    {
        if (_pre_fill)
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distribution(-randomRange, randomRange);
            int mau_temp;
            for (int i = 0; i < _size; i++)
            {
                array[i].tu = distribution(gen);
                mau_temp = distribution(gen);
                array[i].mau = mau_temp == 0 ? mau_temp + 1 : mau_temp;
            }
        }
    }

    friend ostream &operator<<(ostream &os, const arrPhanSo &obj)
    {
        os << '{';
        for (int i = 0; i < obj.size - 1; i++)
        {
            os << obj.array[i] << ", ";
        }
        os << obj.array[obj.size - 1] << '}';
        return os;
    }

    friend istream &operator>>(istream &is, arrPhanSo &obj)
    {
        for (int i = 0; i < obj.size; i++)
        {
            is >> obj.array[i];
        }
        return is;
    }

    PhanSo getMaxFraction()
    {
        PhanSo max(-randomRange, 1);
        for (int i = 0; i < size; i++)
        {
            if (array[i].getValue() > max.getValue())
            {
                max = array[i];
            }
        }
        return max;
    }

    int getPrimeNumeratorCount()
    {
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (isPrime(array[i].tu))
            {
                count++;
            }
        }
        return count;
    }

    arrPhanSo sortAscending()
    {
        sort(array, array + size);
        return *this;
    }
};

/////////////////////////// cau 3.
// suppose all varibles are x
class monomial
{
private:
    int coefficient;
    int exponent;

public:
    monomial(int _coefficient = 1, int _exponent = 1) : coefficient(_coefficient), exponent(_exponent) {}

    friend ostream &operator<<(ostream &os, const monomial &m)
    {
        os << m.coefficient << "x^" << m.exponent;
        return os;
    }

    friend istream &operator>>(istream &is, monomial &m)
    {
        is >> m.coefficient >> m.exponent;
        return is;
    }

    int getCoefficient() const
    {
        return coefficient;
    }

    int getExponent() const
    {
        return exponent;
    }

    void setCoefficient(int _c)
    {
        coefficient = _c;
    }

    void setExponent(int _e)
    {
        exponent = _e;
    }

    double getValue(double _x)
    {
        return (double)coefficient != 0 ? coefficient * pow(_x, exponent) : 0.0;
    }

    monomial getDerivative() const
    {
        return monomial(coefficient * exponent, exponent - 1);
    }

    monomial operator+(const monomial &mn) const
    {
        if (exponent == mn.exponent)
        {
            return monomial(coefficient + mn.coefficient, exponent);
        }
        else
        {
            throw invalid_argument("cannot add monomials with different powers");
        }
    }
    monomial operator+=(const monomial &mn)
    {
        if (exponent == mn.exponent)
        {
            coefficient += mn.coefficient;
            return *this;
        }
        else
        {
            throw invalid_argument("cannot add monomials with different powers");
        }
    }
    monomial operator-(const monomial &mn) const
    {
        if (exponent == mn.exponent)
        {
            return monomial(coefficient - mn.coefficient, exponent);
        }
        else
        {
            throw invalid_argument("cannot subtract monomials with different powers");
        }
    }
    monomial operator-=(const monomial &mn)
    {
        if (exponent == mn.exponent)
        {
            coefficient -= mn.coefficient;
            return *this;
        }
        else
        {
            throw invalid_argument("cannot subtract monomials with different powers");
        }
    }
};

/////////////////////////// cau 4.
class polynomial
{
private:
    int degree;
    monomial* array;
    int constant;

public:
    polynomial(int _degree) : degree(_degree), constant(0)
    {
        if (_degree == 0)
        {
            array = new monomial[1];
            array[0].setCoefficient(0);
        }
        else
        {
            array = new monomial[_degree];
        }
    }

    ~polynomial()
    {
        delete[] array;
    }

    friend ostream& operator<<(ostream& os, const polynomial& p)
    {
        bool isFirst = true;
        for (int i = 0; i < p.degree; i++)
        {
            if (p.array[i].getCoefficient() != 0)
            {
                if (!isFirst && p.array[i].getCoefficient() > 0)
                    os << "+";

                if (p.array[i].getCoefficient() != 1 && p.array[i].getCoefficient() != -1 && p.array[i].getExponent() != 0)
                    os << p.array[i].getCoefficient();

                if (p.array[i].getCoefficient() == -1 && p.array[i].getExponent() != 0)
                    os << "-";

                if (p.array[i].getExponent() != 0)
                    os << "x";

                if (p.array[i].getExponent() != 1 && p.array[i].getExponent() != 0)
                    os << "^" << p.array[i].getExponent();

                if (p.array[i].getExponent() == 0)
                    os << p.array[i].getCoefficient();

                if (isFirst)
                    isFirst = false;
            }
        }
        if(p.constant < 0)
            os << p.constant;
        else
            os << "+" << p.constant;
        return os;
    }

    friend istream& operator>>(istream& is, polynomial& p)
    {
        int temp = 0;
        for (int i = 0; i < p.degree; i++)
        {
            is >> temp;
            p.array[i].setCoefficient(temp);
            p.array[i].setExponent(p.degree - i);
        }
        is >> p.constant;
        return is;
    }

    int getDegree() const
    {
        return degree;
    }

    monomial* getMonomialsArray() const
    {
        return array;
    }

    int getConstant() const
    {
        return constant;
    }

    void setConstant(int _c)
    {
        constant = _c;
    }

    double getValue(double _x)
    {
        double value = constant;
        for (int i = 0; i < degree; i++)
        {
            value += array[i].getValue(_x);
        }
        return value;
    }

    polynomial operator+(const polynomial& p) const
    {
        int h_deg, l_deg;
        monomial* h_ptr, * l_ptr;

        if (p.getDegree() > this->getDegree())
        {
            h_deg = p.getDegree();
            h_ptr = p.array;
        }
        else
        {
            h_deg = this->getDegree();
            h_ptr = this->array;
        }
        l_deg = p.getDegree() + this->getDegree() - h_deg;
        l_ptr = h_ptr == p.array ? this->array : p.array;

        polynomial result(h_deg);
        result.setConstant(this->constant + p.constant);

        int delta = h_deg - l_deg;
        if (delta > 0)
        {
            for (int i = 0; i < delta; i++)
            {
                result.array[i] = h_ptr[i];
            }
        }
        for (int i = delta; i < h_deg; i++)
        {
            result.array[i] = h_ptr[i] + l_ptr[i - delta];
        }

        return result;
    }

    polynomial operator-(const polynomial& p) const
    {
        int h_deg, l_deg;
        monomial* h_ptr, * l_ptr;

        if (p.getDegree() > this->getDegree())
        {
            h_deg = p.getDegree();
            h_ptr = p.array;
        }
        else
        {
            h_deg = this->getDegree();
            h_ptr = this->array;
        }
        l_deg = p.getDegree() + this->getDegree() - h_deg;
        l_ptr = h_ptr == p.array ? this->array : p.array;

        polynomial result(h_deg);
        result.setConstant(this->constant + p.constant);

        int delta = h_deg - l_deg;
        if (delta > 0)
        {
            for (int i = 0; i < delta; i++)
            {
                result.array[i] = h_ptr[i];
            }
        }
        for (int i = delta; i < h_deg; i++)
        {
            result.array[i] = h_ptr[i] - l_ptr[i - delta];
        }

        return result;
    }
};

/////////////////////////// cau 5.
class cBook
{
private:
    string ISBN;
    string name;
    int year;
    int pages;

public:
    cBook(string _ISBN = "978-3-16-148410-0", string _name = "The Blank", int _year = 2077, int _pages = 461) : ISBN(_ISBN), name(_name), year(_year), pages(_pages) {}

    friend ostream &operator<<(ostream &os, const cBook &b)
    {
        os << "ISBN: " << b.ISBN << endl;
        os << "Name: " << b.name << endl;
        os << "Year: " << b.year << endl;
        os << "Pages: " << b.pages << endl;
        return os;
    }
    friend istream &operator>>(istream &is, cBook &b)
    {
        cout << "ISBN: ";
        is >> b.ISBN;
        cout << "Name: ";
        is >> b.name;
        cout << "Year: ";
        is >> b.year;
        cout << "Pages: ";
        is >> b.pages;
        return is;
    }

    string getISBN() const
    {
        return ISBN;
    }
    string getName() const
    {
        return name;
    }
    int getYear() const
    {
        return year;
    }
    int getPages() const
    {
        return pages;
    }

    void setISBN(string _I)
    {
        ISBN = _I;
    }
    void setName(string _n)
    {
        name = _n;
    }
    void setYear(int _y)
    {
        year = _y;
    }
    void setPages(int _p)
    {
        pages = _p;
    }
};

class cListBook
{
private:
    int size;
    cBook *array;

public:
    cListBook(int _size) : size(_size), array(new cBook[_size]) {}

    friend ostream &operator<<(ostream &os, const cListBook &lb)
    {
        for (int i = 0; i < lb.size; i++)
        {
            os << lb.array[i] << endl;
        }
        return os;
    }
    friend istream &operator>>(istream &is, cListBook &lb)
    {
        for (int i = 0; i < lb.size; i++)
        {
            is >> lb.array[i];
        }
        return is;
    }

    cBook latestBook()
    {
        cBook latest = array[0];
        for (int i = 0; i < size; i++)
        {
            if (array[i].getYear() > latest.getYear())
            {
                latest = array[i];
            }
        }
        return latest;
    }
};

int main()
{
    int cau;
    cout << "chon cau (1, 2, 3, 4, 5): ";
    cin >> cau;
    switch (cau)
    {
    case 1:
    {
        cArray A;
        cin >> A;
        cout << "array A: " << A << endl;
        int rand_size;
        cout << "nhap kich thuoc array ngau nhien: ";
        cin >> rand_size;
        cArray R(rand_size, 1);
        cout << "array R: " << R << endl;
        int x;
        cout << "nhap so can dem: ";
        cin >> x;
        cout << x << " xuat hien " << A.count(x) << " lan trong array " << 'A' << endl;
        cout << x << " xuat hien " << R.count(x) << " lan trong array " << 'R' << endl;
        cout << "array A " << (A.isAscending() ? "co" : "khong") << " tang dan" << endl;
        cout << "array R " << (R.isAscending() ? "co" : "khong") << " tang dan" << endl;
        cout << "phan tu le nho nhat trong A la: " << A.minOddNum() << endl;
        cout << "phan tu le nho nhat trong R la: " << R.minOddNum() << endl;
        cout << "sap xep tang dan array A: " << A.sortedArr() << endl;
        cout << "sap xep tang dan array R: " << R.sortedArr() << endl;
        break;
    }
    case 2:
    {
        int size;
        cout << "nhap kich thuoc array phan so: ";
        cin >> size;
        arrPhanSo A(size);
        cin >> A;
        cout << A << endl;
        int r_size;
        cout << "nhap kich thuoc array phan so ngau nhien: ";
        cin >> r_size;
        arrPhanSo R(r_size, 1);
        cout << R << endl;
        cout << "phan so lon nhat trong A la :" << A.getMaxFraction() << endl;
        cout << "phan so lon nhat trong R la :" << R.getMaxFraction() << endl;
        cout << "co " << A.getPrimeNumeratorCount() << " phan so co tu so la so nguyen to trong A" << endl;
        cout << "co " << R.getPrimeNumeratorCount() << " phan so co tu so la so nguyen to trong R" << endl;
        cout << "sap xep tang dan array A: " << A.sortAscending() << endl;
        cout << "sap xep tang dan array R: " << R.sortAscending() << endl;
        break;
    }
    case 3:
    {
        monomial A, B;
        cout << "nhap ax^b (a b): ";
        cin >> A;
        cout << "nhap ax^b (a b): ";
        cin >> B;
        cout << A << " + " << B << " = " << A + B << endl;
        cout << "(" << A << ")' = " << A.getDerivative() << endl;
        cout << "(" << B << ")' = " << B.getDerivative() << endl;
        double x;
        cout << "nhap x: ";
        cin >> x;
        cout << "gia tri don thuc A voi x da nhap: " << A.getValue(x) << endl;
        cout << "gia tri don thuc B voi x da nhap: " << B.getValue(x) << endl;
        break;
    }
    case 4:
    {
        int deg_A, deg_B;
        cout << "nhap bac cua da thuc A: ";
        cin >> deg_A;
        cout << "nhap bac cua da thuc B: ";
        cin >> deg_B;
        polynomial A(deg_A), B(deg_B);
        cout << "(ax^2 + bx^0 + 1 <=> a b 1)" << endl;
        cout << "nhap " << deg_A + 1 << " he so: ";
        cin >> A;
        cout << "nhap " << deg_B + 1 << " he so: ";
        cin >> B;
        cout << '\t' << A << endl;
        cout << "    +" << endl;
        cout << '\t' << B << endl;
        cout << '\t' << A + B << endl << endl;
        cout << '\t' << A << endl;
        cout << "    -" << endl;
        cout << '\t' << B << endl;
        cout << '\t' << A - B << endl << endl;
        break;
    }
    case 5:
    {
        int size;
        cout << "nhap so sach: ";
        cin >> size;
        cListBook A(size);
        cin >> A;
        cout << endl
             << "sach moi nhat: " << endl
             << A.latestBook();
        break;
    }
    default:
        break;
    }
    return 0;
}