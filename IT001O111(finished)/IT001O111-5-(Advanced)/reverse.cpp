#include <iostream>
using namespace std;
int reverse(int a)
{
    int x = 0;
    while (a)
        x = x * 10 + a % 10, a /= 10;
    return x;
}
int main()
{
    int n;
    cin >> n;
    cout << reverse(n);
}
