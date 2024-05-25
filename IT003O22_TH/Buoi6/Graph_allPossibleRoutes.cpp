#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int vertice, edge;
    cin >> vertice >> edge;

    vector<vector<char>> graph(vertice, vector<char>(vertice, '-'));

    for (int v = 0; v < vertice; v++) {
        graph[v][v] = to_string(v)[0];
    }

    for (int e = 0; e < edge; e++) {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1][v2] = 'O';
        graph[v2][v1] = 'O';
    }

    queue<int> nodeQueue;
    nodeQueue.push(0);
    vector<bool> visited(vertice, false);
    vector<int> routes;

    while (!nodeQueue.empty()) {
        int currentNode = nodeQueue.front();
        visited[currentNode] = true;
        nodeQueue.pop();

        for (int neighbor = 0; neighbor < vertice; neighbor++) {
            if (graph[currentNode][neighbor] == 'O' && !visited[neighbor]) {
                nodeQueue.push(neighbor);
                visited[neighbor] = true;
                routes.push_back(neighbor);
            }
        }
    }

    for(int v = 1; v < vertice; v++) {
        if(find(routes.begin(), routes.begin() + routes.size(), v) != routes.end()) {
            cout << "CO\n";
        } else {
            cout << "KHONG\n";
        }
    }

    return 0;
}
