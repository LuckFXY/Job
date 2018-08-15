//
// Created by Administrator on 2018/8/11.
//

#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include "share.h"
using namespace std;
void tetris(){
    int n,m;
    cin >>n>>m;
    vector<int> a(n,0);
    while(m--){
        int c;
        cin >>c;
        a[--c]++;
    }
    cout<< *min_element(a.begin(), a.end())<<endl;
}