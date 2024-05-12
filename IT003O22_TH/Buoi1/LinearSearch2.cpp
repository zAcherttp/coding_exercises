#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, X, temp;
    cin >> N;
    vector<int> arr;

    for (int i = 0; i < N; i++) {
        cin >> temp;
        arr.push_back(temp);
    }
    cin >> X;

    vector<int> found;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] == X) {
            found.push_back(i);
            count++;
        }
    }

    cout << count << endl;
    if (count) {
        for (int i = 0; i < found.size(); i++) {
            cout << found[i] << " " << found[i] + 1 << endl;
        }
    }

    return 0;
}