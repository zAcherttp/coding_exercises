#include <iostream>

using namespace std;

int gender(string g)
{
    if (g == "M" || g == "m")
        return 1;
    else if (g == "F" || g == "f")
        return 0;
    else
        return -1;
    return 0;
}

int age(int a)
{
    if (a < 21)
        return 34;
    else
        return 12;
}

int main()
{
    int a;
    string g;
    int genderType;
    int ageRange;
    int type;

    cin >> a >> g;
    genderType = gender(g);
    ageRange = age(a);

    if (genderType == 0)
    {
        if (ageRange == 34)
            type = 4;
        else if (ageRange == 12)
            type = 2;
        cout << type;
    }
    else if (genderType == 1)
    {
        if (ageRange == 34)
            type = 3;
        else if (ageRange == 12)
            type = 1;
        cout << type;
    }
    else
        cout << "I do not know why";
    return 0;
}