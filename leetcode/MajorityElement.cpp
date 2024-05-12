#include <bits/stdc++.h>
using namespace std;

int MajorityElement(int n) {
    int freq[50000];
    int maxFreq = 0;
    int maxFreqNum;
    for (int i = 0; i < n; i++) {
        int tempInput;
        cin >> tempInput;
        freq[tempInput]++;
        if (freq[tempInput] > maxFreq) {
            maxFreq = freq[tempInput];
            maxFreqNum = tempInput;
        }
    }
    return maxFreqNum;
}

int main() {
    int num;
    cin >> num;
    cout << MajorityElement(num);
}