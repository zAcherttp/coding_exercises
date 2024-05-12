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
    if (x == 1) {
        return 1;
    } else {
        int f1 = 0, f2 = 1;
        for (int i = 1; i < x; i++) {
            int temp = f2;
            f2 = f1 + f2;
            f1 = temp;
        }
        return f2;
    }
}