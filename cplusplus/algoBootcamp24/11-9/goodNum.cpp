#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

long m, n;

int main() {
  fastIO cin >> m >> n;
  int count = 0;
  int d = (int)pow(10, (int)log10(m) + 1);
  for (long i = m; i <= n; i += d)
    count++;
  cout << count;
}