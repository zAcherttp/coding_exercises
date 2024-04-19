#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Data
{
public:
    int key;
    int count;
};

bool cmp(const Data &a, const Data &b)
{
    return a.count == b.count ? (a.key > b.key) : (a.count < b.count);
}

int partition(vector<Data> &arr, int low, int high)
{
    Data pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; ++j)
    {
        if (cmp(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void quick(vector<Data> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick(arr, low, pi - 1);
        quick(arr, pi + 1, high);
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> maHangs(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> maHangs[i];
    }

    vector<Data> banDem;
    for (int maHang : maHangs)
    {
        bool found = false;
        for (auto &pair : banDem)
        {
            if (pair.key == maHang)
            {
                pair.count++;
                found = true;
                break;
            }
        }
        if (!found)
        {
            banDem.push_back({maHang, 1});
        }
    }

    quick(banDem, 0, banDem.size() - 1);
    reverse(banDem.begin(), banDem.end());

    for (auto pair : banDem)
    {
        cout << pair.key << " " << pair.count << "\n";
    }

    return 0;
}