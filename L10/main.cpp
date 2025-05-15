#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
 
using namespace std;
 
int DIM = 3;                  
const string GOAL = "ABCDEFGHL"; 
vector<vector<int>> adj = 
{
    {1, 3}, 
    {0, 2, 4},
    {1, 5},
    {0, 4, 6},
    {1, 3, 5, 7},
    {2, 4, 8},
    {3, 7},
    {4, 6, 8},
    {5, 7}
};
 
struct Node
{                     
    int level;    
    int cStar;        
    string config; 
    vector<string> path;
 
    bool operator>(const Node &other) const
    {
        return cStar > other.cStar;
    }
};