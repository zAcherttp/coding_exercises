#include <bits/stdc++.h> 
using namespace std; 

// Function to print an array 
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i = 0; i < size; i++) { 
		cout << arr[i] << " ";
	}
    cout << '\n';
} 

// Function for Selection sort 
void selectionSort(int arr[], int n) 
{ 
	int i, j, min_idx; 

	// One by one move boundary of 
	// unsorted subarray 
	for (i = 0; i < n - 1; i++) { 

		// Find the minimum element in 
		// unsorted array 
		min_idx = i; 
		for (j = i + 1; j < n; j++) { 
			if (arr[j] < arr[min_idx]) 
				min_idx = j; 
		}

		// Swap the found minimum element 
		// with the first element 
		if (min_idx != i) 
        {
			swap(arr[min_idx], arr[i]); 
        
            //print array after each swap
            printArray(arr, n);
        }
	} 
} 

// Driver program 
int main() 
{
    int size;
    cin >> size;
    int arr[size];

    for(int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

	selectionSort(arr, size); 

	return 0; 
} 

// This is code is contributed by rathbhupendra
