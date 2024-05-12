#include <cmath>
#include <iostream>

using namespace std;

int search_binary(string data[], string query, int N, int &count) {
    int left = 0, right = N - 1;
    count = 0;
    while (left <= right) {
        count += 1;
        int mid = floor((left + right) / 2);

        if (data[mid] < query) {
            left = mid + 1;
        } else if (data[mid] > query) {
            right = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int main() {
    int N;
    cin >> N;
    string data[N], X;

    for (int i = 0; i < N; i++) {
        cin >> data[i];
    }
    cin >> X;

    int index, count;
    cout << search_binary(data, X, N, count) << endl;
    if (search_binary(data, X, N, count) != -1)
        cout << count << endl;

    return 0;
}