#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, inp;
    cin >> n;
    map<int, int> m;
    for (int i{}; i < n; i++)
    {
        cin >> inp;
        m[inp]++;
    }

    int count = 0;

    for (auto i = m.begin(); i != m.end(); i++)
    {
        if (i->first < i->second)
            count += i->second - i->first;
        else if(i->first > i->second)
            count += i->second;
    }

    cout << count;
    return 0;
}