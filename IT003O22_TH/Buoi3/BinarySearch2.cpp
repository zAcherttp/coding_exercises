#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

int partition(tuple<int, int, int> arr[], int low, int high)
{
    int pivot = get<0>(arr[high]);
    int i = (low - 1);
    for (int j = low; j <= high; j++)
    {
        if (get<0>(arr[j]) < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void quick(tuple<int, int, int> arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick(arr, low, pi - 1);
        quick(arr, pi + 1, high);
    }
}
int binarySearch(vector<tuple<int, int, int>> &arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (get<0>(arr[mid]) == target)
        {
            return mid;
        }
        else if (get<0>(arr[mid]) < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    tuple<int, int, int> triplet[N];

    for (int i = 0; i < N; i++)
    {
        cin >> get<0>(triplet[i]);
        get<1>(triplet[i]) = i + 1;
        get<2>(triplet[i]) = i + 1;
    }

    quick(triplet, 0, N);

    vector<tuple<int, int, int>> data;
    tuple<int, int, int> temp = triplet[0];

    data.push_back(temp);
    for (int i = 1; i < N; i++)
    {
        if (get<0>(triplet[i]) == get<0>(data.back()))
        {
            if (get<1>(triplet[i]) < get<1>(data.back()))
                get<1>(data.back()) = get<1>(triplet[i]);
            continue;
        }
        else
        {
            data.push_back(triplet[i]);
        }
    }

    // cout << '\n';
    // for (auto i : data)
    // {
    //     cout << get<2>(i) << " ";
    // }
    // cout << '\n';
    // for (auto i : data)
    // {
    //     cout << get<1>(i) << " ";
    // }
    // cout << '\n';
    // for (auto i : data)
    // {
    //     cout << get<0>(i) << " ";
    // }
    // cout << '\n';

    for (auto i : data) {}

    string query[Q];
    int option[Q];
    int key[Q];

    for (int i = 0; i < Q; i++)
    {
        cin.ignore();
        getline(cin, query[i]);
        stringstream ss(query[i]);
        string ignore;
        ss >> ignore >> option[i] >> key[i];
    }

    // for (int i = 0; i < Q; i++)
    // {
    //     int POS = binarySearch(data, key[i]);
    //     cout << "option: " << option[i] << '\n';
    //     cout << "key   : " << key[i] << '\n';
    //     cout << "data: " << get<0>(data[POS]) << " " << get<1>(data[POS]) << " " << get<2>(data[POS]) << '\n';
    // }

    for (int i = 0; i < Q; i++)
    {
        // cout << "finding " << key[i] << " with option " << option[i] << ", result: ";
        int pos = binarySearch(data, key[i]);

        if (pos != -1)
            switch (option[i])
            {
            case 1:
            {
                cout << get<1>(data[pos]) << '\n';
                break;
            }
            case 2:
            {
                cout << get<2>(data[pos]) << '\n';
                break;
            }
            }
        else
            cout << pos << '\n';
    }
    return 0;
}