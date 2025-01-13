#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int n;
int a[10];
vector<pair<int, int>> arr;

void solve(int row) {
  if (row == n) {
    vector<pair<int, int>> layout;
    for (int i = 0; i < n; i++) {
      layout.push_back({i, a[i]});
      arr.push_back({i, a[i]});
    }
    cout << "[";
    for (int i = 0; i < n; i++) {
      cout << "(" << layout[i].first + 1 << ", " << layout[i].second + 1 << ")";
      if (i != n - 1)
        cout << " ";
    }
    cout << "]" << '\n';
    return;
  }

  for (int col = 0; col < n; col++) {
    bool canPlace = true;
    for (int i = 0; i < row; i++) {
      if (a[i] == col || abs(a[i] - col) == abs(i - row)) {
        canPlace = false;
        break;
      }
    }
    if (canPlace) {
      a[row] = col;
      solve(row + 1);
    }
  }
}

int main() {
  fastIO cin >> n;
  solve(0);
  if (arr.empty())
    cout << "No solution found.";
  return 0;
}