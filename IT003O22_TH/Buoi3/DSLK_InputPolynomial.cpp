#include <bits/stdc++.h>
using namespace std;

struct DONTHUC
{
    int somu;
    double heso;

    DONTHUC(double _heso = 0, int _somu = 0)
    {
        heso = _heso;
        somu = _somu;
    }

    DONTHUC &operator=(const DONTHUC &rhs)
    {
        if (this == &rhs)
            return *this;
        this->heso = rhs.heso;
        this->somu = rhs.somu;
        return *this;
    }
};

struct Node
{
    DONTHUC *data;
    Node *next;

    Node(DONTHUC *_data = nullptr)
    {
        this->data = _data;
        this->next = nullptr;
    }
};

struct DATHUC
{
    Node *head;
    Node *tail;
    DATHUC()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
};
//////////////// your code goes here.

void Xuat(DATHUC B)
{
    Node *current = B.head;
    bool isFirst = true;
    while (current != nullptr)
    {
        if (current->data->heso > 0 && current->data->heso != 1 && isFirst)
        {
            isFirst = false;
            cout << current->data->heso << ((current->data->somu == 1) ? ("x") : ("x^")) << ((current->data->somu == 1) ? : (current->data->somu));
        }
        if (current->data->heso > 0 && current->data->heso != 1 && isFirst)
        {
            isFirst = false;
            cout << current->data->heso << ((current->data->somu == 1) ? ("x") : ("x^")) << ((current->data->somu == 1) ? : (current->data->somu));
        }
        if (current->data->heso == 1 && isFirst)
        {
            isFirst = false;
            cout << ((current->data->somu == 1) ? ("x") : ("x^")) << ((current->data->somu == 1) ? : (current->data->somu));
        }

        if (current->data->heso < 0 && current->data->heso != -1)
        {
            isFirst = false;
            cout << current->data->heso << ((current->data->somu == 1) ? ("x") : ("x^")) << ((current->data->somu == 1) ? : (current->data->somu));
        }
        if (current->data->heso == 1)
        {
            isFirst = false;
            cout << "+" << ((current->data->somu == 1) ? ("x") : ("x^")) << ((current->data->somu == 1) ? : (current->data->somu));
        }
        if (current->data->heso == -1)
        {
            isFirst = false;
            cout << "-" << ((current->data->somu == 1) ? ("x") : ("x^")) << ((current->data->somu == 1) ? : (current->data->somu));
        }
        if (current->data->heso == 0)
            continue;

        current = current->next;
    }
}

// Biến trong đa thức ký hiệu là x
// Số mũ ký hiệu ^
// Phép nhân không ghi ký hiệu
// Các ký tự biểu diễn đa thức ghi liền nhau (không khoảng trắng)
// Đơn thức đầu tiên nếu hệ số là số dương thì không được xuất dấu + trước hệ số
// Đơn thức có hệ số bằng 0 thì không xuất đơn thức đó
// Đơn thức có hệ số bằng 1 hoặc -1 thì không xuất số 1
// Đơn thức có số mũ bằng 0 thì chỉ xuất hệ số của đơn thức
// Đơn thức có số mũ bằng 1 thì không xuất số mũ

void Nhap(DATHUC B, double heso, int somu)
{
    DONTHUC* _donthuc = new DONTHUC(heso, somu);
    Node* node = new Node(_donthuc);
    if (!B.head)
    {
        B.head = node;
    }
    else
    {
        B.head->next = node;
    }
    B.tail = node;

}

double TinhDaThuc(DATHUC B, double x)
{
    double sum = 0.0;
    Node *current = B.head;

    while (current != nullptr)
    {
        sum += current->data->heso * pow(x, current->data->somu);
    }

    current = current->next;

    return sum;
}

//////////////// your code ends here.
int main()
{
    DATHUC B;
    int N;

    cin >> N;
    for (int test = 0; test < N; test++)
    {
        double heso;
        int somu;
        cin >> heso >> somu;
        Nhap(B, heso, somu);
    }

    cout << "Da thuc vua nhap la: ";
    Xuat(B);
    double x;
    cin >> x;
    cout << "\nVoi x=" << x << ", gia tri da thuc la: "
         << setprecision(2) << fixed << TinhDaThuc(B, x);
    return 0;
}
