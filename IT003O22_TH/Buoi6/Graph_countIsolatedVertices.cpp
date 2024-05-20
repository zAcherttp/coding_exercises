#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int m, n, count = 0;
    unordered_map<int, int> edges;
    cin >> m >> n;
    n *= 2;
    while(n--)
    {
        int temp;
        cin >> temp;
        edges[temp]++;
    }

    while(m--)
    {
        if(edges[m] == 0) count++;
    }
    cout << count;
    return 0;
}