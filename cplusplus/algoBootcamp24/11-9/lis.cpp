#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int n;

int main() {
  cin >> n;
  vector<int> a(n);

  for (auto &e : a)
    cin >> e;
  vector<int> b;
  b.push_back(a[0]);
  for (auto e : a)
    if (e > b.back())
      b.push_back(e);
  cout << b.size() << '\n';
  for (auto a : b)
    cout << a << ' ';
}