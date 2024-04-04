// 1. Cài đặt lớp số phức để biểu diễn khái niệm số phức, cho phép quan điểm một số thực như một số phức đặc biệt(phần ảo bằng 0).
// ▪ Định nghĩa các phép toán +, -, *, /, ==, <<, >> trên số phức.
//// check ✓
// ▪ Định nghĩa các thao tác cần thiết cho lớp số phức
//// check ✓

// 2. Giả sử lớp PhanSo đã được khai báo.
// ▪ Cài đặt toán tử > như khai báo cho lớp PhanSo
//// check ✓
//    Hãy xây dựng lớp DSPhanSo để lưu trữ một
//    mảng các phân số cho phép thực hiện các thao
//    tác sau :
// ▪ Nhập giá trị cho các phân số trong mảng
//// check ✓
// ▪ Tìm phân số có giá trị lớn nhất.
//// check ✓
// ▪ Tính tổng các phân số trong mảng
//// check ✓
// ▪ Hãy viết chương trình để nhập một mảng
//   gồm n phân số(n do người dùng nhập)
//// check ✓
// ▪ tìm và in ra màn hình phân số có giá trị lớn nhất.
//// check ✓

// 3. Xét đa thức theo biến x (đa thức một biến) bậc n có dạng như sau:
//
//        P(X) = a1.x^(n) + a2.x^(n-1) + a3.x^(n-2)+ … + aj
//
//    Trong đó: n là bậc của đa thức. a1, a2 , a3, …, aj
//    là các hệ số tương ứng với từng bậc của đa thức.
//    Xây dựng lớp DaThuc biểu diễn khái niệm đa thức với các thao tác sau:
// ▪ Khởi tạo một đa thức có bậc bằng 0 hoặc bậc n.
//// check ✓
// ▪ Tính giá trị của đa thức khi biết giá trị của x
//// check ✓
// ▪ Nhập đa thức
//// check ✓
// ▪ Xuất đa thức
//// check ✓
// ▪ Định nghĩa các toán tử: >>, <<, +, -
//// check ✓
// ▪ Viết chương trình cho phép người dùng nhập vào hai đa thức rồi xuất các
//   đa thức ra màn hình. Sau đó tính tổng hai đa thức và xuất kết quả ra màn
//   hình.
//// check ✓

// 4. Một ma trận là một mảng hai chiều gồm row dòng
//    và n cột. Hãy khai báo và cài đặt lớp biểu diễn
//    khái niệm ma trận để thực hiện các yêu cầu sau:
// ▪ Tạo ma trận ngẫu nhiên row dòng, col cột
//// check ✓
// ▪ Nhập ma trận row dòng col cột
//// check ✓
// ▪ Operator cộng hai ma trận
//// check ✓
// ▪ Operator nhân hai ma trận
// ▪ Viết chương trình cho phép tạo 2 ma trận, cộng,
//   trừ 2 ma trận và xuất kết quả ra màn hình.

//// check ✓


#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

/////////////////////////// cau 1.

class complex
{
private:
    float row;
    float i;

public:
    complex(float _real = 0.0, float _im = 1.0) : row(_real), i(_im) {}

    friend ostream &operator<<(ostream &os, const complex &col)
    {
        os << '(' << col.row << " + " << col.i << "i" << ')';
        return os;
    }

    friend istream &operator>>(istream &is, complex &col)
    {
        cout << "nhap a + bi (a  b): ";
        is >> col.row >> col.i;
        return is;
    }

    void setReal(float _row)
    {
        row = _row;
    }

    const float getReal()
    {
        return row;
    }

    void setIm(float _i)
    {
        i = _i;
    }

    const float getIm()
    {
        return i;
    }

    complex operator+(const complex &col)
    {
        return complex(row + col.row, i + col.i);
    }

    complex operator-(const complex &col)
    {
        return complex(row - col.row, i - col.i);
    }

    complex operator*(const complex &col)
    {
        return complex(row * i - col.row * col.i, row * col.i + col.row * i);
    }

