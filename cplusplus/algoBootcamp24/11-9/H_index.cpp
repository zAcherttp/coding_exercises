#include <bits/stdc++.h>
using namespace std;

#define fastIO                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);

int n;

int main() {
  cin >> n;
  vector<int> article(n);
  for (auto &a : article)
    cin >> a;
  sort(article.begin(), article.end());
  article.erase(article.begin(),
                lower_bound(article.begin(), article.end(), n));
  cout << article.size() + 1 << endl;
}