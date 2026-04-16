#include <iostream>
#include <string.h>
using namespace std;
#define MAX 300

bool checkNum(char n) {
    int m = n;
    return !(48 <= m && m <= 57);
}

int main() {
    char input[MAX];
    cin.getline(input, MAX);
    int length = 0;
    while (input[length] != '\0' && length < MAX) {
        length++;
    }
    for (int i = 0; i < length; i++) {
        cout << "checking " << i << ": [" << input[i] << "]"
             << "\n";
        if (checkNum(input[i])) {
            // cout << "\t" << "passed case 1: [" << input[i] << "]" << "\n";
            continue;
        } else {
            // cout << "\t" << "passed case 2: [" << input[i] << "]" << "\n";
            cout << "CHUOI KHONG HOP LE.";
            goto end;
        }
        // cout << "\t" << "reached end" << "\n";
        goto print;
    }
print:
    for (int i = 0; i < length; i++) {
        cout << input[i];
    }
end:
    return 0;
}