    complex operator/(const complex &col)
    {
        return complex((row * i + col.row * col.i) / (i * i + col.i * col.i), (col.row * i - row * col.i) / (i * i + col.i * col.i));
    }
};

/////////////////////////// cau 2.

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
        while(!ps.mau)
        {
            cout << "nhap lai mau so (!0): ";
            is >> ps.mau;
        }
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


#define randomRange 100
class DSPhanSo
{
private:
    int size;
    PhanSo *array;

public:
    // arrPhanSo(size, pre_filled_with_random_nums_or_not)
    DSPhanSo(int _size = 1, int _pre_fill = 0) : size(_size), array(new PhanSo[_size])
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

    friend ostream &operator<<(ostream &os, const DSPhanSo &obj)
    {
        os << '{';
        for (int i = 0; i < obj.size - 1; i++)
        {
            os << obj.array[i] << ", ";
        }
        os << obj.array[obj.size - 1] << '}';
        return os;
    }

    friend istream &operator>>(istream &is, DSPhanSo &obj)
    {
        for (int i = 0; i < obj.size; i++)
        {
            is >> obj.array[i];
        }
        return is;
    }

    double getSumArray()
    {
        double sum = 0.0;
        for(int i = 0; i < size; i++)
        {
            sum += array[i].getValue();
        }
        return sum;
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

    DSPhanSo sortAscending()
    {
        sort(array, array + size);
        return *this;
    }
};

/////////////////////////// cau 3.
class monomial
{
private:
    int coefficient;
    int exponent;

public:
    monomial(int _coefficient = 1, int _exponent = 1) : coefficient(_coefficient), exponent(_exponent) {}

    friend ostream &operator<<(ostream &os, const monomial &row)
    {
        os << row.coefficient << "x^" << row.exponent;
        return os;
    }

