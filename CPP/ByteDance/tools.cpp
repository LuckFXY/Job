//
// Created by Administrator on 2018/8/12.
//

#include "share.h"
#include <sstream>



bool less_pair ( PAIR& src,  PAIR& dst) {
    return src.first <= dst.first;
}
template <typename T>
void mprint(const vector<vector<T>>& matrix){
    for(auto it = matrix.begin(); it!=matrix.end(); it++){
        for(auto jt = (*it).begin(); jt != (*it).end(); jt++)
            cout<<(*jt)<<' ';
        cout<<endl;
    }
}

template <typename T>
ostream & operator<<(ostream& out, const vector<T> &vec){
    for(auto it = vec.begin(); it!=vec.end(); it++){
        out<<(*it)<<' ';
    }
    out<<'\b';
    return out;
}

void str2matrix(string str_arr[], vector<vector<int>>& matrix){

    int m=10, n =10;
    int a, j=0;
    stringstream ss;
    for(int i=0; i<m; i++){
        ss.clear();
        ss.str(str_arr[i]);
        j=0;
        while(ss>>a){
            matrix[i][j]=a;
            j += 1;
            if(ss.peek() == ',')
                ss.ignore();
        }
    }
    mprint(matrix);
}