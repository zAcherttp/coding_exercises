#include <iostream>

using namespace std;

int input()
{
    int m;
    cin >> m;
    return m;
}

int input(int &b)
{
    cin >> b;
    return b;
}

int TongUocChung(int a, int b)
{
    int sum = 0;
    int smallerNum;
    if (a < b)
        smallerNum = a;
    else
        smallerNum = b;
    for (int i = 1; i <= smallerNum; i++)
    {
        if (a % i == 0 && b % i == 0)
        {
            sum += i;
        }
    }
    if (sum == 0)
        return -1;
    else
        return sum;
}

int main()
{
    int a, b;
    a = input();
    input(b);
    std::cout << TongUocChung(a, b);
    return 0;
}