#include <iostream>
#include <algorithm>

using namespace std;

void printArray(int arr[], int size) 
{ 
	int i; 
	for (i = 0; i < size; i++) { 
		cout << arr[i] << " ";
	}
    cout << '\n';
} 

void bubbleSort(int arr[], int n)
{
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < n - i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                printArray(arr, n);
            }
        }
    }
}

int main() {
    int size;
    cin >> size;
    int arr[size];

    for(int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

	bubbleSort(arr, size); 

	return 0;
}
