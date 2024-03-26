#include <bits/stdc++.h>

using namespace std;

int findGCD(int arr[], int n)
{
    int result = arr[0];
    for (int i = 1; i < n; i++)
    {
        result = gcd(result, arr[i]);
    }
    return result;
}

int main()
{
    int size;
    cin >> size;

    int array[size];
    vector<int> vec;
    int t;
    for (int i = 0; i < size; i++)
    {
        cin >> t;
        array[i] = t;
        vec.push_back(t);
    }

    int gcd = 1;
    vector<int> temp;
    vector<int> to_remove;
    for (int i = 0; i < size; i++)
    {
        temp = vec;
        temp.erase(temp.begin() + i);
        int *a = &temp[0];
        int gcd_ = findGCD(a, size - 1);
        if (gcd_ > gcd)
        {
            gcd = gcd_;
            to_remove.push_back(i + 1);
        }
    }

    int min = to_remove[0];
    for (int i = 1; i < to_remove.size(); i++)
    {
        if (to_remove[i] < min)
            min = to_remove[i];
    }

    cout << min << " " << gcd;
}
