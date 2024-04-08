#include <iostream>

using namespace std;

class element
{
public:
    int value;
    int l_pos;
    int h_pos;

    element(int value = 0)
    {
        l_pos = -1;
        h_pos = -1;
    }

    friend istream &operator>>(istream &is, element &e)
    {
        is >> e.value;
        return is;
    }
};

int main()
{
    int N, Q;
    cin >> N;
    element arr[N];

    for(int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
}