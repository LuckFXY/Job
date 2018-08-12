//
// Created by Administrator on 2018/8/12.
//

#include "share.h"
#include <sstream>



bool less_pair ( PAIR& src,  PAIR& dst) {
    return src.first <= dst.first;
}

void mprint(const vector<vector<int>>& matrix){
    for(auto it = matrix.begin(); it!=matrix.end(); it++){
        for(auto jt = (*it).begin(); jt != (*it).end(); jt++)
            cout<<(*jt)<<' ';
        cout<<endl;
    }
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