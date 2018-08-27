//
// Created by Administrator on 2018/8/26.
//
#include <iostream>
#include<vector>
using namespace std;


int valid(const vector<int>& nums, const int target, int m){
    int sum=0;
    for(int num : nums){
        sum += num;
        if(sum > target){
            sum = num;
            m -=1;
            if(m<1)
                return -1;
        }
    }
    return 1;
}

int splitArray(vector<int>& nums, int m) {
    int total=0, max_one=0;

    for(int i=0;i<nums.size(); i++){
        total += nums[i];
        max_one = nums[i] > max_one ? nums[i] : max_one;
    }
    int left = max_one, right = total;
    int mid = (left + right) >>1;
    int v;
    while(left < right) {
        mid = (left + right) >> 1;
        v = valid(nums, mid, m);
        if(v>0)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
//int main(){
//    int temp[] = {7,6,5,4,3,2,1};
//    vector<int> nums(temp, temp+sizeof(temp)/sizeof(int));
//    cout<<splitArray(nums,2)<<endl;
//    return 0;
//}
