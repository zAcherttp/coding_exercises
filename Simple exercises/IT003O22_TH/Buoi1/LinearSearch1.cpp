#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, X, temp;
    int i;
    cin >> N;
    vector<int> arr;

    for (int i = 0; i < N; i++) {
        cin >> temp;
        arr.push_back(temp);
    }
    cin >> X;

    int found = 0;
    for (i = 0; i < N; i++) {
        if (arr[i] == X) {
            found = 1;
            break;
        }
    }

    if (found) {
        cout << i << endl;
        cout << i + 1 << endl;
        cout << N - 1 - i << endl;
        cout << N - i << endl;
    } else {
        cout << -1;
    }

    return 0;
}