#include <iostream>
#include <vector>

//int main() {
//    int t, n;
//    bool flag = false;
//    cin >> t;
//    while(--t >= 0){
//        cin >> n;
//        vector<string> data(n);
//        flag = false;
//        for(int i=0; i<n; i++){
//            cin >> data[i];
//        }
//        for(int i=0; i<n; i++){
//            for(int j=i+1; j<n; j++){
//                string s = data[j] + data[j];
//                if(s.find(data[i]) != -1){
//                    flag = true;
//                    break;
//                }
//                string tmp = data[i];
//                reverse(tmp.begin(), tmp.end());
//                if(s.find(tmp) != -1){
//                    flag = true;
//                    break;
//                }
//            }
//            if(flag)
//                break;
//        }
//        if(flag)
//            cout<<"Yeah"<<endl;
//        else
//            cout<<"Sad"<<endl;
//    }
//    return 0;
//}
//#include "share.h"
//int main(){
//    test_union_set2();
//}
