//
// Created by Administrator on 2018/9/6.
//

#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n, k;
    int tmp[] = {1,0,1,1,0,0,1,1,0,1,0,1};
    vector<int> bin(tmp, tmp+sizeof(tmp)/sizeof(int));
//    while(cin >> n >> k) {
//        bin.clear();
//        bin.resize(n);
//        for (int i = 0; i < n; i++) {
//            cin >> bin[i];
//        }
    {
        n = 10, k = 2;

        int ret = 0, len = 0;
        int zero;
        for (int i = 0; i < bin.size(); i++) {
            zero = 0;
            int j;
            for (j = i; j < bin.size(); j++) {
                if (bin[j] == 0 && zero < k) {
                    zero += 1;
                } else if (zero >= k)
                    break;
            }
            len = j - i + 1;
            ret = len > ret ? len : ret;
        }
        cout<<ret<<endl;
    }
    return 0;
}