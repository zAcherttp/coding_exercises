#include <iostream>
using namespace std;

void merge(int a[], int const size_a, int b[],
           int const size_b, int c[]) {
    auto index_a = 0, index_b = 0;
    int index_merged = 0;

    while (index_a < size_a && index_b < size_b) {
        if (a[index_a] <= b[index_b]) {
            c[index_merged] = a[index_a];
            index_a++;
        } else {
            c[index_merged] = b[index_b];
            index_b++;
        }
        index_merged++;
    }

    while (index_a < size_a) {
        c[index_merged] = a[index_a];
        index_a++;
        index_merged++;
    }

    while (index_b < size_b) {
        c[index_merged] = b[index_b];
        index_b++;
        index_merged++;
    }

    delete[] a;
    delete[] b;
}

int main() {
    cin.tie(0);
    std::ios::sync_with_stdio(false);
    int n, m;
    int t;
    cin >> t;
    while (cin >> n >> m || t > 0) {
        t--;
        int *a = new int[n], *b = new int[m], *c = new int[n + m];
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < m; i++)
            cin >> b[i];

        merge(a, n, b, m, c);
        int nc = n + m;
        ;
        for (int i = 0; i < nc; i++) {
            cout << c[i] << " ";
        }
        delete c;
        cout << endl;
    }
}
