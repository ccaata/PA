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

int main() {
    vector<int> valori = {4, 7, 10, 15, 20, 27};
    sort(valori.begin(), valori.end());
    
    priority_queue<Node*, vector<Node*>, CompareNode> heap;
    
    for (int val : valori) {
        heap.push(new Node(val));
    }
    
    int lep = 0;
    Node* root = nullptr;
    
    while (heap.size() > 1) {
        Node* t1 = heap.top();
        heap.pop();
        Node* t2 = heap.top();
        heap.pop();
        
        int suma = t1->info + t2->info;
        lep += suma;
        
        Node* parent = new Node(suma);
        parent->left = t1;
        parent->right = t2;
        
        heap.push(parent);
        root = parent; 
    }
    
    cout << "LEP: " << lep << endl; 
    
    if (!heap.empty()) {
        root = heap.top();
        printTree(root); 
        deleteTree(root); 
    }
    
    return 0;
}