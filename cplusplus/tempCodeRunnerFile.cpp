#include <iostream>

using namespace std;

int x = 0;

int main() {
    while(x< 1000000){
        x=-~x;
        cout << x << endl;
    }
}