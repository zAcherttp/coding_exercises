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

void Xuat(DATHUC &B)
{
    Node *current = B.head;
    bool isFirst = true;
    while (current != nullptr)
    {
        if (current->data->heso != 0)
        {
            if (!isFirst && current->data->heso > 0)
                std::cout << "+";

            if (current->data->heso != 1 && current->data->heso != -1 && current->data->somu != 0)
                std::cout << current->data->heso;

            if (current->data->heso == -1 && current->data->somu != 0)
                std::cout << "-";

            if (current->data->somu != 0)
                std::cout << "x";

            if (current->data->somu != 1 && current->data->somu != 0)
                std::cout << "^" << current->data->somu;

            if (current->data->somu == 0)
                std::cout << current->data->heso;

            if (isFirst)
                isFirst = false;
        }

        current = current->next;
    }
    if (isFirst)
        cout << "0";
}

void Nhap(DATHUC &B, double &heso, int &somu)
{
    DONTHUC *_donthuc = new DONTHUC(heso, somu);
    Node *node = new Node(_donthuc);
    if (!B.head)
    {
        B.head = node;
        B.tail = node;
    }
    else
    {
        B.tail->next = node;
        B.tail = node;
    }
}

double TinhDaThuc(DATHUC B, double x)
{
    double sum = 0.0;
    Node *current = B.head;

    while (current != nullptr)
    {
        sum += current->data->heso * pow(x, current->data->somu);
        current = current->next;
    }

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
