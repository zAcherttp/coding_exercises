#include <iostream>
#include <string.h>
#include <string>
using namespace std;
int main()
{
    string s;
    char f[100];
    char c;
    getline(cin, s);

    // trim đầu cuối trên dưới
    s.erase(s.find_last_not_of(" \n\r\t") + 1);

    // viết thường hết
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }

    // viết hoa kí tự kề dấu cách
    for (int i = 0; i < s.length(); i++)
    {
        if (i == 0)
        {
            s[i] = toupper(s[i]);
        }
        else if (s[i - 1] == ' ')
        {
            s[i] = toupper(s[i]);
        }
    }

    // xoá khoảng cách thừa ở giữa
    int i = 0, index = 0, check = 0;
    while (s[i])
    {
        c = s[i];
        if (isspace(c) && check == 0)
        {
            f[index++] = s[i];
            check = 1;
        }
        else if (isalnum(c))
        {
            f[index++] = s[i];
            check = 0;
        }
        i++;
    }
    cout << f;
    return 0;
}
