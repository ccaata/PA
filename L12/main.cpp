#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

void dijkstra(int n, vector<vector<int>>& L, int i0, vector<int>& D, vector<int>& P) {
    vector<bool> S(n, false);

    for (int i = 0; i < n; i++) {
        P[i] = i0;
        D[i] = L[i0][i];
    }
    S[i0] = true;

    for (int count = 1; count < n; count++) {
        int k = -1, minDist = INF;
        for (int j = 0; j < n; j++) {
            if (!S[j] && D[j] < minDist) {
                minDist = D[j];
                k = j;
            }
        }

        if (k == -1) break; 

        S[k] = true;

        for (int j = 0; j < n; j++) {
            if (!S[j] && L[k][j] < INF) {
                if (D[j] > D[k] + L[k][j]) {
                    D[j] = D[k] + L[k][j];
                    P[j] = k;
                }
            }
        }
    }
}

int main() {
    int n = 5;
    int start = 0;

    vector<vector<int>> G = {
        {0,   10,  3,  INF, INF},
        {INF, 0,   1,  2,   INF},
        {INF, 4,   0,  8,   2},
        {INF, INF, INF, 0,   7},
        {INF, INF, INF, 9,   0}
    };

    vector<int> D(n, INF);
    vector<int> P(n, -1);

    dijkstra(n, G, start, D, P);

    cout << "Distante minime de la nodul " << start << ":\n";
    for (int i = 0; i < n; i++) {
        cout << " -> " << i << ": " << (D[i] == INF ? -1 : D[i]) << " (predecesor: " << P[i] << ")\n";
    }

    return 0;
}