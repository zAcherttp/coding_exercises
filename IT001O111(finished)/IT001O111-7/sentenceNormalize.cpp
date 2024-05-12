#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    string u = s;
    string a = " ";

    while (s.find("  ") != string::npos) {
        s.erase(s.find("  "), 1);
    }

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            if (s[i - 1] == ' ')
                s.erase(i - 1, 1);
            if (s[i + 1] != ' ')
                s.insert(i, a);
        }
    }

    while (s.find("  ") != string::npos) {
        s.erase(s.find("  "), 1);
    }

    cout << u << '\n';
    cout << s;

    return 0;
}