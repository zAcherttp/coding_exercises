#include <iostream>
using namespace std;

int GCD(int a, int b) {
  if (!b)
    return a;
  return GCD(b, a % b);
}

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  int s = 0;
  while ((double)a / b != (double)c / d) {
    a += 1;
    b += 1;
    int d = GCD(a, b);
    a /= d;
    b /= d;
    s++;
    if (s > 1000) {
      cout << 0;
      return 0;
    }
  }
  cout << s;
  return 0;
}