//
// Created by Administrator on 2018/8/25.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;
inline string num2str(unsigned num){
    string s;
    char tmp;
    unsigned n, i=0;
    while(num){
        int tmp = num % 10;
        s.push_back(tmp + 48);
        num = num / 10;
    }
    n = s.size();
    for(int i=0;i<n/2;i++){
        tmp = s[i];
        s[i] = s[n-1-i];
        s[n-1-i] = tmp;
    }
    return s;
}
int comp(const string &a, const string &b){
    int ret = 0;
    int i=0, j=0;
    if(a != b){
        while(i<a.size() && j < b.size()){
            if(a[i] > b[j]){
                ret = 1;
                break;
            }
            else if(a[i] < b[j]){
                ret = -1;
                break;
            }
            i += 1;
            j += 1;
        }
        if(a[i-1] == b[j-1]){
            if(a.size() > b.size()) ret = 1;
            else ret = -1;
        }
    }
    return -ret;
}
void vprint(const vector<string>& vec){
    for(auto it = vec.begin(); it!=vec.end(); it++){
        cout<<(*it)<<' ';
    }
    cout<<endl;
}
void quicksort(vector<string> &nums, int start, int end, int(*comp)(const string&, const string&)){
    string tmp, pivot = nums[start];
    int left = start, right = end;
    if(start < end) {
        while (left < right) {
            while (right > left && comp(nums[right], pivot)>0 ) right -= 1;
            while (left < right && comp(nums[left], pivot)<=0 ) left += 1;
            if (left != right) {
                tmp = nums[right];
                nums[right] = nums[left];
                nums[left] = tmp;
            }
            cout<<pivot<<' ';
            vprint(nums);
        }
        nums[start] = nums[left];
        nums[left] = pivot;
        quicksort(nums, start, left - 1, comp);
        quicksort(nums, left + 1, end, comp);
    }

}
#include <algorithm>
//int main(){
//
//    int _test[] = {3,30,34,5,9,10,2};
//    vector<int> test(_test, _test+7);
//    int n = test.size();
//    vector<string> snum(n,string());
//    for(int i=0; i<test.size(); i++){
//        snum[i] = num2str(test[i]);
//    }
//    quicksort(snum, 0, snum.size()-1, comp);
//    string ret;
//    for(int i=0; i<snum.size(); i++){
//        ret += snum[i];
//    }
//    cout<<ret<<endl;
//    return 0;
//}
