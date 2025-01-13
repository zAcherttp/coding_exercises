#include <bits/stdc++.h>

using namespace std;

int main() {
    int p;
    cin >> p;
    string l = to_string(p);
    int x[l.size()];

    // xếp input vào array 4 chỗ theo lề phải
    int digit;
    for (int i = 0; i < l.size(); i++) {
        digit = p % 10;
        x[i] = digit;
        p /= 10;
    }

    int xx = 0;
    for (int i = 0; i < l.size(); i++)
        xx += x[i];
    cout << xx;
    return 0;
}