#include <bits/stdc++.h>
using namespace std;

int n, k, p, x, ans = 0;
vector<int> a;

void upd(int i, int x) {
  a[p + i] = x;
  for (int j = (p + i) / 2; j > 0; j >>= 1)
    a[j] = __gcd(a[2 * j], a[2 * j + 1]);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  p = 1;
  while (p < k)
    p <<= 1;
  a.assign(4 * p + 5, 0);
  for (int i = 0; i < k; ++i)
    cin >> a[p + i];
  for (int i = p - 1; i > 0; --i)
    a[i] = __gcd(a[2 * i], a[2 * i + 1]);
  ans = a[1];
  for (int i = k; i < n; ++i) {
    cin >> x;
    upd(i % k, x);

    if (ans < a[1])
      ans = a[1];
  }
  cout << ans;
}
