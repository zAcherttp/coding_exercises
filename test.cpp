#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

#define randomMatrixSizeRange 10      // [2, n]
#define randomMatrixFillValueRange 10 // [-n, n]
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
        if (_row <= 1 || _col <= 1)
        {
            if (_row <= 1 && _col >= 2)
            {
                row = dSize(gen);
            }
            else if (_row >= 2)
                col = dSize(gen);
            else
            {
                row = dSize(gen);
                col = dSize(gen);
            }
        }
        matrix = new int *[row];
        for (int i = 0; i < col; i++)
        {
            matrix[i] = new int[row];
        }
        if (random_fill)
        {
            uniform_int_distribution<int> dValue(-randomMatrixFillValueRange, randomMatrixFillValueRange);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    matrix[i][j] = dValue(gen);
                }
            }
        }
        else
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    matrix[i][j] = 0;
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
        for (int i = 0; i < v.row; i++)
        {
            os << '[';
            for (int j = 0; j < v.col - 1; j++)
            {
                os << v.matrix[i][j] << ' ';
            }
            os << v.matrix[i][v.col - 1] << ']' << '\n';
        }
        return os;
    }

    friend istream &operator>>(istream &is, Matrix &v)
    {
        for (int i = 0; i < v.row; i++)
        {
            for (int j = 0; j < v.col; j++)
            {
                is >> v.matrix[i][j];
            }
        }
        return is;
    }

    Matrix operator+(const Matrix &mt)
    {
        if (mt.row == this->row && mt.col == this->col)
        {
            Matrix add(row, col, 0);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    add.matrix[i][j] = this->matrix[i][j] + mt.matrix[i][j];
                }
            }
            return add;
        }
        else
        {
            throw invalid_argument("matrices are not of equal sizes");
        }
    }

    Matrix operator-(const Matrix &mt)
    {
        if (mt.row == this->row && mt.col == this->col)
        {
            Matrix sub(row, col, 0);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    sub.matrix[i][j] = this->matrix[i][j] - mt.matrix[i][j];
                }
            }
            return sub;
        }
        else
        {
            throw invalid_argument("matrices are not of equal sizes");
        }
    }

    Matrix operator*(const Matrix &mt)
    {
        if (this->col == mt.row)
        {
            Matrix product(row, mt.col, 0);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < mt.col; j++)
                {
                    int sum = 0;
                    for (int k = 0; k < col; k++)
                    {
                        sum += this->matrix[i][k] * mt.matrix[k][j];
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
    int a, b, m, n;
    cout << "nhap lan luot so hang va so cot cua ma tran A: ";
    cin >> a >> b;
    cout << "nhap lan luot so hang va so cot cua ma tran B: ";
    cin >> m >> n;
    int option;
    cout << "nhap de chon:\n";
    cout << "0 - Nhap ma tran.\n";
    cout << "1 - Tao ngau nhien ma tran.\n";
    while(option != 0 && option != 1)
    {
        cin >> option;
    }
    Matrix A(a, b, option), B(m, n, option);

    if (option == 0)
    {
        cout << "nhap ma tran A (" << A.getCol() << "x" << A.getRow() << "):\n";
        cin >> A;
        cout << "nhap ma tran B (" << B.getCol() << "x" << B.getRow() << "):\n";
        cin >> B;
    }   

    cout << A << "+\n" << B << '\n';
    cout << A + B << '\n';

    cout << A << "-\n" << B << '\n';
    cout << A - B << '\n';

    cout << A << "*\n" << B << '\n';
    cout << A * B << '\n';

    return 0;
}