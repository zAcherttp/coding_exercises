#include <iostream>
using namespace std;
int modulo(int m, int n)
{
    if (n > m)
    {
        return m;
    }
    else
    {
        return modulo(m - n, n);
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    cout << modulo(m, n);
}