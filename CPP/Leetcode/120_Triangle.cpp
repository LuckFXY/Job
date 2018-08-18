//
// Created by fxy on 18-8-18.
//
#include "share.h"
#include <iostream>
#include <vector>
using namespace std;

inline int min(int a, int b){
    return a<b?a:b;
}
int minimumTotal(vector<vector<int>>& triangle) {
    if(triangle.size() == 0){
        return 0;
    }
    int m  = triangle.size(), n = 1;

    vector<vector<int>> dp(m, vector<int>(1,0));
    dp[0][0] = triangle[0][0];

    int ret = triangle[0][0];
    for(int i = 1; i < m; i++){
        dp[i].reserve(i+1);
        dp[i][0] = dp[i-1][0] + triangle[i][0];
        ret = dp[i][0];
        for(int j = 1; j < i; j++){
            dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j];
            ret = min(ret, dp[i][j]);
        }

        dp[i][i] = dp[i-1][i-1] + triangle[i][i];
        ret = min(ret, dp[i][i]);
    }
    cout<<ret<<endl;
    return ret;
}

//[[-7],[-2,1],[-5,-5,9],[-4,-5,4,4],[-6,-6,2,-1,-5],[3,7,8,-3,7,-9],[-9,-1,-9,6,9,0,7],[-7,0,-6,-8,7,1,-4,9],[-3,2,-6,-9,-7,-6,-9,4,0],[-8,-6,-3,-9,-2,-6,7,-5,0,7],[-9,-1,-2,4,-2,4,4,-1,2,-5,5],[1,1,-6,1,-2,-4,4,-2,6,-6,0,6],[-3,-3,-6,-2,-6,-2,7,-9,-5,-7,-5,5,1]]
void test_triangle_120(){
    int input[13][13]={{-7},{-2,1},{-5,-5,9},{-4,-5,4,4},{-6,-6,2,-1,-5},{3,7,8,-3,7,-9},{-9,-1,-9,6,9,0,7},{-7,0,-6,-8,7,1,-4,9},{-3,2,-6,-9,-7,-6,-9,4,0},{-8,-6,-3,-9,-2,-6,7,-5,0,7},{-9,-1,-2,4,-2,4,4,-1,2,-5,5},{1,1,-6,1,-2,-4,4,-2,6,-6,0,6},{-3,-3,-6,-2,-6,-2,7,-9,-5,-7,-5,5,1}};
    int m=13, n=13;
    vector<vector<int>> vec(m, vector<int>(1,0));
    for(int i=0; i<m; i++){
        vec[i].reserve(i+1);
        for(int j=0; j<i+1; j++){
            vec[i][j] = input[i][j];
        }
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<i+1; j++){
            cout<<vec[i][j]<<' ';
        }
        cout<<endl;
    }
    minimumTotal(vec);
}