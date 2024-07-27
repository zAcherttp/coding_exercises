#include <bits/stdc++.h>

using namespace std;

int main() {

    int arraySize;
    cin >> arraySize;

    int array[arraySize];
    for (int i = 0; i < arraySize; i++) {
        cin >> array[i];
    }

    for (int i = 1; i < arraySize; i += 2) {
        array[i] = array[i] * pow(-1, i);
    }

    vector<int> minNeg;
    vector<int> minPos;

    int posSum = 0;
    for (int i = 0; i < arraySize; i++) {
        if (array[i] >= 0) {
            posSum += array[i];
            minPos.push_back(array[i]);
            // cout << array[i] << " ";
        }
    }
    // cout << "= " << posSum << endl;

    int negSum = 0;
    for (int i = 0; i < arraySize; i++) {
        if (array[i] < 0) {
            negSum += array[i];
            minNeg.push_back(array[i]);
            // cout << array[i] << " ";
        }
    }
    // cout << "= " << negSum << endl;

    int minN = INT_MAX, minP = INT_MAX;
    if (!minNeg.empty()) {
        minN = *min_element(minNeg.begin(), minNeg.end());
    }
    if (!minPos.empty()) {
        minP = *min_element(minPos.begin(), minPos.end());
    }

    // cout << "minN = " << minN << endl;
    // cout << "minP = " << minP << endl;

    int firstSum, maxSum;
    firstSum = negSum + posSum;
    maxSum = firstSum - 2 * minN - 2 * minP;
    if (maxSum < firstSum)
        maxSum = firstSum;
    // cout << "tong dau tien = " << firstSum << endl;
    cout /*<< "tong lon nhat = "*/ << maxSum;

    /*Print the array.
    for (int i = 0; i < arraySize; i++) {
        cout << array[i] << " ";
    }
    cout << endl;*/

    return 0;
}