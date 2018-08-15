//
// Created by Administrator on 2018/8/12.
//
#include "share.h"
#include<algorithm>
#include<sstream>

void test_input(vector<PAIR>& intervals){
    string s[] ={
      "0,1;2,9;10,16;20,30",
      "6,10;30,40;44,50;70,80"
    };
    stringstream stream;
    for(int i=0; i<2; i++){
        stream.clear();
        stream.str(s[i]);
        int a,b;
        char c;
        while(stream>>a>>c>>b){
            intervals.emplace_back(PAIR(a,b));
            if(stream.peek()==';')
                stream.ignore();
        }
    }
//    for(auto it=intervals.begin();it!=intervals.end();it++)
//        cout<<(*it)<<endl;
}
typedef vector<PAIR>::iterator iter;
ostream& operator << (ostream& out, const PAIR& src){
    out<<src.first<<','<<src.second;
}
void merge_overlap() {
    vector <PAIR> intervals;
    test_input(intervals);

    sort(intervals.begin(), intervals.end(), less_pair);

    for(auto it=intervals.begin();it!=intervals.end();it++)
        cout<<(*it)<<endl;

    PAIR tmp = PAIR(-1,-1);
    PAIR* last = &tmp;
    cout<<"----------"<<endl;
    vector<iter> output;
    for(auto it=intervals.begin();it!=intervals.end();it++){
        if( (*it).first > (*last).second){
            output.emplace_back(it);
            last = &(*it);
        }
        else if((*it).second > (*last).second)){
            (*last).second = (*it).second;
        }
    }
    for(auto it = output.begin(); it!=output.end(); it++){
        cout<<intervals[(*it) - intervals.begin()]<<';';
    }
    cout<<endl;
}