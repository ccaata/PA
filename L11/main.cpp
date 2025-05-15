#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graf{
    int n;
    vector<int> np; //numar predecesori
    vector<vector<int>> a;
};


vector<int> SortareTopologica (Graf D){
    queue<int> C;
    vector<int> sorted; // vectorul cu nodurile sortate

    int i;
    for (i = 0; i < D.n; ++i){
        if (D.np[i] == 0)
            C.push(i);
    }

    for (i = 0; i < D.n; ++i){
        if (C.empty() == 1){
            cout << "Graful contine cicluri\n";
        }

        int u = C.front();
        C.pop();
        sorted.push_back(u);

        //cautam vecinii
        int j;
        for (j = 0; j < D.a[u].size(); j++){
            int v = D.a[u][j];
            D.np[v]--;
            if (D.np[v] == 0)
                C.push(v);
        }
    }
    return sorted;
}



int main(){

    Graf D;
    D.n = 6;
    D.a = {
        {1, 3},
        {2},
        {3, 4},
        {4},
        {},
        {}
    };
    D.np = {0, 1, 1, 2, 2, 0};

    vector <int> sorted;
    sorted = SortareTopologica(D);

    for (int i = 0; i < sorted.size(); ++i){
        cout << char ('A' + sorted[i]) << ' ';
    }
}