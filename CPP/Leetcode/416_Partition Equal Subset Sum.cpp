//
// Created by Administrator on 2018/8/26.
//
#include<iostream>
#include <vector>
using namespace std;
bool canPartition(vector<int>& nums) {
    long tmp, sum=0;
    for(int num: nums){
        sum += num;
    }
    if(sum ^ 1 == 1) return false;
    sum /=2;

    vector<bool> dp(sum+1);
    dp[0]=true;
    for(int num: nums){
        cout<<num<<endl;
        //dp[num] = true;
        for(int i=sum; i>=0; i-- ){
            if(dp[i]){
                tmp = i + num;
                if(tmp == sum)
                    return true;
                else if(tmp < sum)
                    dp[tmp] = true;

            }

        }
    }
    return false;
}

//int main(){
//    int temp[] = {1,5,11,1};
//    vector<int> nums(temp, temp+ sizeof(temp)/sizeof(int));
//    cout<<canPartition(nums)<<endl;
//    return 0;
//}