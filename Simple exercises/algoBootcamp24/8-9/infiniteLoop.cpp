#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  if ((b - a) % 2 == 1 && a < b || a > b)
    cout << "TRUE";
  else
    cout << "FALSE";
  return 0;
}