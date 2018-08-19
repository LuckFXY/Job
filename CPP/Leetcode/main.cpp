
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
typedef pair<int, int> PAIR;
//int walk(map<int, PAIR> graph, int start){
//    int total = 0;
//    vector<int> stack;
//    stack.emplace_back(start);
//    int cur;
//    while(!stack.empty()){
//        cur = stack.back();
//        stack.pop_back();
//
//    }
//}
//int main() {
//
//    int n, m, a, b;
//    cin >> n >> m;
//    vector<int> weight(n);
//    for(int i=0; i<n ;i++){
//        cin>>weight[i];
//    }
//    map<int, map<int, int>> graph;
//
//    for(int i=0; i<m; i++){
//        cin>>a >> b;
//        graph.insert(a, map(b,weight[i]))
//    }
//
//    int nmax = 0, nweight = 0;
//
//    return 0;
//}

#include <cstdio>
#include <algorithm>
typedef pair<int, int> PAIR;
ostream& operator << (ostream& out, const PAIR src){
    out<<src.first<<' '<<src.second;
    return out;
}
bool comp(PAIR a, PAIR b){
    return a.first < b.first;
}
#include <string>
#include <algoritm>
int main(){
    vector<int> data;
    int a[] = {1,2,3,4,5,};
    data.assign(a, a+3);
    data.insert(data.begin(), 0);
    data.erase(data.begin());

    for(auto it = data.begin(); it != data.end(); it++){
        cout<< *it <<endl;
    }

    //sort(data.begin(), data.end());
//    for(auto it = data.begin(); it != data.end(); it++){
//        cout<< *it <<endl;
//    }
    return 0;
}