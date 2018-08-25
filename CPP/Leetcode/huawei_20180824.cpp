//
// Created by fxy on 18-8-22.
//

#include <iostream>
using namespace std;
int test1(){
    int n;
    float val;
    float a, b, ret;
    while(cin >> n >> val){
        a = n * val;
        if(n>=3)
            a *= 0.7;
        if(a >= 50){
            a -= 10;
        }

        b = n * val;
        if(b >= 10)
            b -= 2;
        b += 6;
        if(b >= 105)
            b -= 6;
        cout<<a <<' '<<b<<endl;
        ret = a-b;
        if(ret == 0)
            printf("0");
        else if(ret > 0)
            printf("2");
        else
            printf("1");
    }
    return 0 ;
}
#include <vector>
#include <string>

int check(string s, int start, int end){
    int n=0;
    vector<char> stack;
    for(int i=start; i<end; i++){
        if(s[i] == '(')
            stack.emplace_back('(');
        else if(s[i] == ')'){

            char left = '0';
            if(!stack.empty())
                left = stack.back();
            if(left == '('){
                stack.pop_back();
                n += 1;
            }
            else
                break;
        }
        else
            break;
    }
    return n*2;
}
int test2(){
    string s = "(()()())(())(())";
    while(cin >> s){
        int max = 0;
        vector<int> a(0, s.size());
        int start=0, last = s.size();
        while(start < last ){
            int n = check(s,start,s.size());
            start = start + 1;

            max = n > max ? n : max;
        }
        cout<<max<<endl;
    }
    return 0;
}
int main(){
    string s = "ABABCABCDABCDEABCDEF";
    vector<int> next(s.size()+1, 0);
    int i=1, k=0;
    int max_idx = 0;
    for(i = 1 ; i< s.size(); i++) {
        k=0;
        next.clear();
        while (i < s.size()) {
            if (s[i] == s[k]) {
                i += 1;
                k += 1;
                next[i] = k;
                max_idx = next[i] > next[max_idx] ? i : max_idx;
            } else if (k == 0) {
                i += 1;
            } else
                k = next[k];
        }
        for (int i = 0; i < next.size(); i++) {
            cout << next[i] << ' ';
        }
        cout << endl;

        int length = next[max_idx];

        cout << s.substr(max_idx - next[max_idx], length) << ' ' << length << endl;
    }
    return 0;
}