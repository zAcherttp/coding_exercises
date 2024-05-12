#include <iostream>
#include <vector>

using namespace std;
#define type int

string whetherAnEqualSubmatrixExists(const vector<vector<type>> &l, const vector<vector<type>> &s) {
    // getSizes
    int m = l.size(), n = l[0].size();
    int r = s.size(), c = s[0].size();

    // loopDetect, 1 if found -1 otherwise
    for (int i = 0; i <= m - r; i++) {
        for (int j = 0; j <= n - c; j++) {
            int flag = 0;
            for (int k = 0; k < r; k++) {
                for (int g = 0; g < c; g++) {
                    if (l[i + k][j + g] == s[k][g]) {
                        flag++;
                    } else {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag == r * c) {
                return "co B trong A";
                // return 1;
            }
        }
    }
    return "khong co B trong A";
    // return -1;
}

int main() {
    // inputMatricesSizes
    int m, n, r, c;
    do {
        cout << "nhap ma tran kich thuoc m x n and ma tran con r x c: ";
        cin >> m;
        if (m == 0) {
            cout << "thua" << endl;
            continue;
        }
        cin >> n;
        if (n == 0) {
            cout << "thua" << endl;
            continue;
        }
        cin >> r;
        if (r == 0 || r > m) {
            cout << "thua" << endl;
            continue;
        }
        cin >> c;
        if (c == 0 || c > n) {
            cout << "thua" << endl;
            continue;
        }
        break;

    } while (true);

    vector<vector<type>> l_matrix(m, vector<type>(n)), s_matrix(r, vector<type>(c));

    // inputMatrices
    // inputLargerMatrix
    type inputL;
    for (int i = 0; i < m; i++) {
        cout << "nhap hang " << i + 1 << " (" << n << " so): ";
        for (int j = 0; j < n; j++) {
            cin >> inputL;
            l_matrix[i][j] = inputL;
        }
    }
    // inputSmallerMatrix
    type inputS;
    for (int i = 0; i < r; i++) {
        cout << "nhap hang " << i + 1 << " (" << c << " so): ";
        for (int j = 0; j < c; j++) {
            cin >> inputS;
            s_matrix[i][j] = inputS;
        }
    }

    // printResult
    cout << whetherAnEqualSubmatrixExists(l_matrix, s_matrix);

    return 0;
}
