#include <iostream>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool isComposite(int n) {
    return !isPrime(n);
}

int main() {
    int n;
    cin >> n;
    if (n == 1)
        cout << -1;
    else if (isPrime(n)) {
        cout << 1;
    } else if (!isPrime(n)) {
        cout << 0;
    } else
        cout << -1;

    return 0;
}