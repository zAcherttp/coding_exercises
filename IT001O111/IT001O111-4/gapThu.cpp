#include <bits/stdc++.h>

using namespace std;

int main() {
    long double n, m, h, w;
    cin >> n >> m >> h >> w;

    long double fn, fm;
    fn = n;
    fm = m;

    int gap1 = 0;
    while (fn > h) {
        fn /= 2;
        gap1 += 1;
    }
    while (fm > w) {
        fm /= 2;
        gap1 += 1;
    }
    // cout << "gap khong xoay: " << gap << " lan" << endl;

    fn = n;
    fm = m;
    int gap2 = 0;
    while (fn > w) {
        fn /= 2;
        gap2 += 1;
    }
    while (fm > h) {
        fm /= 2;
        gap2 += 1;
    }
    // cout << "gap xoay: " << gap << " lan" << endl;

    if (gap2 < gap1)
        cout << gap2;
    else
        cout << gap1;

    return 0;
}