#include <iostream>
using namespace std;

int main()
{
    int N, sigma = 0;
    cin >> N;
    int c[N], d[360] = {0};
    d[359] = 1;
    for (int i = 0; i < N; i++)
    {
        cin >> c[i];
        sigma += c[i];
        d[sigma % 360 - 1] = 1;
    }
    int degreeCount = 1, dMax = 0;
    for (int i = 0; i < 360; i++)
    {
        if (!d[i])
        {
            degreeCount++;
        }
        else
        {
            if (degreeCount > dMax)
                dMax = degreeCount;
            degreeCount = 1;
        }
    }
    cout << dMax;
}