#include <bits/stdc++.h>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<double>> matrix(m, vector<double>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == matrix[j][i]) {
                continue;
            } else {
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    return 0;
}