#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int n;
void Binary(int n) {
  int d = 1 << n;
  for (int i = 0; i < d; i++) {
    for (int j = n - 1; j >= 0; j--) {
      if (i & (1 << j))
        cout << 1;
      else
        cout << 0;
    }
    cout << '\n';
  }
}
int main() {
  fastIO cin >> n;

  Binary(n);
}