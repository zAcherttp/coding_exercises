#include <iostream>

using namespace std;

int main() {
    char r1[2];
    char r2[2];
    for (int i = 0; i < 2; i++) {
        cin >> r1[i];
    }
    for (int i = 0; i < 2; i++) {
        cin >> r2[i];
    }
    if (r1[0] == '#' && r2[1] == '#' && r1[1] == '.' && r2[0] == '.' || r1[0] == '.' && r2[1] == '.' && r1[1] == '#' && r2[0] == '#') {
        cout << "No";
    } else
        cout << "Yes";
}