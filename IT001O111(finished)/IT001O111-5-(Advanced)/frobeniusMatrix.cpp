#include <bits/stdc++.h>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int m, n;
    cin >> m >> n;
    double a[m][n];
    int non_zero_column = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    }
    for (int i = 0; i < n; i++) {
        if (a[i][i] != 1) {
            cout << "No";
            goto end;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (a[i - 1][j] != 0) {
                cout << "No";
                goto end;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j][i] != 0) {
                non_zero_column++;
                break;
            }
        }
        if (non_zero_column == 2) {
            cout << "No";
            goto end;
        }
    }
    cout << "Yes";
end:
    return 0;
}