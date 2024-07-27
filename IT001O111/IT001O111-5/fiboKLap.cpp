#include <iostream>
using namespace std;
#define MAX 300

int Fibo(int);

int main() {
    int x;
    cin >> x;
    if (x < 1 || x > 30)
        cout << "So " << x << " khong nam trong khoang [1,30]." << endl;
    else {
        cout << Fibo(x) << endl;
    }
    return 0;
}

int Fibo(int x) {
    if (x == 0 || x == 1) {
        return x;
    }
    int a = 0, b = 1, c = 0;
    for (int i = 2; i <= x; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}