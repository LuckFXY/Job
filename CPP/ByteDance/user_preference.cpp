//
// Created by Administrator on 2018/8/24.
//
#include "share.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int find_low(vector<int>& v,int target){
    int low=0;
    int high=v.size()-1;
    int mid;
    if(target<=v[low]) return -1;
    if(target>v[high]) return high;
    while(low<high){
        mid=(low+high+1)>>1;
        //cout<<low<<" "<<high<<"  "<<mid<<endl;
        if(target<=v[mid]){
            high=mid-1;
        }else{
            low=mid;
        }
    }
    return high;
}

int find_high(vector<int>& v,int target) {
    int low = 0;
    int high = v.size() - 1;
    int mid;
    if (target < v[low]) return -1;
    if (target >= v[high]) return high;
    while (low < high) {
        mid = (low + high + 1) >> 1;
        //cout<<low<<"  "<<high<<"  "<<mid<<endl;
        if (target == v[mid]) {
            return mid;
        } else if (target < v[mid]) {
            high = mid - 1;
        } else {
            low = mid;
        }
    }
    return high;
}
void test_find(){

    int n, t, l, r, k, sum;
    map<int, vector<int>> count;
    cin >> n;
    for(int i=1;i<=n ;i++){
        //i是用户编号，t是该用户的喜好
        cin >>t;
        if(count.find(t) == count.end()){
            vector<int> v;
            v.push_back(i);
            count[t] = v;
        }
        else{
            count[t].push_back(i);
        }
    }
    cin >> n;

    map<int, vector<int>>::iterator it;
    for(int i=0; i<n; i++){
        cin >> l >> r >> k;
        sum = 0;
        it = count.find(k);
        if(it != count.end()){
            vector<int> &v = count[k];
            int low = find_low(v, l);
            int high = find_high(v, r);
            sum=high-low;
        }
        cout<<sum<<endl;
    }
}