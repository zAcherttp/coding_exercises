// #include <iostream>
// #include <sstream>
// #include <string>
// using namespace std;

// string reverse(string s) {
//     int size = s.size();
//     string temp;
//     for(int i = size - 1; i >= 0; i--) {
//         temp += s[i];
//     }
//     return temp;
// }

// int main() {
//     string t;
//     getline(cin, t);
//     stringstream ss(t);
//     string w;
//     int check = 0;
//     while(ss >> w) {
//         cout << reverse(w) << " "; check++;
//     }
//     if(check == 0) cout << "Chuoi rong.";
//     return 0;
// }
#include <iostream>
#include <string.h>
#include <string>
using namespace std;
#define MAX 300

int myStrcmp(char s1[], char s2[]);
int myStrlen(char s[], int k);
void myStrcpy(char s[], int vt, char s1[], int k);
void mySubstr(char s[], int b, int count, char ss[]);
bool myStrcat(char s1[], char s2[]);
void StringReverse(char st[]);

int main() {
    char s[MAX];
    cin.getline(s, MAX);
    if (myStrcmp(s, "") == 0)
        cout << "Chuoi rong." << endl;
    else {
        StringReverse(s);
        cout << s << endl;
    }
    return 0;
}

int myStrlen(char s[], int k) {
    int length = 0;
    while (s[length + k] != '\0') {
        length++;
    }
    return length;
}

int myStrcmp(char s1[], char s2[]) {
    int l1 = myStrlen(s1, 0);
    int l2 = myStrlen(s2, 0);
    if (l1 < l2) {
        return -1;
    } else if (l1 > l2) {
        return 1;
    } else {
        for (int i = 0; i < l1; i++) {
            if (s1[i] == s2[i]) {
                continue;
            } else {
                if (s1[i] > s2[i]) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }
    return 0;
}

void myStrcpy(char s[], int vt, char s1[], int k) {
    int l1 = myStrlen(s, vt);
    int l2 = myStrlen(s1, k);
    for (int i = 0; i < vt; i++) {
        s[i + vt] = s1[i + k];
    }
}

void mySubstr(char s[], int b, int count, char ss[]) {
    for (int i = 0; i < count; i++) {
        ss[i] = s[i + b];
    }
}

bool myStrcat(char s1[], char s2[]) {
    int i = myStrlen(s1, 0);
    for (int j = 0; s2[j] != '\0'; j++) {
        if (i + j == MAX - 1) {
            return false;
        }
        s1[i + j] = s2[j];
    }
    s1[i + myStrlen(s2, 0)] = '\0';
    return true;
}

void ReverseWord(char w[], int s, int e) {
    while (s < e) {
        char t = w[s];
        w[s] = w[e];
        w[e] = t;
        ++s;
        --e;
    }
}

void StringReverse(char st[]) {
    int length = myStrlen(st, 0);
    int start = 0;

    for (int i = 0; i <= length; ++i) {
        if (st[i] == ' ' || st[i] == '\0') {
            ReverseWord(st, start, i - 1);
            start = i + 1;
        }
    }
}