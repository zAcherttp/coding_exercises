#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int m, n;
char a[1000][1000];
bool v[1000][1000] = {false};

int solve(int y, int x, bool c) {
  int ans = 0;
  bool up = !v[y + 1][x];
  bool down = !v[y - 1][x];
  bool left = !v[y][x - 1];
  bool right = !v[y][x + 1];
  if (a[y][x] == 'A') {

    if (up)
      ans += solve(y + 1, x, true);
    if (down)
      ans += solve(y - 1, x, true);
    if (left)
      ans += solve(y, x - 1, true);
    if (right)
      ans += solve(y, x + 1, true);
  } else if (a[y][x] == 'C' && c) {
    if (up)
      ans += solve(y + 1, x, true);
    if (down)
      ans += solve(y - 1, x, true);
    if (left)
      ans += solve(y, x - 1, true);
    if (right)
      ans += solve(y, x + 1, true);
  } else if (a[y][x] == 'M' && c) {

    return 1;
  }
  if (y == m - 1 && x == n - 1) {
    return ans;
  }
  return ans;
}

int main() {
  fastIO cin >> m >> n;
  int ans = 0;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      ans += solve(i, j, v[i][j]);
  cout << ans;
}
