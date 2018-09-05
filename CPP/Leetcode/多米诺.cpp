//
// Created by Administrator on 2018/9/3.
//

#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

class pos{
public:
    int first;
    int second;
    pos(int a, int b){
        first = a;
        second = b;
    }
    friend bool operator < (pos& a, pos& b);
    friend bool operator < (pos& a, const pos& b);
    friend bool operator < (const pos& a,const pos& b);
};
bool operator < (pos& a, pos& b){
    return a.first < b.first;
}
bool operator < (pos& a, const pos& b){
    return a.first < b.first;
}
bool operator < (const pos& a,const pos& b){
    return a.first < b.first;
}
int main2(){
    int n, a, b;
    cin >>n;
    if(n<=0) return 0;
    vector<pos> data;
    map<int, int> order;
    for(int i=0; i<n; i++){
        cin >> a>> b;
        data.emplace_back(pos(a,b));
        order[a] = i;
    }
    sort(data.begin(), data.end());

    vector<int> record(n, 1);
    data.back().second=-1;
    for(int i=n-2; i>=0; i--){
        int cnt=1;
        int j = i+1;
        int last=-1;
        while(j<n){
            int tmp = data[j].first - data[i].first;
            int jump=1;
            if(data[i].second > tmp){
                if(data[j].second != -1){
                    jump = data[j].second+1;
                    cnt += record[j];
                }
                else{
                    cnt += 1;
                }
                last = j;
            }
            j += jump;
        }
        if(cnt==1)
            data[i].second = -1;
        else if(last != -1)
            data[i].second = last;
        record[i] = cnt;
    }
    vector<int> res(n,0);
    for(int i=0; i<n; i++){
        int p = data[i].first;
        int ord = order[p];
        res[ord] = record[i];
    }
    cout<<res[0];
    for(int i=1; i<n; i++)
        cout<<' '<<res[i];
    return 0;
}

