#include <iostream>

using namespace std;

int sum(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
        if (sum == 0)
            return -1;
    }
    return sum;
}

int main() {
    int n;
    cin >> n;
    int sumOfDivisors = sum(n);
    cout << sumOfDivisors;
    return 0;
}