#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void sortareTopologicaBFS(int n, const vector<vector<int>>& adj) {
    vector<int> inDegree(n, 0);   
    queue<int> C;             
    vector<int> L;           

    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    for (int u = 0; u < n; ++u) {
        if (inDegree[u] == 0) {
            C.push(u);
        }
    }

    for (int k = 0; k < n; ++k) {
        if (C.empty()) {
            cout << "Graful contine cicluri\n";
            return;
        }

        int u = C.front(); C.pop();
        L.push_back(u);

        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                C.push(v);
            }
        }
    }

    cout << "Sortarea topologica: ";
    for (int v : L) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    int n = 6;
    vector<vector<int>> adj(n);

    adj[5] = {0, 2};
    adj[4] = {0, 1};
    adj[2] = {3};
    adj[3] = {1};

    sortareTopologicaBFS(n, adj);

    return 0;
}
