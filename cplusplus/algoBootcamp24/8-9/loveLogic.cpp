#include <iostream>

using namespace std;

int main() {
  bool tre_trung;
  bool xinh_dep;
  bool co_gau;
  bool giau_co;
  cin >> tre_trung >> xinh_dep >> co_gau >> giau_co;

  bool md1 = !tre_trung || xinh_dep;
  bool md2 = !xinh_dep || co_gau;
  bool md3 = xinh_dep || !co_gau || giau_co;
  if (md1 && md2 && md3)
    cout << 1;
  else
    cout << 0;
}