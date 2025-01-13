#include <bits/stdc++.h>

using namespace std;

int main() {

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  cin >> t;

  for (int i = 0; i < t; i++) {
    long k;
    cin >> k;

    long n = sqrt(k);
    long j = 0;
    while ((n - j) * (n) + (n - j + 1) * (n + 1) > 2 * k) {
      j++;
    }
    if ((n - j) * (n) + (n - j + 1) * (n + 1) == 2 * k) {
      cout << n - j << " " << n << '\n';
    } else {
      cout << -1 << " " << -1 << '\n';
    }
  }
}