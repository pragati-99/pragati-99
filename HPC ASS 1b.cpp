#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node) {
    stack<int> s;
    s.push(node);

    while (!s.empty()) {
        int curr_node = s.top();
        s.pop();

        if (!visited[curr_node]) {
            visited[curr_node] = true;

            // Print the visited node
            #pragma omp critical
            cout << curr_node << " ";

            // Push adjacent nodes to the stack (sequentially to avoid race)
            for (int i = 0; i < graph[curr_node].size(); i++) {
                int adj_node = graph[curr_node][i];

                // It's possible another thread marks it visited just before this, so we recheck
                if (!visited[adj_node]) {
                    s.push(adj_node);
                }
            }
        }
    }
}

int main() {
    int n, m, start_node;

    cout << "Enter No of Nodes, Edges, and Start Node: ";
    cin >> n >> m >> start_node;

    cout << "Enter Pairs of Edges:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // For undirected graph
    }

    // Initialize visited[] array
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    cout << "\nDFS Traversal: ";
    dfs(start_node);
    cout << endl;

    return 0;
}
//OUTPUT
//Enter No of Nodes, Edges, and Start Node: 5 4 0
//Enter Pairs of Edges:
//0 1
//1 2
//2 3
//3 4

//DFS Traversal: 0 1 2 3 4
