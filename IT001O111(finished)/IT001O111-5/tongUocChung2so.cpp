#include <iostream>
#include <cmath>
using namespace std;

#include <bits/stdc++.h>

set<int> getPrimeFactors(int n)
{
    set<int> factors;
    for (int i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            factors.insert(i);
            n /= i;
        }
    }

    if (n > 1)
    {
        factors.insert(n);
    }

    return factors;
}

int sum_common_prime(int n, int m)
{
    set<int> factors_n = getPrimeFactors(n);
    set<int> factors_m = getPrimeFactors(m);

    int sum = 0;
    for (int factor : factors_n)
    {
        if (factors_m.count(factor))
        {
            sum += factor;
        }
    }

    if (sum == 0)
    {
        return -1;
    }

    return sum;
}

int main()
{
    int m, n;
    cin >> m >> n;
    cout << sum_common_prime(m, n);
}