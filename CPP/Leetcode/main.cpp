#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ULL;
void num2arr(vector<int>& arr, ULL num){
    for(int i=0; i<64; i++){
        arr[i] = (num & 1) == 0 ? 0 : 1;
        num = num >> 1;
    }
}


int main() {
    ULL x = 0b100100;
    //  y = 0b0__0__
    ULL k = 5;
    ULL y = ~x;
    ULL mask = 1;
    vector<int> candidate(64, 0);
    num2arr(candidate, k);
    int idx =0;
    for(int i=0; i<64; i++){
        if((x & mask)==0){
            if(candidate[idx] == 0)
                x = x | mask;
            idx += 1;
        }
        mask = mask >> 1;
    }

}
