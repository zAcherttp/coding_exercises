#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    vector<int> v, nguyento;
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        cin >> temp;
        v.push_back(temp);
    }

    if (n == 0)
    {
        goto end;
    }

    for (int i = 0; i < n; i++)
    {
        if (isPrime(v[i]))
        {
            nguyento.push_back(v[i]);
        }
        continue;
    }
    if (nguyento.size() > 0)
    {
        for (int i = 0; i < nguyento.size(); i++)
        {
            cout << nguyento[i] << " ";
        }
    }
    else
    {
        cout << 0;
    }
end:
    return 0;
}