#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

string s;

int main() {
  fastIO cin >> s;
  int l = 0, r = s.size() - 1;
  if (s[l] != s[r])
    cout << "Win";
  else
    cout << "Lose";
}