#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        cin >> temp;
        v.push_back(temp);
    }
    int insert;
    cin >> insert;
    int index;
    cin >> index;

    v.insert(v.begin() + index, insert);

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }

    return 0;
}