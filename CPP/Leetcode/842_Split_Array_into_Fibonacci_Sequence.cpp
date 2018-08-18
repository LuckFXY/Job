//
// Created by Administrator on 2018/8/14.
//
#include "share.h"
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
inline int ndigit(unsigned long num){
    int cnt=0;
    while(num){
        cnt += 1;
        num /= 10;
    }
    return cnt>0?cnt:1;
}
inline void vprint(vector<unsigned long> arr){
    for(auto it = arr.begin(); it != arr.end(); it++)
        cout<<(*it)<<' ';
    cout<<endl;
}
bool fibonacci_sequence(string s);
void fibonacci_sequence_test(){
    string s[] = {
            "3611537383985343591834441270352104793375145479938855071433500231900737525076071514982402115895535257195564161509167334647108949738176284385285234123461518508746752631120827113919550237703163294909",
            "0000",
            "123456579",
            "81321345589144233",
            "11235813",
            "112358130",
            "0123",
            "1101111"
    };
    for(int i=0; i<8; i++){
		cout << "s=" << s[i].c_str() << endl;
        fibonacci_sequence(s[i]);
    }
}
const unsigned long MAX_INT = (1<<31)-1;
bool fibonacci_sequence(string s){

    unsigned long a,b,c=0,sum=0;
    unsigned idx=0, clen;
    vector<unsigned long> ret;
    bool pass = false;
    for(unsigned alen = 1; alen <= s.size()/2; alen++){
        pass = false;
        ret.clear();

        sscanf(s.substr(0,alen).c_str(),"%ld",&a);
        if(s.substr(0,alen)[0] == '0' && a!=0)
            continue;
        idx = alen;
        ret.emplace_back(a);

        for(unsigned blen=1; blen < s.size()/2; blen++) {
            if(idx + blen > s.size())
                break;
            idx = alen;
            sscanf(s.substr(idx, blen).c_str(), "%ld", &b);
            ret.emplace_back(b);
            idx += blen;
            c = 0;
            while (idx < s.size()) {
                sum = a + b;
                clen = ndigit(sum);
                sscanf(s.substr(idx, clen).c_str(), "%ld", &c);
                if (c != sum || sum > MAX_INT) {
                    ret.clear();
                    ret.emplace_back(a);
                    break;
                }
                pass = true;
                ret.emplace_back(c);
                a = b, b = c;
                idx += clen;
            }
            if (idx == s.size() && pass){
                alen=s.size()/2;
                break;
            }
        }

    }
    if(idx == s.size() && pass){
        vprint(ret);
        return true;
    }
    else
        return false;
}