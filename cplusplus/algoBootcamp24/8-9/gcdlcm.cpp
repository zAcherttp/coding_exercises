#include <iostream>
using namespace std;

long GCD(long a, long b) {
  if (!b)
    return a;
  return GCD(b, a % b);
}

long LCM(long a, long b) { return a / GCD(a, b) * b; }

int main() {
  long a, b;
  cin >> a >> b;
  cout << GCD(a, b) << " " << LCM(a, b);
  return 0;
}