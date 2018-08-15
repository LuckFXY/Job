//
// Created by Administrator on 2018/8/11.
//

#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
#include "share.h"
int tower(){

    int n=3,k=2;
    cin>>n>>k;

    vector<int> tower(n,0);
    for(int i=0; i<n; i++)
        cin >> tower[i];

    vector<vector<int>> output(0, vector<int>(2,0));
    int i=0;
    for(i=0; i<k; i++){
        auto max_t = max_element(tower.begin(), tower.end());
        auto min_t = min_element(tower.begin(), tower.end());
        if(max_t == min_t) break;
        vector<int> tmp(2,0);
        tmp[0] = max_t - tower.begin() + 1;
        tmp[1] = min_t - tower.begin() + 1;
        output.emplace_back(tmp);
        (*max_t)--;
        (*min_t)++;
    }
    i = i < k ? i : k;
    auto max_t = max_element(tower.begin(), tower.end());
    auto min_t = min_element(tower.begin(), tower.end());
    int score = *max_t - *min_t;
    cout<<score<<' '<<i+1<<endl;
    for(auto it = output.begin(); it!=output.end(); it++){
        cout<<(*it)[0]<<' '<<(*it)[1]<<endl;
    }
}