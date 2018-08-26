//
// Created by Administrator on 2018/8/24.
//
#include <iostream>
#include <vector>
using namespace std;
inline int max(int a, int b){
    return a>b?a:b;
}
ostream & operator<<(ostream& out, const vector<int> &vec){
    for(auto it = vec.begin(); it!=vec.end(); it++){
        out<<(*it)<<' ';
    }
    return out;
}
int maxValue(int n, int volume, vector<int> cost, vector<int> weight){
    if(n<=0 or n != cost.size() or n!= weight.size()){
        return 0;
    }
    vector<vector<int>> dp(n, vector<int>(volume+1, 0));
    int i,j;
    for(j = cost[0]; j <= volume; j++){
        dp[0][j] = weight[0];
    }
    cout<<dp[0]<<endl;
    for(i = 1; i < n; i++){
        for(j=0; j<cost[i]; j++)
            dp[i][j] = dp[i-1][j];
        for(j = cost[i]; j <= volume; j++){
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-cost[i]] + weight[i]);
        }
        cout<< dp[i] <<endl;
    }
}
int maxValue_ops_one(int n, int volume, vector<int> cost, vector<int> weight){
    if(n<=0 or n != cost.size() or n!= weight.size()){
        return 0;
    }
    vector<int> dp(volume+1, 0);
    int i,j;
    for(j = cost[0]; j <= volume; j++){
        dp[j] = weight[0];
    }
    cout<<dp<<endl;
    for(i = 1; i < n; i++){

        for(j = volume; j >= cost[i]; j--){
            dp[j] = max(dp[j], dp[j-cost[i]] + weight[i]);
        }
//        for(j=cost[i]-1; j>=0; j--)
//            dp[j] = dp[j];
        cout<< dp <<endl;
    }
}
int main(){
    int _cost[] = {2,3,3,4,6};
    int _weight[] = {1,2,5,9,4};
    int N = sizeof(_cost) / sizeof(int);
    vector<int> cost(_cost, _cost+N);
    vector<int> weight(_weight, _weight+N);
    maxValue_ops_one(N, 10, cost, weight);
    return 0;
}