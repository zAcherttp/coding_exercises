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

    int connectedGraphCount = 0;
    vector<bool> visited(vertice, false);

    for (int v = 0; v < vertice; v++) {
        if (!visited[v]) {
            connectedGraphCount++;
            queue<int> nodeQueue;
            nodeQueue.push(v);
            visited[v] = true;

            while (!nodeQueue.empty()) {
                int currentNode = nodeQueue.front();
                nodeQueue.pop();

                for (int neighbor = 0; neighbor < vertice; neighbor++) {
                    if (graph[currentNode][neighbor] == 'O' && !visited[neighbor]) {
                        nodeQueue.push(neighbor);
                        visited[neighbor] = true;
                    }
                }
            }
        }
    }

    cout << connectedGraphCount;

    return 0;
}
