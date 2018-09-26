#include<iostream>
#include<vector>
using namespace std;
int min_score=0x7fffffff;
int score;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int getSum(vector<int>& help, int start, int end){
    int s = start !=0 ? help[start] : 0;
    return help[end] - s;
}
#include<
void minSum(vector<int>& data, vector<int>& help, int m, int mi, int start, int end){
    if(mi < m){
        if(mi==0){
            min_score = min(min_score, score);
            score = 0;
        }
        int n = data.size();
        for(int i=start; i<=end; i++){
            int tmp = getSum(help, start, end);
            score = max(score, tmp);
            minSum(data, help, m, mi+1, i+1, n-(m-mi)-i);
        }
    }
}

int main(){
    int n,m;
    vector<int> data;
    while(cin >> n >> m){
        data.resize(n);
        for(int i=0; i<n; i++){
            cin >> data[i];
        }

        vector<int> help(n,0);
        help[0] = data[0];
        for(int i=1; i<n; i++){
            data[i] += data[i-1];
        }

        minSum(data, help, m, 0, 0, n-1);
        cout<<min_score<<endl;
    }
    return 0;
}