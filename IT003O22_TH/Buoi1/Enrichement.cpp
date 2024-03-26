#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> l(m, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> l[i][j];
        }
    }

    int oreWorthSumMin = numeric_limits<int>::max();

    for (int i = 0; i <= m - 3; i++)
    {
        for (int j = 0; j <= n - 3; j++)
        {
            int oreWorthSum = 0;
            oreWorthSum += l[i][j] + l[i][j + 1] + l[i][j + 2] + l[i + 1][j] + l[i + 1][j + 1] + l[i + 1][j + 2] + l[i + 2][j] + l[i + 2][j + 1] + l[i + 2][j + 2];
            if (oreWorthSum < oreWorthSumMin)
            {
                oreWorthSumMin = oreWorthSum;
            }
        }
    }
    cout << oreWorthSumMin;
    return 0;
}