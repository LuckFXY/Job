//
// Created by Administrator on 2018/8/12.
//
#include "share.h"
#include <set>
using namespace std;
typedef pair<int,int> PAIR;
void test_input(vector<vector<int>>& matrix){
    string str_arr[]={
            "0,0,0,0,0,0,0,0,0,0",
            "0,0,0,1,1,0,1,0,0,0",
            "0,1,0,0,0,0,0,1,0,1",
            "1,0,0,0,0,0,0,0,1,1",
            "0,0,0,1,1,1,0,0,0,1",
            "0,0,0,0,0,0,1,0,1,1",
            "0,1,1,0,0,0,0,0,0,0",
            "0,0,0,1,0,1,0,0,0,0",
            "0,0,1,0,0,1,0,0,0,0",
            "0,1,0,0,0,0,0,0,0,0"
    };
    str2matrix(str_arr, matrix);
}
void fans_group() {
    int m=10, n=10;
    //char tmp;
    //cin>>m>>tmp>>n;
    vector<vector<int>> matrix(m, vector<int>(n,0));
    set<long> close;
    vector<PAIR> stack;
//    for(int i=0; i<m; i++){
//        for(int j=0; j<n-1; j++){
//            cin>>matrix[i][j]>>tmp;
//        }
//        cin>>matrix[i][n-1];
//    }
    test_input(matrix);
    int p=0, q=0;
    long key;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            key = i*m+j;
            if(close.find(key) != close.end() or matrix[i][j] == 0)
                continue;
            p += 1;
            stack.clear();
            PAIR t = PAIR(i,j);
            stack.emplace_back(t);
            int cnt=0;
            while(!stack.empty()){
                PAIR cur = *(stack.end()-1);
                stack.pop_back();
                key = cur.first*m + cur.second;
                if(close.find(key) == close.end()){
                    close.insert(key);
                    cnt += 1;
                    for(int a=cur.first-1;a<cur.first+2;a++){
                        if(a<0 or a>=n) continue;
                        for(int b=cur.second-1; b< cur.second+2; b++){
                            key = a*m+b;
                            if(b>=0 && b<m && close.find(key) == close.end()){
                                if(matrix[a][b] == 1) {
                                    stack.emplace_back(PAIR(a, b));
                                }
                            }
                        }
                    }
                }
            }
            q = cnt > q ? cnt: q;
        }
    }
    cout<<p<<','<<q<<endl;

}

