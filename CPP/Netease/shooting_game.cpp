//
// Created by Administrator on 2018/8/10.
//
#include "share.h"
#define cor(x,y) ((x*n)+y) //you must define variable n firstly
#define max(x,y) ((x)>=(y)?(x):(y))
int shooting_game() {
    int n ;
    cin >> n;

    int *x = new int[n];
    int *y = new int[n];
    int *dx = new int[n*n];
    int *dy = new int[n*n];
    for(int i=0; i < n; i++){
        cin >> x[i];
    }
    for(int i=0; i < n; i++){
        cin >> y[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dx[cor(i,j)] = x[i] - x[j];
            dy[cor(i,j)] = y[i] - y[j];
        }
    }
    int maxn = -1, cnt =0;
    for(int a=0; a < n; a++){
        for(int b=0; b<n ; b++){
            if(b==a) continue;
            for(int c=0; c<n; c++){
                if(c == a || c == b || dy[cor(a,b)] * dx[cor(a,c)] == dx[cor(a,b)] * dy[cor(a,c)]) continue;
                cnt = 0;
                for(int d=0; d<n; d++){
                    if(dy[cor(a,b)] * dx[cor(a,d)] == dx[cor(a,b)] * dy[cor(a,d)])
                        cnt += 1;
                    else if(dy[cor(a,b)] * dy[cor(c,d)] == -dx[cor(a,b)] * dx[cor(c,d)])
                        cnt += 1;
                }
                maxn = max(maxn, cnt);
            }
        }
    }
    maxn = (maxn == -1) ? n : maxn;
    cout<<maxn<<endl;
    delete[] x;
    delete[] y;
    delete[] dx;
    delete[] dy;
    return 0;
}
