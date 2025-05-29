#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>

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

int main() {
    cout<<"\033[32m"; 
    cout<<"==========================================================================================\n";
    cout<<"\033[31m"<<" Backpack problem Interclasare grafice\n"<<"\033[0m";
    int M = 15;
    vector<int> w = {2, 5, 8, 3, 7};
    vector<int> p = {10, 20, 30, 40, 50};
    int n = w.size();
    vector<int> x(n);
    cout << "Greutatea maxima a rucsacului: " << M << "\n";
    cout << "Greutatile obiectelor: ";
    for (int i = 0; i < n; ++i) {
        cout << w[i] << " ";
    }
    cout << "\nProfiturile obiectelor: ";
    for (int i = 0; i < n; ++i) {
        cout << p[i] << " ";
    }
    cout << "\nNumarul de obiecte: " << n << "\n";
// START TIMER
   auto start = std::chrono::high_resolution_clock::now();
    rucsac(M, n, w, p, x);
 // STOP TIMER
    auto end = std::chrono::high_resolution_clock::now();    
    auto duration = (end - start);    
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Microsecond (as int)    
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration); // Milliseconds (as int)    
    const float ms_fractional = static_cast<float>(us.count()) / 1000;         // Milliseconds (as float)    
   //Afisare timp de executie
    cout<<"\033[32m";
    cout<<"==========================================================================================\n";
    cout <<"\033[31m"<< "Timpul de executie al algoritmului este: " << ms_fractional << " ms\n";
    cout<<"\033[0m";

    cout << "Solutia optima este: \n";
    for (int i = 0; i < n; ++i) {
        cout << "Obiectul " << i + 1 << ": " << (x[i] ? "Ales" : "Neales") << "\n";
    }
cout<<"\033[32m"; 
    cout<<"==========================================================================================\n"<<"\033[0m";
    cout << "Greutatea totala: ";
    int totalWeight = 0;
    for (int i = 0; i < n; ++i) {
        if (x[i]) {
            totalWeight += w[i];
        }
    }
    cout << totalWeight << "\n";
    cout << "Profitul total: ";
    int totalProfit = 0;
    for (int i = 0; i < n; ++i) {
        if (x[i]) {
            totalProfit += p[i];
        }
    }
    cout << totalProfit << "\n";
    cout<<"\033[32m";
    cout<<"==========================================================================================\n"<<"\033[0m";

    return 0;
}