//
// Created by Administrator on 2018/8/14.
//
#include "share.h"
#include <iostream>
inline int nzero(int num){
    int cnt=0;
    int f=5;
    while(f <= num){
        cnt += num / f;
        f *= 5;
    }
    return cnt;
}
/*
 * 不懂呀
 */
int preimageSizeFZF_fast(int K) {
    /*
     *  b 包含 5的次幂后缀0的个数。
     */
    if(K == 0)
        return 5;

    int b[13] = {1};
    for(int i=1; i<13; i++){
        b[i] = b[i-1] * 5 + 1;
    }
    int idx =0 ;
    while(idx < 13 && b[idx] <= K) idx += 1;
    idx -= 1;
    while(K > 0){
        if(K != b[idx] * 5){
            K -= (K/b[idx] * b[idx]);
            idx -= 1;
        }
        else
            return 0;
    }
    return 5;
}
/*
 * 1000000000 会出错。
 */
int preimageSizeFZF(int K) {
    for (double l = 0, r = 5*(K+1); l < r;) {
        double m = l + (r - l) / 2, c = m;
        for (int i = 5; m / i > 0; i *= 5)
            c += m / i; // the m-th is c
        if (c < K)
            l = m + 1;
        else if (c > K)
            r = m;
        else
            return 5;
    }
    return 0;
}
void preimageSizeFZF_test(){
    long num[]={6, 10, 15, 26, 1000000000};
    for(int i=0; i<5; i++){
        std::cout<<num[i]<<' '<<preimageSizeFZF(num[i])<<std::endl;

    }
}
