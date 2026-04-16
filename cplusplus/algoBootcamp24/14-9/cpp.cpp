#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr);

int m, n, k;

int main() {
  fastIO cin >> n >> m >> k;
  char a[n + 1][m + 1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      a[i][j] = '.';
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[n][j] == '.' && a[i][m] == '.' && k > 0) {
        a[i][j] = '*';
        a[n][j] = '*';
        a[i][m] = '*';
        k--;
      }
    }
  }
  if (k > 0) {
    cout << "Impossible";
    return 0;
  }
  cout << "Possible\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << a[i][j];
    }
    cout << '\n';
  }
}