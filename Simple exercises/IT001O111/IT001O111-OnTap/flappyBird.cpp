#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    int b[n];
    int aMax = 0, bMin = 100000000;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > aMax)
            aMax = a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        if (b[i] < bMin)
            bMin = b[i];
    }
    int ans = bMin - aMax + 1;
    if (ans >= 0)
        cout << ans;
    else
        cout << 0;
}