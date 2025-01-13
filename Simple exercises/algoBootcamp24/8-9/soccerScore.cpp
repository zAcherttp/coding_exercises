#include <iostream>

using namespace std;

int main() {
  int thang[6];
  int thua[6];
  int theVang[6];
  for (int i = 0; i < 6; i++) {
    cin >> thang[i] >> thua[i] >> theVang[i];
  }

  int mot[4] = {0};
  int hai[4] = {0};

  for (int i = 0; i < 3; i++) {
    int diff = thang[i] - thua[i];
    mot[0] += (diff >= 0) ? (diff == 0 ? 1 : 3) : 0;
    mot[1] += diff;
    mot[2] += thang[i];
    mot[3] += theVang[i];
  }

  for (int i = 3; i < 6; i++) {
    int diff = thang[i] - thua[i];
    hai[0] += (diff >= 0) ? (diff == 0 ? 1 : 3) : 0;
    hai[1] += diff;
    hai[2] += thang[i];
    hai[3] += theVang[i];
  }

  if (mot[0] < hai[0])
    cout << hai[0] << " " << hai[1] << " " << hai[2] << " " << hai[3];
  else if (mot[0] > hai[0])
    cout << mot[0] << " " << mot[1] << " " << mot[2] << " " << mot[3];
  else if (mot[1] < hai[1])
    cout << hai[0] << " " << hai[1] << " " << hai[2] << " " << hai[3];
  else if (mot[1] > hai[1])
    cout << mot[0] << " " << mot[1] << " " << mot[2] << " " << mot[3];
  else if (mot[2] < hai[2])
    cout << hai[0] << " " << hai[1] << " " << hai[2] << " " << hai[3];
  else if (mot[2] > hai[2])
    cout << mot[0] << " " << mot[1] << " " << mot[2] << " " << mot[3];
  else if (mot[3] < hai[3])
    cout << hai[0] << " " << hai[1] << " " << hai[2] << " " << hai[3];
  else if (mot[3] > hai[3])
    cout << mot[0] << " " << mot[1] << " " << mot[2] << " " << mot[3];
  else
    cout << mot[0] << " " << mot[1] << " " << mot[2] << " " << mot[3];
}
