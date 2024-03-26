#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<double>> matrix(m, vector<double>(n));
    vector<vector<double>> tranposedMatrix(n, vector<double>(m));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tranposedMatrix[j][i] = matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << tranposedMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}