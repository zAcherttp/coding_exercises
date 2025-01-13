#include <chrono>
#include <iostream>
#include <string.h>

using namespace std;
using namespace chrono;

int n;
int a[20001];

int main() {
    cin >> n;

    auto start_time = high_resolution_clock::now();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            if (i * j <= n)
                a[i * j]++;
            else
                break;
    }
    int ans = 0;
    for (int i = 1; i < n; i++)
        ans += a[i] * a[n - i];

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);

    cout << "Result: " << ans << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
}