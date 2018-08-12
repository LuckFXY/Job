//
// Created by Administrator on 2018/8/11.
//

#include"share.h"

void apple(){
    int n=6,m=20;

    //cin>>n;
    int tmp[6] = {2,3,4,1,5,6};
    //vector<int> heap(n,0);
    vector<int> heap(tmp, tmp+6);
//    cin >>heap[0];
    for(int i=1; i<n; i++) {
//        cin >> heap[i];
        heap[i] += heap[i-1];
    }
//    cin >>m;
    int q;

    for(int i=0; i<21; i++){
        //cin >> q;
        q=i+1;
        cout<<"q="<<q<<endl;
        int left=0, right=n-1,mid;
        while(left < right){
            mid = (left+right)>>1;
            if(q == heap[mid])
                break;
            else if(q < heap[mid])
                right = mid - 1;
            else
                left = mid+1;
        }
        if (heap[mid] == q)
            cout<<mid<<endl;
        else if(heap[left] < q)
            cout<<left+1<<endl;
        else
            cout<<left<<endl;
    }
}