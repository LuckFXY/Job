//
// Created by Administrator on 2018/9/10.
//

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;
//#define FRE
inline bool read(vector<int> &arr){
    int a;
    char ch;

    while(scanf("%d,",&a) ==1){
        arr.emplace_back(a);
    }
    if(scanf("%d", &a)==1)
        arr.emplace_back(a);
    return arr.size() != 0;
}
void fun1(){
#ifdef FRE
    freopen("in.txt","r",stdin);
#endif
    string s;
    vector<int> a1, a2;
    vector<int> ret;
    while(read(a1)){
        read(a2);
        auto i = a1.begin(), j = a2.begin();
        while(i != a1.end() && j != a2.end()){
            if(*i <= *j){
                ret.emplace_back(*i);
                i++;
            }
            else{
                ret.emplace_back(*j);
                j++;
            }
        }
        for(auto &item : ret){
            printf("%d,",item);
        }
        printf("\b\n");
        ret.clear();
        a1.clear();
        a2.clear();
    }
}

//int main(){
//    test2();
//    return 0;
//}