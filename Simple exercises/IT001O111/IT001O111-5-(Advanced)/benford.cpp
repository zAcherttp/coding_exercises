#include <iostream>
using namespace std;
#define MAX 100

bool isBenford(int a[], int n) {
    int freq1 = 0;
    int freq4 = 0;
    for (int i = 0; i < n; i++) {
        string num = to_string(a[i]);
        a[i] = stoi(num.substr(0, 1));
        if (a[i] == 4)
            freq4++;
        if (a[i] == 1)
            freq1++;
    }
    if (freq1 == 3 && freq4 == 1)
        return true;
    else
        return false;
}

int Nhapmang(int a[], int n) {
    for (int i = 0; i < n; i++)
        cin >> a[i];
    return 0;
}

int main() {
    int a[MAX], n = 10;
    Nhapmang(a, n);
    if (isBenford(a, n) == true)
        cout << "TRUE" << endl;
    else
        cout << "FALSE" << endl;
    return 0;
}