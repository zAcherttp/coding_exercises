#include <bits/stdc++.h>

using namespace std;
int main() {
  int n, k, a, b;
  cin >> n >> k >> a >> b;

  int t = 0;
  while (n > 1) {
    if (n % k == 0) {
      n /= k;
      t += b;
    } else {
      n--;
      t += a;
    }
  }
  cout << t;

  return 0;
}