    friend istream &operator>>(istream &is, monomial &row)
    {
        is >> row.coefficient >> row.exponent;
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

    void setCoefficient(int _col)
    {
        coefficient = _col;
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

class polynomial
{
private:
    int degree;
    monomial *array;
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

    friend ostream &operator<<(ostream &os, const polynomial &p)
    {
        for (int i = 0; i < p.degree; i++)
        {
            os << p.array[i] << " + ";
        }
        os << p.constant;
        return os;
    }

    friend istream &operator>>(istream &is, polynomial &p)
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

    monomial *getMonomialsArray() const
    {
        return array;
    }

    int getConstant() const
    {
        return constant;
    }

    void setConstant(int _col)
    {
        constant = _col;
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

    polynomial operator+(const polynomial &p) const
    {
        int h_deg, l_deg;
        monomial *h_ptr, *l_ptr;

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
    
    polynomial operator-(const polynomial &p) const
    {
        int h_deg, l_deg;
        monomial *h_ptr, *l_ptr;

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

/////////////////////////// cau 4.

#define randomMatrixSizeRange 10       // [2, n]
#define randomMatrixFillValueRange 10  // [-n, n]
class Matrix
{
private:
    int row;
    int col;
    int **matrix{};
public:
    explicit Matrix(int _row = 1, int _col = 1, int random_fill = 1) : row(_row), col(_col)
    {
        random_device rd;
        mt19937 gen(rd());
        gen.seed(std::chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> dSize(2, randomMatrixSizeRange);
        if(_row <= 1 || _col <= 1)
        {
            if(_row <= 1 && _col >= 2)
            {
                row = dSize(gen);
            } else if (_row >= 2)
                col = dSize(gen);
            else {
                row = dSize(gen);
                col = dSize(gen);
            }

        }
        matrix = new int*[col];
        for(int i = 0; i < row; i++)
        {
            matrix[i] = new int[col];
        }
        if(random_fill)
        {
            uniform_int_distribution<int> dValue(-randomMatrixFillValueRange, randomMatrixFillValueRange);
            for(int i = 0; i < row; i++)
            {
                for(int j = 0; j < col; j++)
                {
                    matrix[i][j] = dValue(gen);
                }
            }
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < row; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    [[nodiscard]] int getRow() const
    {
        return row;
    }

    [[nodiscard]] int getCol() const
    {
        return col;
    }

    friend ostream &operator<<(ostream &os, const Matrix &v)
    {
        for(int i = 0; i < v.row; i++)
        {
            os << '[';
            for(int j = 0; j < v.col - 1; j++)
            {
                os << v.matrix[i][j] << ' ';
            }
            os << v.matrix[i][v.col - 1] << ']' << '\n';
        }
        return os;
    }

    friend istream &operator>>(istream &is, Matrix &v)
    {
        for(int i = 0; i < v.row; i++)
        {
            for(int j = 0; j < v.col; j++)
            {
                is >> v.matrix[i][j];
            }
        }
        return is;
    }

    Matrix operator+(const Matrix &mt)
    {
        if(mt.row == row && mt.col == col)
        {
            Matrix sum(row, col, 0);
            for(int i = 0; i < row; i++)
            {
                for(int j = 0; j < col; j++)
                {
                    sum.matrix[i][j] = matrix[i][j] + mt.matrix[i][j];
                }
            }
            return sum;
        } else
        {
            throw invalid_argument("matrices are not of equal sizes");
        }
    }

    Matrix operator-(const Matrix &mt)
    {
        if(mt.row == row && mt.col == col)
        {
            Matrix sum(row, col, 0);
            for(int i = 0; i < row; i++)
            {
                for(int j = 0; j < col; j++)
                {
                    sum.matrix[i][j] = matrix[i][j] - mt.matrix[i][j];
                }
            }
            return sum;
        } else
        {
            throw invalid_argument("matrices are not of equal sizes");
        }
    }

    Matrix operator*(const Matrix &mt)
    {
        if(col == mt.row) // Modified this condition
        {
            Matrix product(row, mt.col, 0); // Corrected the dimensions here
            for(int i = 0; i < row; i++)
            {
                for(int j = 0; j < mt.col; j++) // Modified the loop condition to mt.col
                {
                    int sum = 0;
                    for(int k = 0; k < col; k++) // Modified the loop condition to col
                    {
                        sum += matrix[i][k] * mt.matrix[k][j];
                    }
                    product.matrix[i][j] = sum;
                }
            }
            return product;
        }
        else
        {
            throw invalid_argument("columns number of the first matrix is not equal to the rows number of the second matrix");
        }
    }
};

int main()
{
    int cau;
    cout << "chon cau (1, 2, 3, 4): ";
    cin >> cau;
    switch (cau)
    {
    case 1:
    {
        break;
    }
    case 2:
    {
        int n;
        cout << "nhap kich thuoc day phan so A: \n";
        cin >> n;
        DSPhanSo A(n, 0);
        cin >> A;
        cout << "phan so lon nhat trong A la: " << A.getMaxFraction();
        break;
    }
    case 3:
    {
        int a, b;
        cout << "nhap lan luot bac cua da thuc A va da thuc B: \n";
        cin >> a >> b;
        polynomial A(a), B(b);
        cout << "nhap " << a + 1 << " he so cho da thuc A\n";
        cin >> A;
        cout << "nhap " << b + 1 << " he so cho da thuc B\n";
        cin >> B;
        cout << "da thuc A: " << A << '\n';
        cout << "da thuc B: " << B << '\n';
        cout << "tong hai da thuc A va B:\n";
        cout << A + B;
        break;
    }
    case 4:
    {
        int a, b, m, n;
        cout << "nhap lan luot so hang va so cot cua ma tran A: ";
        cin >> a >> b;
        cout << "nhap lan luot so hang va so cot cua ma tran B: ";
        cin >> m >> n;
        Matrix A(a, b, 1), B(m, n, 1);
        // cout << "nhap ma tran A (" << A.getCol() << "x" << A.getRow() << "):\n";
        // cin >> A;
        // cout << "nhap ma tran B (" << B.getCol() << "x" << B.getRow() << "):\n";
        // cin >> B;
        cout << A << "+\n" << B << '\n' << A + B << '\n';
        cout << A << "-\n" << B << '\n' << A - B << '\n';
        cout << A << "*\n" << B << '\n' << A * B << '\n';
        break;
    }
    default:
        break;
    }
    return 0;
}