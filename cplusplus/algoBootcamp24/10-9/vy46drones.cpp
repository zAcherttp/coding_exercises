#include <bits/stdc++.h>

using namespace std;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  cin >> n;
  vector<pair<float, int>> array(n);

  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    array[i].first = sqrt(x * x + y * y);
    array[i].second = i + 1;
    }

  sort(array.begin(), array.end());
  for (int i = 0; i < array.size(); i++) {
    if (array[i].first <= i / 1.0) {
      cout << -1;
      return 0;
    }
  }
  for (auto i : array) {
    cout << i.second << " ";
  }

  return 0;
}
