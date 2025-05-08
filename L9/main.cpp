#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
vector<int> w = {4, 7, 11, 14};
int m = 25;
vector<int> x(4);
 
int sum(vector<int> x){
    int s=0;
    for(int i:x){
        s=s+i;
    }
    return s;
}
 
void afisare(vector<int> x) {
    for (float val : x) {
        cout << val << " ";
    }
    cout << endl;
}
 
void subOpt(int s, int k, int r){
    x[k]=1;
    if(s+w[k]==m){
        for(int i=0;i<=k;i++)
            cout<<x[i]<<" ";
        cout<<endl;
        //s=0;
    }
    if (k + 1 < w.size() && s + w[k] + w[k+1] <= m) {
        subOpt(s + w[k], k + 1, r - w[k]);
    }
    if((s+r-w[k]>=m) && (s+w[k+1]<=m)){
        x[k]=0;
        subOpt(s, k+1, r-w[k]);
    }
}
 
int main() {
    int r=sum(w);
    subOpt(0, 0, r);
    return 0;
}