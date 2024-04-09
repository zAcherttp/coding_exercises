#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    vector<int> line;
    unordered_map<int, bool> check;
    unordered_map<int, bool> check_printed;
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        line.push_back(temp);
        check[temp] = true;
    }

    for(int i = line.size(); i >= 0; i--)
    {
        if(check[line[i]] && !check_printed[line[i]])
        {
            cout << line[i] << ' ';
            check_printed[line[i]] = true;
        }
    }

    for(int i = 1; i <= n; i++)
    {
        if(!check[i]) cout << i << ' ';
    }

    return 0;
}