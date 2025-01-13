#include <iostream>
using namespace std;
#include <cmath>

int sum_all_square(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && floor(sqrt(i)) * floor(sqrt(i)) == i) {
            sum += i;
        }
    }
    if (sum == 0)
        return -1;
    else
        return sum;
}

int main() {
    int n;
    cin >> n;
    cout << sum_all_square(n);
}
