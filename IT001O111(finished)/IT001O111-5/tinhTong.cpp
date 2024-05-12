#include <iostream>
using namespace std;

int sum_even_divisor(int n) {
    int sum = 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0 && i % 2 == 0) {
            sum += i;
        }
    }
    if (sum == 0)
        return -1;
    else
        return sum;
}

int Input() {
    int n;
    cin >> n;
    return n;
}

int main() {
    int n;
    n = Input();
    cout << sum_even_divisor(n);
}
