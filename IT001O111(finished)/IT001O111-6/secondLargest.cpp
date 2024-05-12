#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, first = 0, second = 0;
    cin >> n;
    vector<int> v;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        v.push_back(temp);
    }

    if (n == 0) {
        goto end;
    }
    for (int i = 0; i < n; i++) {
        sum += v[i];
    }
    if (sum == v[0] * v.size()) {
        goto end;
    }

    for (int i = 0; i < n; i++) {
        if (v[i] > first) {
            first = v[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (v[i] > second && v[i] < first) {
            second = v[i];
        }
    }

end:
    cout << second << endl;
    return 0;
}