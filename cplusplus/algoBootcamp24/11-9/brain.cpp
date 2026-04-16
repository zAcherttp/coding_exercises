#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int n, ans, id = 0;
vector<int> a, pre, suf;

int main() {
  fastIO cin >> n;
  a.resize(n);
  pre.resize(n + 2);
  suf.resize(n + 2);
  for (auto &e : a)
    cin >> e;
  pre[1] = a[0];
  for (int i = 2; i <= n; i++)
    pre[i] = __gcd(pre[i - 1], a[i - 1]);
  suf[n] = a[n - 1];
  for (int i = n - 1; i >= 1; i--)
    suf[i] = __gcd(suf[i + 1], a[i - 1]);

  ans = max(suf[2], pre[n - 1]);
  if (suf[2] >= pre[n - 1])
    id = 1;
  else
    id = n;

  for (int i = n - 1; i > 1; i--)
    if (__gcd(pre[i - 1], suf[i + 1]) > ans)
      ans = __gcd(pre[i - 1], suf[i + 1]), id = i;

  cout << id << " " << ans;
}
