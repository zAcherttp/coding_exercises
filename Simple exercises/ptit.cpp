#include <iostream>
using namespace std;

bool kiemTraSoNguyenTo(int &n) {
  if (n < 2)
    return false;

  for (int i = 2; i * i <= n; i++) {

    if (n % i == 0)
      return false;
  }
  return true;
}

int main() {
  int a, b;
  cin >> a >> b;
  int n;
  for (int i = 1; i < b - a; i++) {
    n = a + i;

    if (kiemTraSoNguyenTo(n)) {
      cout << n << " ";
    }
  }
  return 0;
}