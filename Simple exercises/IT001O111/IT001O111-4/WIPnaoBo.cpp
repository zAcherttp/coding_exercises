#include <bits/stdc++.h>

using namespace std;

bool IsPrime(int a) {
    for (int i = 2; i * i <= a; i++)
        if (a % i == 0)
            return false;
    if (a == 1)
        return false;
    return true;
}

int main() {

    int n;
    cin >> n;

    int nArray[n];
    for (int i = 0; i < n; i++) {
        cin >> nArray[i];
    }

    vector<int> prime;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        if (IsPrime(nArray[i])) {
            prime.push_back(nArray[i]);
            pos.push_back(i);
        }
    }

    int minPrimePos = 0;
    for (int i = 0; i < prime.size(); i++) {
        if (prime[i] <= prime[0])
            minPrimePos = pos[i];
    }
    /* SAI
        if (prime.size() > 1) {
            cout << minPrimePos + 1 << " " << 1 << endl;
        }
    */
    if (prime.size() == 1 && prime[0] == 1) {
        cout << pos[0] + 1 << 0; // tìm ưcln của dãy còn lại
    }

    for (int i = 0; i < prime.size(); i++) {
        cout << prime[i] << " ";
    }

    return 0;
}