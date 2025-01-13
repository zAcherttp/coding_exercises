#include <iostream>
#include <vector>
using namespace std;

void MEX(vector<int> arr) {
    vector<bool> check(arr.size() + 1, false);
    int mex = 0;
    for (int i = 0; i < arr.size(); i++) {
        check[arr[i]] = true;
        int j = mex;
        while (check[j]) {
            j++;
        }
        mex = j;
        cout << mex << " ";
    }
}

int main() {
    int N, temp;
    cin >> N;
    vector<int> arr;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        arr.push_back(temp);
    }
    MEX(arr);
    return 0;
}