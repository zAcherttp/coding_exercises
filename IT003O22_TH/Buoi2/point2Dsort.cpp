#include <algorithm>
#include <iostream>
using namespace std;

class Point2D {
public:
    int x;
    int y;

    bool operator<(const Point2D &p) {
        return x == p.x ? (y > p.y) : (x < p.x);
    }
};

int partition(Point2D arr[], int low, int high) {
    Point2D pivot = arr[high];

    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick(Point2D arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick(arr, low, pi - 1);
        quick(arr, pi + 1, high);
    }
}

int main() {
    int n;
    cin >> n;
    Point2D arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i].x >> arr[i].y;
    }
    quick(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << arr[i].x << ' ' << arr[i].y << '\n';
    }
}
