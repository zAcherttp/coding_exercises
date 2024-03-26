#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int N, Q;

bool search_binary(int data[], int query)
{
    int left = 0, right = N - 1;
    int mid = (int)(left + right) / 2;
    while (left <= right)
    {
        int mid = floor((left + right) / 2);

        if (data[mid] < query)
        {
            left = mid + 1;
        }
        else if (data[mid] > query)
        {
            right = mid - 1;
        }
        else
        {
            return true;
        }
    }

    return false;
}

int main()
{
    cin >> N >> Q;
    int data[N];
    int query[Q];

    for (int i = 0; i < N; i++)
    {
        cin >> data[i];
    }
    sort(data, data + N);

    for (int i = 0; i < Q; i++)
    {
        cin >> query[i];
    }

    for (int i = 0; i < Q; i++)
    {
        search_binary(data, query[i]) ? cout << "YES" << endl : cout << "NO" << endl;
    }
    return 0;
}