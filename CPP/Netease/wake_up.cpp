//
// Created by Administrator on 2018/8/11.
//
#include <iostream>
using namespace std;
int wake_up(){
    int n,k;
    cin >> n >> k;
    int* interest = new int[n];
    int* wake = new int[n];
    for(int i=0; i<n; i++){
        cin >> interest[i];
    }
    for(int i=0; i<n; i++){
        cin >> wake[i];
    }

    int total = 0;
    int backup = 0;
    for(int i=0; i<n; i++){
        if(wake[i] == 1){
            total += interest[i];
            interest[i] = 0;
        }
        else
            backup += interest[i];
    }

    if(n>k) {
        int ksum = 0;

        for(int j =0 ;j<k;j++) {
            ksum += interest[j];
        }
        int best = ksum;
        for(int j=k; j<n; j++){
            ksum -= interest[j-k];
            ksum += interest[j];
            if(ksum>best)
                best = ksum;
        }
        total += best;
    }
    else
        total += backup;
    cout<<total<<endl;
    return 0;
}