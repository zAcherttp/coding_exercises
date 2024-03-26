#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, t;
    cin >> n;
    vector<bool> check(n + 1, false);
    for(int i = 0; i < n; i++)
    {
        cin >> t;
        if(t <= n)
        check[t] = true;
    }
    for(int i = 0; i <= n; i++)
    {
        if(!check[i])
        {
            cout << i;
            break;
        }
    }
    return 0;
}