#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, start, range;
    cin >> n;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        vec.push_back(temp);
    }
    cin >> start >> range;
    vec.erase(vec.begin() + start, vec.begin() + start + range);
    for (int i : vec) {
        cout << i << " ";
    }
    return 0;
}