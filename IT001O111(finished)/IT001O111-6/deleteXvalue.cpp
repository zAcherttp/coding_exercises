#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, del;
    cin >> n;
    vector<int> vec;
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        cin >> temp;
        vec.push_back(temp);
    }
    cin >> del;
    auto newEnd = std::remove(vec.begin(), vec.end(), del);
    vec.erase(newEnd, vec.end());
    for (int i : vec)
    {
        cout << i << " ";
    }
    return 0;
}