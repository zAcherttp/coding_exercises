#include <iostream>
#include <bits/stdc++.h>

using namespace std;

double calculate(int n)
{
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum = sqrt(i + sum);
        cout << sum << endl;
    }
    return sum;
}

int main()
{
    int n;
    cin >> n;
    cout << setprecision(3) << calculate(n);
}