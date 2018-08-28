#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void num2arr(vector<int>& arr, int num){
    int n=arr.size();
    for(int i=0; i<arr.size(); i++){
        arr[i] = num & 1;
        num = num >> 1;
    }
}
string show(vector<int> nums, vector<int> flags){
    string s;
    for(int i=0; i<nums.size(); i++) {
        if(flags[i]==1)
            s+= nums[i]+48;
    }
    return s;
}

int main() {
    int t1[]={0,1,2,3,4,5,6,7,8,9};
    int t2[]={0,1,1,1,1,1,1,1,1,0};
    vector<int>  nums(t1, t1+10);
    vector<int> flags(t2, t2+10);
    //input

    //
    vector<int> zero_idx;
    vector<int> zero_flags;

    for(int i=0; i<flags.size(); i++){
        if(flags[i]==0){
            zero_idx.emplace_back(i);
        }
    }
    int max_num = (1 << zero_idx.size() );
    zero_flags.resize(zero_idx.size());
    vector<string> ret;
    string s;
    for(int i=0; i<max_num; i++){
        num2arr(zero_flags, i);
        for(int j=0; j<zero_idx.size(); j++){
            flags[zero_idx[j]] = zero_flags[j];
        }
        s = show(nums, flags);
        ret.emplace_back(s);
    }
    sort(ret.begin(), ret.end());
    for(int i=0; i<ret.size(); i++){
        cout<<ret[i]<<endl;
    }
    return 0;
}
