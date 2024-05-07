#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;

vector<int> get_ans(const vector<int> &A, int K)
{
    map<int, int> Hash;
    vector<int> ans;

    for (auto i : A)
    {
        Hash[i]++;
    }

    auto it = Hash.begin();
    for (it; it != Hash.end() && K != 0; it++)
    {
        ans.push_back(it->first);
        it->second--;
        K--;
    }

    it = Hash.begin();
    while (K != 0)
    {
        if (it->second == 0)
            it++;
        else
        {
            ans.push_back(it->first);
            it->second--;
            K--;
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> ans = get_ans(a, k);

    for (const int &x : ans)
        cout << x << ' ';
    return 0;
}