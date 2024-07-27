#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> n;
    vector<int> vecM, vecN;
    deque<int> deq;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        vecN.push_back(temp);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int temp = 0;
        cin >> temp;
        vecM.push_back(temp);
    }

    for (int i = 0; i < m + n; i++) {
        if (vecN[vecN.size() - 1] > vecM[vecM.size() - 1]) {
            deq.push_front(vecN[vecN.size() - 1]);
            vecN.pop_back();
        } else {
            deq.push_front(vecM[vecM.size() - 1]);
            vecM.pop_back();
        }
    }
    for (int i : deq) {
        cout << i << " ";
    }

    return 0;
}