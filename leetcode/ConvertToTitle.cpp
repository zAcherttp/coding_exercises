
#include <bits/stdc++.h>
using namespace std;

// string convertToTitle(int columnNumber) {
//         string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", result = "";
//         vector<int> weight;
//         weight.push_back(0);
//         int maxWeight;
//         if (columnNumber < 27) {
//             return result + letter[columnNumber - 1];
//         }
//         for(int i = 1 ;i < columnNumber; i *= 26) {
//             weight.push_back(i);
//             maxWeight = i;
//         }

// for(int i = maxWeight; i >= 0; i--) {
//     for(int j = 26; j > 0; j--) {
//         if(columnNumber - j*weight[i] > 0) {
//             result += letter[j - 1];
//         }
//     }
// }
// return result;

//}

int main()
{
    int columnNumber;
    cin >> columnNumber;
    string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", result = "";
    vector<int> weight;
    // if (columnNumber < 27) {
    //     cout << result + letter[columnNumber - 1];
    // }
    weight.push_back(1);
    for (int i = 26; i < columnNumber; i *= 26)
    {
        weight.push_back(i);
    }
    int weightSize = weight.size();

    int count = 0;
    for (auto x : weight)
    {
        cout << x << " ";
        count++;
    }
    cout << endl;
    if (columnNumber % 26 != 0)
    {
        result += letter[columnNumber % 26];
        columnNumber -= columnNumber % 26;
    }
    cout << "columnNumber = " << columnNumber << endl;
    for (int i = count; i > 0; i--)
    {
        cout << "i = " << i << endl;
        for (int j = 26; j > 0; j--)
        {
            cout << "j = " << j << endl;
            if (columnNumber - j * weight[i - 1] >= 0)
            {
                cout << "passed!" << endl;
                columnNumber -= j * weight[i - 1];
                result += letter[25 - j];
            }
        }
    }
    cout << endl;

    cout << result;

    // cout << convertToTitle(num);
    return 0;
}