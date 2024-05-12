#include <iostream>
using namespace std;

string checkWin(int a[][3]) {
    for (int i = 0; i < 3; i++) {
        if (a[i][0] == 0 && a[i][1] == 0 && a[i][2] == 0) {
            return "Yes";
        }
    }

    for (int j = 0; j < 3; j++) {
        if (a[0][j] == 0 && a[1][j] == 0 && a[2][j] == 0) {
            return "Yes";
        }
    }

    if (a[0][0] == 0 && a[1][1] == 0 && a[2][2] == 0) {
        return "Yes";
    }
    if (a[0][2] == 0 && a[1][1] == 0 && a[2][0] == 0) {
        return "Yes";
    }

    return "No";
}

int main() {
    int a[3][3];
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". - - - ? ";
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }

    int n;
    cout << "n = ";
    cin >> n;

    int b[n];
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[k] - a[i][j] == 0)
                    a[i][j] = 0;
            }
        }
    }

    cout << checkWin(a);
    return 0;
}