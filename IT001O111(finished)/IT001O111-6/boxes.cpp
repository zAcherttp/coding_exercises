#include <bits/stdc++.h>
using namespace std;

int main()
{
    int h, w;
    cin >> w >> h;
    vector<vector<int>> l(h, vector<int>(w));
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            cin >> l[i][j];
        }
    }

    int min = l[0][0];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (min > l[i][j])
            {
                min = l[i][j];
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            sum += l[i][j] - min;
        }
    }

    cout << sum;
    return 0;
}
