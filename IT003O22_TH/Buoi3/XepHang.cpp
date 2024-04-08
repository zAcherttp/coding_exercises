#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    vector<int> line;
    unordered_map<int, int> check;
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        line.push_back(temp);
        check[temp]++;
    }

    for(int i = line.size(); i >= 0; i--)
    {
        if(check[line[i]] == 1) cout << line[i] << ' ';
    }


    for(int i = 0; i < n; i++)
    {
        if(check[line[i]] == 0) cout << i - 1 << ' ';
    }
    return 0;
}