#include <iostream>
#include <string>
#include <sstream>
#include <climits> 

using namespace std;

int partition(int arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quick(int arr[], int start, int end)
{
    if (start >= end) return;
    int p = partition(arr, start, end);
    quick(arr, start, p - 1);
    quick(arr, p + 1, end);
}

pair<int, int> option(string opt)
{
    stringstream ss(opt);
    string temp;
    int type, key, i = 0;

    while(ss >> temp)
    {
        if(i%3 != 0)
        {
            if(i%3 == 1) type = stoi(temp);
            if(i%3 == 2) key = stoi(temp);
        }
    }

    return make_pair(type, key);
}

void find(int arr[], pair<int, int> opt);

int main()
{
    int N, Q;
    cin >> N;
    int data[N];

    for(int i = 0; i < N; i++)
    {
        cin >> data[i];
    }

    quick(data, 0, N - 1);

    string query;
    for(int i = 0; i < Q; i++)
    {
        getline(cin, query);
        cin.ignore();
        find(data, option);
    }
}