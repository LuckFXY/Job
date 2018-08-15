//
// Created by Administrator on 2018/8/11.
//

#include <iostream>
#include <vector>

using namespace std;
#define max(x,y) ((x)>=(y)?(x):(y))
void mprint(vector<vector<int>> m){

    for (vector<vector<int>>::iterator it = m.begin(); it != m.end(); it++) {
        for (vector<int>::iterator jt = (*it).begin(); jt != (*it).end(); jt++) {
            cout << *jt << ' ';
        }
        cout << endl;
    }
}
int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
    int m=0, n =0;
    m=grid.size();
    if(m)
        n = grid[0].size();
    int* left = new int[m];
    int* top = new int[n];

    for(int i=0;i<n;i++) {
        top[i] = 0;
    }
    for(int i=0; i<m;i++){
        left[i] = 0;
        for(int j=0; j<n; j++){
            left[i] = max(left[i], grid[i][j]);
            top[j] = max(top[j], grid[i][j]);
        }
    }
    for(int i=0; i<m;i++){
        for(int j=0; j<n; j++){
            grid[i][j] = -max(-left[i], -top[j]);
        }
    }
    mprint(grid);

    delete[] top;
    delete[] left;
    return 0;
}

int skyline_medium(){
    int arr[]={3, 0, 8, 4, 2, 4, 5, 7, 9, 2, 6, 3, 0, 3, 1, 0};
    int m=4, n =4;
    vector<vector<int>> matrix(m, vector<int>(n));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            matrix[i][j] = arr[i*m+j];
        }
    }
    mprint(matrix);
    maxIncreaseKeepingSkyline(matrix);

    return 0;
}