#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int n;
void permutation(int n) {
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  do {
    for (auto &e : a)
      cout << e << ' ';
    cout << '\n';
  } while (next_permutation(a.begin(), a.end()));
}
int main() {
  fastIO cin >> n;

  permutation(n);
}