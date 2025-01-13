#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Sắp xếp mảng theo thứ tự tăng dần.
    sort(a, a + n);

    // Tìm giá trị tuyệt đối lớn nhất trong mảng.
    int max_abs = *max_element(a, a + n);

    // Tổng lớn nhất có thể đạt được là tổng của các phần tử có dấu trái dấu và tổng của các phần tử có dấu phải dấu.
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            sum += a[i];
        } else {
            sum -= a[i];
        }
    }

    // Nếu tổng lớn nhất có thể đạt được là số nguyên âm, thì ta đổi chỗ hai số có giá trị tuyệt đối lớn nhất.
    if (sum < 0) {
        swap(a[0], a[n - 1]);
    }

    // In ra tổng lớn nhất.
    cout << sum << endl;

    return 0;
}