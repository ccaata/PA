#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
using namespace std;
float greedy_backpack(int w[], float p[], int n, int M, float x[]) {
    float max_profit = 0; 
    
    int C_ocupat = 0; 
    float prof_weight[n];
    for (int i = 0; i < n; i++) {
        prof_weight[i] = p[i] / w[i];
    }
    //vector cu indexuri sortate în funcție de prof_weight în ordine descrescătoare
    vector<int> order_sort(n);
    for (int i = 0; i < n; ++i) {
        order_sort[i] = i;
    }
    sort(order_sort.begin(), order_sort.end(), [&prof_weight](int a, int b) {
        return prof_weight[a] > prof_weight[b];
    });
    for (int i = 0; i < n; ++i) 
        x[i] = 0;
    for (int i = 0; i < n; ++i) {
        if (C_ocupat >= M) break;
        while (C_ocupat < M && x[order_sort[i]] == 0) {
            if (C_ocupat + w[order_sort[i]] <= M) {
                x[order_sort[i]] = 1;
                C_ocupat += w[order_sort[i]];
                max_profit += p[order_sort[i]];
            } else {
                x[order_sort[i]] = float(M - C_ocupat) / w[order_sort[i]];
                C_ocupat = M;
                max_profit += x[order_sort[i]] * p[order_sort[i]];
                break; 
            }
        }
    }
    return max_profit;
}
int main(){
    cout<<"\033[32m"; 
    cout<<"==========================================================================================\n";
    cout<<"\033[31m"<<"Greedy backpack problem\n"<<"\033[0m";
    int w[] = {10,40,50,30,20,60}; 
    float p[] = {0.3,0.8,1,0.7,0.5,1.1}; 
    int n = 6;              
    int M = 70;              
    float x[n];             
    //Start the greedy backpack algorithm timer
    auto start = std::chrono::high_resolution_clock::now();
    float maxProfit = greedy_backpack(w, p, n, M, x);
    //Stop the greedy backpack algorithm timer
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = (end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Microsecond (as int)
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration); // Milliseconds (as int)
    const float ms_fractional = static_cast<float>(us.count()) / 1000; // Milliseconds (as float)
    cout <<"\033[31m"<< "Timpul de executie = " << us.count() << "µs (" << ms_fractional << "ms)" <<"\033[0m"<< endl;
    cout<<"\033[32m";
    cout<<"==========================================================================================\n";
    cout<<"\033[0m";
    //Display the results
    cout << "Greutatea maxima a rucsacului: " << M << endl;
    cout << "Greutatile obiectelor: ";
    for (int i = 0; i < n; ++i) {
        cout << w[i] << " ";
    }
    cout << "Obiectele selectate : ";
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    cout << "Profitul maxim: " << maxProfit << endl;
}