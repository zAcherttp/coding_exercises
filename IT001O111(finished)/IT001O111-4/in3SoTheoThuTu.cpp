#include <bits/stdc++.h>

using namespace std;

int main()
{
    double a, b, c, M, m;
    cin >> a >> b >> c;
    if (a >= b)
        M = a;
    else
        M = b;
    if (M <= c)
        M = c;
    if (a >= b)
        m = b;
    else
        m = a;
    if (m >= c)
        m = c;
    cout << m << " " << a + b + c - M - m << " " << M;
    return 0;
}