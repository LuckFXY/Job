//
// Created by Administrator on 2018/8/25.
//
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include<iterator>
using namespace std;
char temp[]="10\n"
        "0\n"
        "5 3 0\n"
        "8 4 0\n"
        "9 0\n"
        "9 0\n"
        "3 0\n"
        "0\n"
        "7 9 0\n"
        "0\n"
        "9 7 0";
#include <sstream>
stringstream ss(temp);

int find(vector<int> &leads, int x){
    if(leads[x] != x)
        leads[x] = find(leads, leads[x]);
    return leads[x];
}
int test_union_set2() {
    int n, a;
    ss >> n;
    map<int, set<int>> data;
    vector<int> leads(n,0);
    for(int i=0; i<n; i++){leads[i]=i;}

    for (int i = 1; i <= n; i++) {
        set<int> newone;
        while (ss >> a) {
            if (a == 0) break;
                newone.insert(a);
        }
        data[i] = newone;
    }
    int groups = n;
    for(int i=1; i<=n; i++){
        for(int j=i+1; j<n; j++){
            if(data[i].count(j) != 0){
                int lead1 = find(leads, i);
                int lead2 = find(leads, j);
                if(lead1 != lead2){
                    leads[lead1] = lead2;
                    groups--;
                }
            }
        }
    }
    cout<<groups<<endl;
    return 0;
}