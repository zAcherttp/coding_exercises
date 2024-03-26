#include <iostream>
#include <iomanip>
using namespace std;

double pow(double base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    double result = 1.0;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}

double fac(int n)
{
    if (n == 0)
        return 1;
    else
        return n * fac(n - 1);
}

double approx(double x)
{
    double sum = 0.0;
    int sign = 1.0;
    for (int i = 0; i <= 7; i++)
    {
        sum += sign * pow(x, 2 * i + 1) / fac(2 * i + 1);
        sign *= -1;
    }
    return sum;
}

int main()
{
    double x;
    cin >> x;
    double pi = 3.1416;
    while (x < -pi)
        x += 2 * pi;
    while (x > pi)
        x -= 2 * pi;
    cout << fixed << setprecision(4) << approx(x);
}
