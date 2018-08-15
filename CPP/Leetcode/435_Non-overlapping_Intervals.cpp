//
// Created by Administrator on 2018/8/13.
//
#include "share.h"
#include <sstream>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
}Interval;

bool compare(const Interval &src, const Interval &dst){
    return src.end > dst.end;
}
ostream& operator<<(ostream& out, const Interval& src){
    cout<<src.start<<' '<<src.end;
}
void test_input(vector<Interval>& intervals){
    string s ="[1,2], [2,3]";
    stringstream ss;
    ss.str(s);
    int a,b;
    char c;
    while(ss>>c>>a>>c>>b>>c){
        if(ss.peek() == ',' || ss.peek() == ' '){
            ss.ignore();
        }
        intervals.emplace_back(Interval(a,b));
    }
}
typedef vector<Interval>::iterator iter_type;
void deduplicate_overlapping(){
    vector<Interval> intervals;
    test_input(intervals);
    sort(intervals.begin(), intervals.end(), compare);
    vector<iter_type> iter_vec;
    //int big = intervals.front().end + 1;
    Interval* last = nullptr;
    for(auto it = intervals.begin(); it != intervals.end(); it++){
        if( last == nullptr || (*it).end <= (*last).start ){
            iter_vec.emplace_back(it);
            last = &(*it);
        }
        else if((*it).start > (*last).start){
            (*last).start =(*it).start;
        }
    }
//    for(auto it = iter_vec.begin(); it != iter_vec.end(); it++){
//        cout<<intervals[(*it) - intervals.begin()]<<endl;
//    }
    cout<<intervals.size() - iter_vec.size();
}
