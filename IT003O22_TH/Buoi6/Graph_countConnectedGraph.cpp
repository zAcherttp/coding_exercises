#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    int v, e;
    cin >> v, e;
    vector<vector<bool>> graph(v, vector<bool>(v, false));

    int v1, v2;
    for(int i = 0; i < e; i++) {
        cin >> v1 >> v2;
        graph[v1][v2] = true;
        graph[v2][v1] = true;
    }


    return 0;
}