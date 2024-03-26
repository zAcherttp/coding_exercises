// #include <iostream>
// using namespace std;

// int main() {
//     string s1, s2, s3;
//     getline(cin, s1);
//     getline(cin, s2);

//     int l = s1.size() + s2.size();

//     if(l < 255) {
//         s3 = s1 + " " + s2;
//         cout << s3;
//     } else {
//         cout << "Khong noi duoc. Khong du bo nho.";
//     }

//     return 0;
// }

#include <iostream>
#include <string>
using namespace std;
#define MAX 255

int myStrlen(char s[]);
bool myStrcat(char s1[], char s2[]);

int main()
{
    char s1[MAX], s2[MAX];
    cin.getline(s1, MAX);
    cin.getline(s2, MAX);
    bool kt = myStrcat(s1, s2);

    if (kt)
    {
        cout << s1;
    }
    else
    {
        cout << "Khong noi duoc. Khong du bo nho.";
    }

    return 0;
}

int myStrlen(char s[])
{
    int length = 0;
    while (s[length] != '\0')
    {
        length++;
    }
    return length;
}

bool myStrcat(char s1[], char s2[])
{
    int i = myStrlen(s1);
    for (int j = 0; s2[j] != '\0'; j++)
    {
        if (i + j == MAX - 1)
        {
            return false;
        }
        s1[i + j] = s2[j];
    }
    s1[i + myStrlen(s2)] = '\0';
    return true;
}
