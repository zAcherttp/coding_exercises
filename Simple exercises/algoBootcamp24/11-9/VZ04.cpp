#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

string s;

string vz(string s) {
  set<char> set = {'a', 'e', 'i', 'o', 'u', 'w', 'y'};
  string ans;
  ans += toupper(s[0]);
  for (int i = 1; i < s.size(); i++)
    if (set.find(s[i]) == set.end() && set.find(s[i - 1]) == set.end()) {
      if (islower(ans.back()))
        ans += toupper(s[i]);
      else
        ans += tolower(s[i]);
    } else
      ans += tolower(s[i]);
  return ans;
}

int main() {
  fastIO cin >> s;
  cout << vz(s);
  return 0;
}
