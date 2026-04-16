#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int n, k;

int main() {
  fastIO;
  cin >> n >> k;
  vector<int> a(n);
  for (auto &e : a)
    cin >> e;

  int pos = 0;
  int cost = 0;
  int j = 1;
  for (int i = pos; i < n - 1; i += j) {
    int m = abs(a[i] - a[i + 1]);
    j = 1;
    cout << pos << ' ' << m << ' ' << cost << '\n';
    for (int p = pos + 1; p < i + k - 1; p++) {
      cout << p << ' ' << abs(a[i] - a[p]) << '\n';
      if (abs(a[i] - a[p]) <= m) {
        m = abs(a[i] - a[p]);
        pos = p;
        j = p - i;
      }
    }
    cost += m;
  }
  cout << cost;
}