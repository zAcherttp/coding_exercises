#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  int m = max(a, b);
  int s = a + b;
  if (m == 7 && 12 <= s && s <= 13 || m == 6 && 6 <= s && s <= 10) {
    cout << 1;
  } else {
    cout << 0;
  }
}