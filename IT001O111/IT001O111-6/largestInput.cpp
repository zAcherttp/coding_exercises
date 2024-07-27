#include <iostream>
using namespace std;

int largest_input() {
    int input;
    cin >> input;

    if (input == 0) {
        return 0;
    }

    int largest = largest_input();

    return (input > largest) ? input : largest;
}

int main() {
    cout << largest_input();
}
