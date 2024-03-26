#include <bits/stdc++.h>

using namespace std;

int main()
{
    double diem, temp;
    int n;
    cin >> diem >> n;
    temp = round(diem * n);
    diem = temp / n;
    cout << setprecision(10) << diem;
    return 0;
}
