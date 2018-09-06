//
// Created by Administrator on 2018/9/6.
//

#include<iostream>
#include<string>
using namespace std;
void Reverse(string::iterator start, string::iterator end){
    int length = (end - start + 1) >> 1;
    int cnt = 0;
    char ch;
    while(cnt < length){
        ch = *start;
        *start = *end;
        *end = ch;
        start ++;
        end --;
        cnt++;
    }
}
string& Reverse(string &s){
    if(s.empty()) return s;
    string::iterator left = s.begin();
    string::iterator right = s.begin();
    string::iterator end = s.end();
    while(right != end){
        if(*left == ' '){
            left++;
            right++;
        }
        else if(right == end || *right == ' '){
            Reverse(left, right-1);
            left = right;
        }
        else
            right++;
    }
    Reverse(s.begin(), s.end()-1);
    return s;
}
//int main(){
//    string s="I am a student.";
//    Reverse(s);
//    cout<<s<<endl;
//    return 0;
//}
