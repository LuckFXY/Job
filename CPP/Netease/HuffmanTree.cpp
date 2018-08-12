//
// Created by Administrator on 2018/8/11.
//

#include <iostream>
#include <string>
#include<vector>
#include <queue>
#include <map>
#define SHIFT 27
using namespace std;
void aprint(int* arr, int n){
    for(int i=0; i<n; i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}
void mprint(vector<vector<int>> m){
    int idx = 0;
    for(auto it=m.begin();it!=m.end();it++){
        cout<<idx<<' ';
        idx += 1;
        for(auto jt=(*it).begin();jt!=(*it).end();jt++){
            if(jt==(*it).begin() && *jt < 127)
                cout<<(char)*jt<<' ';
            else
                cout<<*jt<<' ';
        }
        cout<<endl;
    }
}
typedef pair<int, int> PAIR;
class ComparePair{
public:
    bool operator()(PAIR src, PAIR dst){
        return src.first < dst.first;
    }
};
void create_HuffmanTree(
        vector<vector<int>>& table,
        priority_queue<PAIR, vector<PAIR>, ComparePair>& pq){

    unsigned parent_idx = table.size();
    cout<<parent_idx<<endl;
    while(pq.size() > 1){
        PAIR a = pq.top();
        pq.pop();
        PAIR b = pq.top();
        pq.pop();
        vector<int> parent = vector<int>(4,0);
        int parent_weight = a.first + b.first;
        parent[1] = -1;
        parent[2] = a.second;
        parent[3] = b.second;
        table.emplace_back(parent);
        table[a.second][1] = parent_idx;
        table[b.second][1] = parent_idx;
        pq.push(PAIR(-parent_weight, parent_idx));
        parent_idx += 1;

    }
    mprint(table);
}
string create_HuffmanCode(
        vector<vector<int>>& table,
        const string& target){

}
string encode(string longUrl) {
    int frequency[100] = {0};
    unsigned i=0,j=0;
    string text;
    priority_queue<PAIR, vector<PAIR>, ComparePair> pq;
    for(j =0; j< longUrl.size(); j++){
        if(longUrl[j] == '/'){
            if(j-i>0)
                text += longUrl.substr(i,j-i);
            i=j+1;
        }
        else
            frequency[longUrl[j]-SHIFT] += 1;
    }
    if(i<j)
        text += longUrl.substr(i,j-i);

    cout<<text<<endl;

    vector<vector<int>> table(0, vector<int>(4,0));

    for(int i=0, j=0; i<100;i++){
        int weight = frequency[i];
        if(weight) {
            int ch = i + SHIFT;
            vector<int> tmp = vector<int>(4,0);
            tmp[0] = ch;
            tmp[1] = -1;
            table.emplace_back(tmp);
            pq.push(PAIR(-weight, j));
            j += 1;
        }
    }
    mprint(table);
    cout<<"--------------"<<endl;
    create_HuffmanTree(table, pq);
//
//    while(!pq.empty()){
//        PAIR cur = pq.top();
//        pq.pop();
//        cout<<cur.first<<' '<<char(table[cur.second][0])<<endl;
//    }
    return string();
}

// Decodes a shortened URL to its original URL.
string decode(string shortUrl) {
    string s;
    return s;
}
//int main(){
//    string s="777777755555224444";//"https://leetcode.com/problems/design-tinyurl";
//    encode(s);
//    return 0;
//}