#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


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

int lowerbound(){

    int tmp[] = {1,3,5,5,5,9,11,13,15,17};
    vector<int> data(tmp, tmp+sizeof(tmp)/sizeof(int));
    cout<<myLowerBound(data, 5)<<endl;

}