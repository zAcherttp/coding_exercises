#include <iostream>

using namespace std;

int main()
{
    int temperature;
    cout << "What is the outdoor temperature?";
    cin >> temperature;
    cout << "What is your plan today?" << endl;

    if (temperature >= 33)
        cout << "Good day for swimming";
    else if (24 <= temperature && temperature < 33)
        cout << "Good day for golfing";
    else if (10 <= temperature && temperature < 24)
        cout << "Good day to play tennis";
    else if (temperature < 10)
        cout << "Go to bed";

    return 0;
}
