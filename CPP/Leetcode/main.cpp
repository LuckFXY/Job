#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int binarySearch(const vector<int> &nums, const int k){
    int first=0, last=nums.size();
    int length = nums.size();
    int half, mid;
    while(length>0){
        half = length >> 1;
        mid = first + half;
        if(nums[mid] <  k){
            first = mid+1;
            length = length - first;
        }
        else{
            length = half;
        }
    }
    return first;
}
int binarySearch2(vector<int> &data, int k) {
    int i = 0, j = data.size();
    int mid;
    while(i<j){
        mid = (i+j)>>1;

        if(data[mid] < k)
            i = mid+1;
        else if(data[mid] == k)
            j = mid;
        else
            j = mid-1;
    }
    return j;
}

int myLowerBound(vector<int> &data, int k) {
    int start = 0;
    int last = data.size();
    while (start < last) {
        int mid = (start + last) / 2;
        if (data[mid] >= k) {
            last = mid;
        } else {
            start = mid + 1;
        }
    }
    return start;
}
int count(int n){
    int cnt=0;
    int mask = 1;
    for(int i=0; i<32; i++){
        if(n & mask)
            cnt += 1;
        mask = mask << 1;
    }
    return cnt;
}

int main(){
    int a, b,c;
    int n;
    int k;
    cin >> k;
    bool flag;
    while(--n >=0) {
        cin >> a >> b >> c;
        if (b <= k && k <= c) {
            cout << a << endl;
            flag = true;
        }
    }
    if(!flag)
        cout<<"null"<<endl;
}
int main(){

    int tmp[] = {1,3,5,5,5,9,11,13,15,17};
//    vector<int> nums(tmp, tmp+sizeof(tmp)/sizeof(int));
//    int k, ret;
//    for(int k=-2; k<20; k++){
//        ret = myLowerBound(nums, k);
//        auto ans = lower_bound(nums.begin(), nums.end(), k);
//        printf("k = %d ret = %d nums[ret]=%d ans = %d\n",k,ret,nums[ret],ans-nums.begin());
//
//    }
    cout<<count(15)<<endl;

}