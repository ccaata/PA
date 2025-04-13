#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;

// Funcția interclGrafice pentru interclasarea graficelor
vector<P> interclGrafice(const vector<P>& S, const vector<P>& T) {
    vector<P> S_next;
    size_t j = 0, k = 0;
    int L = 1;

    while (j < S.size() && k < T.size()) {
        if (L == 1) {
            if (S[j].first < T[k].first) {
                S_next.push_back(S[j++]);
            } else if (S[j].first == T[k].first) {
                if (S[j].second >= T[k].second) {
                    S_next.push_back(S[j++]);
                    k++;
                } else {
                    S_next.push_back(T[k++]);
                    j++;
                    L = 2;
                }
            } else {
                if (T[k].second > S[j].second) {
                    S_next.push_back(T[k++]);
                    L = 2;
                } else {
                    j++;
                }
            }
        } else {
            if (S[j].first < T[k].first) {
                if (S[j].second > T[k].second) {
                    S_next.push_back(S[j++]);
                    L = 1;
                } else {
                    k++;
                }
            } else if (S[j].first == T[k].first) {
                if (S[j].second >= T[k].second) {
                    S_next.push_back(S[j++]);
                    k++;
                    L = 1;
                } else {
                    S_next.push_back(T[k++]);
                    j++;
                }
            } else {
                S_next.push_back(T[k++]);
            }
        }
    }

    while (j < S.size()) S_next.push_back(S[j++]);
    while (k < T.size()) S_next.push_back(T[k++]);

    return S_next;
}

// Funcția rucsac
void rucsac(int M, int n, const vector<int>& w, const vector<int>& p, vector<int>& x) {
    vector<vector<P>> S(n + 1);
    S[0] = {{0, 0}};

    for (int i = 1; i <= n; ++i) {
        vector<P> T;
        for (const auto& pair : S[i - 1]) {
            T.emplace_back(pair.first + w[i - 1], pair.second + p[i - 1]);
        }
        S[i] = interclGrafice(S[i - 1], T);
    }

    P best = {0, 0};
    for (const auto& pair : S[n]) {
        if (pair.first <= M && pair.second > best.second) {
            best = pair;
        }
    }

    int Xj = best.first, Yj = best.second;
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