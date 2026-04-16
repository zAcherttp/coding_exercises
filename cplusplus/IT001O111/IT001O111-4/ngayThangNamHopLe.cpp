#include <bits/stdc++.h>

using namespace std;

bool namNhuan(int n) {
    return (n % 4 == 0 && n % 100 != 0 || n % 400 == 0);
}

int main() {
    int ngay, thang, nam;
    cin >> ngay >> thang >> nam;
    if (nam <= 0)
        cout << "Nam khong hop le.";
    else if (thang > 12 || thang < 1)
        cout << "Thang khong hop le.";
    else if (ngay < 1)
        cout << ngay << "/" << thang << "/" << nam << " la ngay khong hop le.";
    else if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        if (ngay < 31)
            cout << ngay << "/" << thang << "/" << nam << " la ngay hop le.";
        else
            cout << ngay << "/" << thang << "/" << nam << " la ngay khong hop le.";
    } else if (thang == 2) {
        if (namNhuan(nam)) {
            if (ngay < 30)
                cout << ngay << "/" << thang << "/" << nam << " la ngay hop le.";
            else
                cout << ngay << "/" << thang << "/" << nam << " la ngay khong hop le.";
        } else {
            if (ngay < 29)
                cout << ngay << "/" << thang << "/" << nam << " la ngay hop le.";
            else
                cout << ngay << "/" << thang << "/" << nam << " la ngay khong hop le.";
        }
    } else if (thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10 || thang == 12) {
        if (ngay < 32)
            cout << ngay << "/" << thang << "/" << nam << " la ngay hop le.";
        else
            cout << ngay << "/" << thang << "/" << nam << " la ngay khong hop le.";
    }

    return 0;
}