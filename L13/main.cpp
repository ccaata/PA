#include <iostream>
#include <vector>
#include <climits>
#include <stdexcept>

using namespace std;

const int INF = INT_MAX;

void afiseazaDrum(int u, int v, const vector<vector<int>>& P) {
    if (P[u][v] == -1) {
        cout << "Nu există drum de la " << u << " la " << v << endl;
        return;
    }

    vector<int> drum;
    int current = v;
    while (current != u) {
        drum.push_back(current);
        current = P[u][current];
    }
    drum.push_back(u);

    cout << "Drum de la " << u << " la " << v << ": ";
    for (int i = drum.size() - 1; i >= 0; --i) {
        cout << drum[i] << (i > 0 ? " -> " : "\n");
    }
}

void floydWarshall(int n, vector<vector<int>>& L, vector<vector<int>>& P) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && L[i][j] != INF)
                P[i][j] = i;
            else
                P[i][j] = -1;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int temp;
                if (L[i][k] == INF || L[k][j] == INF)
                    temp = INF;
                else
                    temp = L[i][k] + L[k][j];

                if (temp < L[i][j]) {
                    L[i][j] = temp;
                    P[i][j] = P[k][j];
                }

                if (i == j && L[i][j] < 0) {
                    throw runtime_error("(di)graful are circuite negative");
                }
            }
        }
    }
}

int main() {
    int n = 4;
    vector<vector<int>> L = {
        {0,     3,     INF,   7},
        {8,     0,     2,     INF},
        {5,     INF,   0,     1},
        {2,     INF,   INF,   0}
    };

    vector<vector<int>> P(n, vector<int>(n, -1));

    try {
        floydWarshall(n, L, P);

        cout << "Distante minime:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (L[i][j] == INF)
                    cout << "INF ";
                else
                    cout << L[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nDrumuri minime intre toate perechile:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j)
                    afiseazaDrum(i, j, P);
            }
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}