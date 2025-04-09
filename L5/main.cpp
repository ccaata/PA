#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
    Node(int i) : info(i), left(nullptr), right(nullptr) {}
};

void printTreeHelper(Node* node, const string& prefix = "", bool isLeft = false) {
    if(node == nullptr) return;

    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    if(node->left == nullptr && node->right == nullptr) {
        cout << "[" << node->info << "]"; 
    } else {
        cout << node->info;                
    }
    cout << endl;

    printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), true);
    printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), false);
}

void printTree(Node* root) {
    cout << "Structura arborelui:" << endl;
    printTreeHelper(root);
    cout << endl;
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->info > b->info; 
    }
};
//Lab 6 Paradigma Greedy  Problema rucsacului var cont 
void greedy_backpack(int w[], float p[], int n, int M, float x[]) {
    float max_profit = 0; 
    
    int C_ocupat = 0; 
    float prof_weight[n];
    for (int i = 0; i < n; i++) {
        prof_weight[i] = p[i] / w[i];
    }
    // order sort: vector cu indexuri sortate în funcție de prof_weight în ordine descrescătoare
    vector<int> order_sort(n);
    for (int i = 0; i < n; ++i) {
        order_sort[i] = i;
    }
    sort(order_sort.begin(), order_sort.end(), [&prof_weight](int a, int b) {
        return prof_weight[a] > prof_weight[b];
    });

    for (int i = 0; i < n; ++i) {
        x[i] = 0;
        while (C_ocupat < M && x[i] == 0) {
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
}
int main() {
    // vector<int> valori = {4, 7, 10, 15, 20, 27};
    // sort(valori.begin(), valori.end());
    
    // priority_queue<Node*, vector<Node*>, CompareNode> heap;
    
    // for (int val : valori) {
    //     heap.push(new Node(val));
    // }
    
    // int lep = 0;
    // Node* root = nullptr;
    
    // while (heap.size() > 1) {
    //     Node* t1 = heap.top();
    //     heap.pop();
    //     Node* t2 = heap.top();
    //     heap.pop();
        
    //     int suma = t1->info + t2->info;
    //     lep += suma;
        
    //     Node* parent = new Node(suma);
    //     parent->left = t1;
    //     parent->right = t2;
        
    //     heap.push(parent);
    //     root = parent; 
    // }
    
    // cout << "LEP: " << lep << endl; 
    
    // if (!heap.empty()) {
    //     root = heap.top();
    //     printTree(root); 
    //     deleteTree(root); 
    // }
    cout<<"\033[32m"; 
    cout<<"==========================================================================================\n";
    cout<<"\033[31m"<<"Greedy backpack problem\n"<<"\033[0m";
    int w[] = {10,40,50,30,20,60}; 
    float p[] = {0.3,0.8,1,0.7,0.5,1.1}; 
    int n = 6;              
    int M = 70;              
    float x[n];             
    
    greedy_backpack(w, p, n, M, x);
    
    cout << "Obiectele selectate : ";
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    return 0;
}