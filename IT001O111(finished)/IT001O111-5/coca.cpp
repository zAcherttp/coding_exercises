#include <bits/stdc++.h>
using namespace std;

int main() {
    string row;
    cin >> row;
    if (row[0] == row[row.size() - 1])
        cout << "Lose";
    else
        cout << "Win";
}