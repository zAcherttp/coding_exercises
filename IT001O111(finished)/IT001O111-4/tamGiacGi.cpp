#include <bits/stdc++.h>

using namespace std;

bool isRightTriangle(int a, int b, int c) {
    if (a > b && a > c) {
        return (a * a == b * b + c * c);
    } else if (b > a && b > c) {
        return (b * b == a * a + c * c);
    } else {
        return (c * c == a * a + b * b);
    }
}

bool IsTriangle(int a, int b, int c) {
    return (a + b > c && a + c > b && b + c > a);
}

int main() {
    double a, b, c, s;
    cin >> a >> b >> c;

    if (IsTriangle(a, b, c)) {

        double s, d;
        d = (a + b + c) / 2.0;
        s = round(sqrt(d * (d - a) * (d - b) * (d - c)) * 100) / 100;

        if (isRightTriangle(a, b, c))
            cout << "Tam giac vuong, dien tich = " << setprecision(2) << fixed << s;
        else if (a == b && a == c)
            cout << "Tam giac deu, dien tich = " << setprecision(2) << fixed << s;
        else if (a == b || a == c || b == c)
            cout << "Tam giac can, dien tich = " << setprecision(2) << fixed << s;
        else
            cout << "Tam giac thuong, dien tich = " << setprecision(2) << fixed << s;
    } else
        cout << "Khong phai tam giac";
}