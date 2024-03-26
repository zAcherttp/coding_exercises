// #include <iostream>
// using namespace std;

// int main() {
//     string s1;
//     string s2;
//     getline(cin, s1);
//     getline(cin, s2);
//     if(s1 == s2) cout << 0;
//     if(s1 > s2) cout << 1;
//     if(s1 < s2) cout << -1;
// }
#include <iostream>
#include <string.h>
using namespace std;
#define MAX 255

int myStrcmp(char s1[], char s2[]);

int main()
{
    char s1[MAX], s2[MAX];
    cin.getline(s1, MAX);
    cin.getline(s2, MAX);
    int kt = myStrcmp(s1, s2);
    cout << kt << endl;
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

int myStrcmp(char s1[], char s2[])
{
    int l1 = myStrlen(s1);
    int l2 = myStrlen(s2);
    if (l1 < l2)
    {
        return -1;
    }
    else if (l1 > l2)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < l1; i++)
        {
            if (s1[i] == s2[i])
            {
                continue;
            }
            else
            {
                if (s1[i] > s2[i])
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}