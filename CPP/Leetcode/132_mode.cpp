//
// Created by Administrator on 2018/8/26.
//
#include <queue>
#include <iostream>
using namespace std;

template <typename T>
ostream & operator<<(ostream& out, const vector<T> &vec){
    for(auto it = vec.begin(); it!=vec.end(); it++){
        out<<(*it)<<' ';
    }
    out<<'\b';
    return out;
}


struct mygreater{
    bool operator () (const int& __x, const int& __y) const{
        return __x > __y;
    }
};

class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if(nums.size()<3) return false;
        priority_queue<int, vector<int>,mygreater> s2;
        int c = 0x80000000;
        int cur, n = nums.size();

        for(int i=n-1; i>=0; i--){
            cur = nums[i];
            if(s2.empty() || cur < s2.top()){
                s2.push(cur);
            }
            else{
                while(!s2.empty() && s2.top() <= cur){
                    if(s2.top() != cur && s2.top() > c)
                        c = s2.top();
                    s2.pop();
                }
                s2.push(cur);
            }
            if(cur < c)
                return true;
        }
        return false;
    }
};

//int main(){
//    Solution s = Solution();
//    int a[] = {-2,1,2,-2,1,2};
//    vector<int> nums(a, a+sizeof(a)/sizeof(int));
//    cout<<s.find132pattern(nums)<<endl;
//}