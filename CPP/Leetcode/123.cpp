#include<iostream>
#include<vector>
#include<algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
struct node{
    int first;
    int second;
    node(int a, int b){
        first = a;
        second = b;
    }
    friend bool operator< (const node &a, const node &b);
};
using namespace std;
bool operator< (const node &a, const node &b){
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}
int main(){
    int n, a, b;
    vector<node> data;
    while(cin >> n) {
        if(n<=0) {
            cout<<0<<endl;
            continue;
        }
        int start=0x7fffffff;
        int end=0;
        data.clear();
        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            data.push_back(node(a,b));
            start = min(start, a);
            end = min(end, b);
        }

        sort(data.begin(), data.end());
        int mcnt = 0;

        for(auto it = data.begin(); it != data.end()-1; it++){
            int cnt = 1;

            mcnt = max(mcnt, cnt);
        }
        cout<<mcnt<<endl;
    }
    return 0;
}