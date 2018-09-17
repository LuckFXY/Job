//
// Created by Administrator on 2018/9/17.
//

#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
    double key;
    int pos;
    node(double k, int p):key(k), pos(p){}
    friend bool operator < (const node& a, const node& b);
};
bool operator < (const node& a, const node& b){
    return a.key > b.key;
}
#define maxNum(a,b) ((a)>(b)?(a):(b))
int candy(priority_queue<node>& data) {
    unsigned n = data.size();
    vector<int> count(n, 0);
    n-=1;
    while(!data.empty()){
        const node &cur = data.top();
        int &num = count[cur.pos];
        if(cur.pos != 0)
            num = maxNum(num, count[cur.pos-1] + 1);
        if(cur.pos != n)
            num = maxNum(num, count[cur.pos+1] + 1);

        data.pop();
    }
    unsigned res=0;
    for(auto &it : count)
        res += it;
    return res;
}
#include<queue>
int main() {
    int res;

    int _numbers_size = 0;
    cin >> _numbers_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    //vector<double> _numbers;
    priority_queue<node, vector<node>> data;
    double _numbers_item;
    for(int _numbers_i=0; _numbers_i<_numbers_size; _numbers_i++) {
        cin >> _numbers_item;
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        //_numbers.push_back(_numbers_item);
        data.push(node(_numbers_item, _numbers_i));
    }

    res = candy(data);
    cout << res << endl;

    return 0;
    queue<int> a;
    a.fron
}


