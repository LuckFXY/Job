//
// Created by fxy on 18-8-22.
//
/*
 * 链接：https://www.nowcoder.com/questionTerminal/fe298c55694f4ed39e256170ff2c205f
来源：牛客网

有这样一道智力题：“某商店规定：三个空汽水瓶可以换一瓶汽水。小张手上有十个空汽水瓶，她最多可以换多少瓶汽水喝？”答案是5瓶，
 方法如下：先用9个空瓶子换3瓶汽水，喝掉3瓶满的，喝完以后4个空瓶子，用3个再换一瓶，喝掉这瓶满的，这时候剩2个空瓶子。
 然后你让老板先借给你一瓶汽水，喝掉这瓶满的，喝完以后用3个空瓶子换一瓶满的还给老板。
 如果小张手上有n个空汽水瓶，最多可以换多少瓶汽水喝？
 */
#include <iostream>
using namespace std;
int function_1(){
    int m, reserve, cnt;

    while(cin >>m){
        cnt =0;
        while(m>2){
            reserve = m%3;
            m = m / 3;
            cnt += m;
            if(m){
                m += reserve;
            }
        }
        if(m==2){
            cnt += 1;
        }
        cout<<cnt<<endl;
    }
}
int function_2(){
    /*
     * 1 0
     * 2 1
     * 3 1
     * 4 2
     * 5 2
     * 6 3
     * 6瓶喝3瓶,兑一瓶,共4瓶. 问题从6简化为4
     * 4瓶喝3瓶,兑一瓶,共2瓶,问题简化2
     * 2瓶借一瓶,兑一瓶,喝完结束
     * f[n] = f[n-2]+1 , f[0]=0,  f[1] =1
     */
    int m,a,b,c;
    while(cin >>m){
        if(m<=1)
            cout<<0<<endl;
        else if(m==2)
            cout<<1<<endl;
        else{
            a=0, b=1;
            while(--m>=2){
                c = a + 1;
                a=b, b=c;
            }

            cout<<c<<endl;
        }

    }
}
