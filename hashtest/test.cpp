#include <iostream>
using namespace std;

bool powerOfTwoOrNot(int n)
{
    return n > 0 && !(n & (n - 1));
}

int main()
{
    int n;
    cin >> n;
    cout << powerOfTwoOrNot(n);
    return 0;
}
