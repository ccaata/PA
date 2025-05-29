#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <memory>
#include <exception>

// Node structure
class Node {
public:
    int id;
    double cost;
    
    Node(int id, double cost) : id(id), cost(cost) {}
    
    bool operator<(const Node& other) const {
        return cost > other.cost; // Min-heap
    }
};

class Perspico {
private:
    std::vector<std::vector<int>> adjacencyList; // Adjacency list representation
    std::vector<double> costs; // Costs for each node
    
public:
    Perspico(int n) : adjacencyList(n), costs(n, 0) {}
    
    // Add edge to the graph
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
    }
    
    // Set cost for a node
    void setCost(int node, double cost) {
        costs[node] = cost;
    }
    
    // Calculate estimated cost for a node
    double calculateEstimatedCost(int node) {
        // Calculate the cost as the sum of path cost from root to node
        // plus the heuristic estimate to goal
        double pathCost = costs[node];
        double heuristic = calculateHeuristic(node);
        return pathCost + heuristic;
    }
    
    // Calculate heuristic estimate to goal
    double calculateHeuristic(int node) {
        // Simple heuristic: minimum cost among all children
        if (adjacencyList[node].empty()) {
            return 0; // Leaf node, no additional cost
        }
        
        double minCost = std::numeric_limits<double>::max();
        for (int child : adjacencyList[node]) {
            minCost = std::min(minCost, costs[child]);
        }
        return minCost;
    }
    
    // Check if node is on the frontier
    bool isOnFrontier(int node) {
        // A node is on the frontier if it has no children
        // or if all its children have been processed
        return adjacencyList[node].empty();
    }
    
    // Get viable children of a node
    std::vector<int> getViableChildren(int node) {
        // Return all children that haven't been processed yet
        return adjacencyList[node];
    }
    
    // Main perspico algorithm
    bool perspico(int root) {
        // Priority queue to store nodes with their estimated costs
        std::priority_queue<Node> A;
        
        // Calculate initial cost for root
        double rootCost = calculateEstimatedCost(root);
        A.push(Node(root, rootCost));
        
        while (!A.empty()) {
            // Get node with minimum estimated cost
            Node current = A.top();
            A.pop();
            
            // Check if node is on the frontier
            if (isOnFrontier(current.id)) {
                std::cout << "Solution found at node: " << current.id << std::endl;
                return true;
            }
            
            // Get viable children
            std::vector<int> children = getViableChildren(current.id);
            
            // Calculate costs for children and add to queue
            for (int child : children) {
                double childCost = calculateEstimatedCost(child);
                A.push(Node(child, childCost));
            }
        }
        
        // If we reach here, no solution was found
        throw std::runtime_error("No solution exists.");
        return false;
    }
};

int main() {
    try {
        // Example usage
        Perspico perspico(5); // Create graph with 5 nodes
        
        // Add edges (example)
        perspico.addEdge(0, 1);
        perspico.addEdge(0, 2);
        perspico.addEdge(1, 3);
        perspico.addEdge(2, 4);
        
        // Set costs (example)
        perspico.setCost(0, 10);
        perspico.setCost(1, 5);
        perspico.setCost(2, 8);
        perspico.setCost(3, 3);
        perspico.setCost(4, 2);
        
        // Run perspico algorithm
        perspico.perspico(0);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}