#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    double a[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    }
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i][i];
    cout << sum;
    return 0;
}