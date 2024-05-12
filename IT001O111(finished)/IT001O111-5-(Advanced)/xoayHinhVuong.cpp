#include <iostream>
#include <vector>
using namespace std;

int countSubMatrices(const vector<vector<char>> &l, const vector<vector<char>> &s) {
    int m = l.size();
    int n = s.size();
    int count = 0;

    for (int i = 0; i <= m - n; i++) {
        for (int j = 0; j <= m - n; j++) {
            int flag = 0;
            for (int k = 0; k < n; k++) {
                for (int g = 0; g < n; g++) {
                    if (l[i + k][j + g] == s[k][g]) {
                        flag++;
                    } else {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag == n * n) {
                count++;
            }
        }
    }
    return count;
}

void rotateClockwiseBy90(vector<vector<char>> &m) {

    int n = m.size();
    vector<vector<char>> temp(n, vector<char>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[j][n - i - 1] = m[i][j];
        }
    }

    m = temp;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (true) {
        int m, n;
        cin >> m >> n;
        int count[4] = {0, 0, 0, 0};
        vector<vector<char>> l(m, vector<char>(m)),
            s(n, vector<char>(n));
        if (m == 0 || n == 0) {
            break;
        }

        // inputMatrix
        for (int i = 0; i < m; i++) {
            string inputL = "temp";
            cin >> inputL;
            for (int j = 0; j < m; j++) {
                l[i][j] = inputL[j];
            }
        }
        for (int i = 0; i < n; i++) {
            string inputS = "temp";
            cin >> inputS;
            for (int j = 0; j < n; j++) {
                s[i][j] = inputS[j];
            }
        }

        // rotate & compare
        count[0] = countSubMatrices(l, s);
        rotateClockwiseBy90(s);
        count[1] = countSubMatrices(l, s);
        rotateClockwiseBy90(s);
        count[2] = countSubMatrices(l, s);
        rotateClockwiseBy90(s);
        count[3] = countSubMatrices(l, s);

        // print result
        for (int i = 0; i < 4; i++) {
            cout << count[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
