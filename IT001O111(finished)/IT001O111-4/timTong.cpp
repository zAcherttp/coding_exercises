#include <bits/stdc++.h>

using namespace std;

bool check_sum(int array[], int size, int sum) {
    std::unordered_map<int, bool> seen;
    for (int i = 0; i < size; i++) {
        if (seen.count(sum - array[i])) {
            return true;
        }
        seen[array[i]] = true;
    }
    return false;
}

int main() {
    int arraySize;
    cin >> arraySize;

    int array[arraySize];
    for (int i = 0; i < arraySize; i++) {
        cin >> array[i];
    }

    int sum;
    cin >> sum;

    if (check_sum(array, arraySize, sum))
        cout << "YES";
    else
        cout << "NO";
}