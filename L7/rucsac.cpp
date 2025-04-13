#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> Pair;

// Funcția interclGrafice pentru interclasarea graficelor
vector<Pair> interclGrafice(const vector<Pair>& Si, const vector<Pair>& Ti) {
    vector<Pair> Si_plus_1;
    size_t j = 0, k = 0;
    int L = 1;

    while (j < Si.size() && k < Ti.size()) {
        if (L == 1) {
            if (Si[j].first < Ti[k].first) {
                Si_plus_1.push_back(Si[j++]);
            } else if (Si[j].first == Ti[k].first) {
                if (Si[j].second >= Ti[k].second) {
                    Si_plus_1.push_back(Si[j++]);
                    k++;
                } else {
                    Si_plus_1.push_back(Ti[k++]);
                    j++;
                    L = 2;
                }
            } else {
                if (Ti[k].second > Si[j].second) {
                    Si_plus_1.push_back(Ti[k++]);
                    L = 2;
                } else {
                    j++;
                }
            }
        } else {
            if (Si[j].first < Ti[k].first) {
                if (Si[j].second > Ti[k].second) {
                    Si_plus_1.push_back(Si[j++]);
                    L = 1;
                } else {
                    k++;
                }
            } else if (Si[j].first == Ti[k].first) {
                if (Si[j].second >= Ti[k].second) {
                    Si_plus_1.push_back(Si[j++]);
                    k++;
                    L = 1;
                } else {
                    Si_plus_1.push_back(Ti[k++]);
                    j++;
                }
            } else {
                Si_plus_1.push_back(Ti[k++]);
            }
        }
    }

    while (j < Si.size()) {
        Si_plus_1.push_back(Si[j++]);
    }

    while (k < Ti.size()) {
        Si_plus_1.push_back(Ti[k++]);
    }

    return Si_plus_1;
}

// Funcția rucsac
void rucsac(int M, int n, const vector<int>& w, const vector<int>& p, vector<int>& x) {
    vector<vector<Pair>> S(n + 1);
    S[0].push_back({0, 0});

    for (int i = 1; i <= n; ++i) {
        vector<Pair> Ti;
        for (const auto& pair : S[i - 1]) {
            Ti.push_back({pair.first + w[i - 1], pair.second + p[i - 1]});
        }
        S[i] = interclGrafice(S[i - 1], Ti);
    }

    Pair optimal = {0, 0};
    for (const auto& pair : S[n]) {
        if (pair.first <= M && pair.second > optimal.second) {
            optimal = pair;
        }
    }

    int Xj = optimal.first;
    int Yj = optimal.second;

    for (int i = n - 1; i >= 0; --i) {
        auto it = find(S[i].begin(), S[i].end(), make_pair(Xj, Yj));
        if (it != S[i].end()) {
            x[i] = 0;
        } else {
            x[i] = 1;
            Xj -= w[i];
            Yj -= p[i];
        }
    }
}