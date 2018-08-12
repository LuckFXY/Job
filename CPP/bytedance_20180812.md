# 20180812 头条机试

惨惨惨，前天开始用CPP写机试的我被头条不定长输入坑。0.9/5 ![img](./img/sad.png)

### 1. 球迷

在一个矩阵观众席上，不同队伍的球迷相邻而坐（斜着也选），不同队伍的球迷绝不相邻（至少相隔一个空位）。请统计观众席上多少个队伍的球迷，球迷最多一组有多少人？

输入：

第一行，观众席的行和列m,n

从第2行开始到第m+1行，每一行置1为球迷，0为空位

输出：

队伍数量，球迷最多一组人数

e.g

10,10

0,0,0,0,0,0,0,0,0,0

0,0,0,1,1,0,1,0,0,0

0,1,0,0,0,0,0,1,0,1

1,0,0,0,0,0,0,0,1,1

0,0,0,1,1,1,0,0,0,1

0,0,0,0,0,0,1,0,1,1

0,1,1,0,0,0,0,0,0,0

0,0,0,1,0,1,0,0,0,0

0,0,1,0,0,1,0,0,0,0

0,1,0,0,0,0,0,0,0,0

> ```
> #include <set>
> #include <iostream>
> #include <vector>
> using namespace std;
> typedef pair<int,int> PAIR;
> int main() {
>     int m=10, n=10;
>     char tmp;
>     cin>>m>>tmp>>n;
>     vector<vector<int>> matrix(m, vector<int>(n,0));
>     set<long> close;
>     vector<PAIR> stack;
>     for(int i=0; i<m; i++){
>         for(int j=0; j<n-1; j++){
>             cin>>matrix[i][j]>>tmp;
>         }
>         cin>>matrix[i][n-1];
>     }
>     test_input(matrix);
>     int p=0, q=0;
>     long key;
>     for(int i=0; i<m; i++){
>         for(int j=0; j<n; j++){
>             key = i*m+j;
>             if(close.find(key) != close.end() or matrix[i][j] == 0)
>                 continue;
>             p += 1;
>             stack.clear();
>             PAIR t = PAIR(i,j);
>             stack.emplace_back(t);
>             int cnt=0;
>             while(!stack.empty()){
>                 PAIR cur = *(stack.end()-1);
>                 stack.pop_back();
>                 key = cur.first*m + cur.second;
>                 if(close.find(key) == close.end()){
>                     close.insert(key);
>                     cnt += 1;
>                     for(int a=cur.first-1;a<cur.first+2;a++){
>                         if(a<0 or a>=n) continue;
>                         for(int b=cur.second-1; b< cur.second+2; b++){
>                             key = a*m+b;
>                             if(b>=0 && b<m && close.find(key) == close.end()){
>                                 if(matrix[a][b] == 1) {
>                                     stack.emplace_back(PAIR(a, b));
>                                 }
>                             }
>                         }
>                     }
>                 }
>             }
>             q = cnt > q ? cnt: q;
>         }
>     }
>     cout<<p<<','<<q<<endl;
> }
> ```

### 2. 合并区间

给定m行区间[left,right]信息，将重叠的两个区间合并为一个大的区间，输出合并后的结果

输入

第一行m

接下来m行为区间信息。区间左右值用逗号分隔，不同的区间用分号分隔

输出

合并后的区间，区间左右值用逗号分隔，不同的区间用分号分隔

e.g

输入

2

0,1;2,9;10,16;20,30

6,10;30,40;44,50;70,80

输出

0,1;2,16;20,40;44,50;70,80;

> ```
> #include<sstream>
> #include <iostream>
> #include <vector>
> #include <string>
> using namespace std;
> 
> typedef pair<int,int> PAIR;
> typedef vector<PAIR>::iterator iter;
> 
> ostream& operator << (ostream& out, const PAIR& src){
>     out<<src.first<<','<<src.second;
> }
> 
> bool less_pair ( PAIR& src,  PAIR& dst) {
>     return src.first <= dst.first;
> }
> 
> void mergeIntervals() {
>     vector <PAIR> intervals;
>     int m;
>     stringstream stream;
>     cin>>m;
>     for(int i=0; i<m; i++){
>         stream.clear();
>         stream.str(s[i]);
>         int a,b;
>         char c;
>         while(stream>>a>>c>>b){
>             intervals.emplace_back(PAIR(a,b));
>             if(stream.peek()==';')
>                 stream.ignore();
>         }
>     }
>     
>     sort(intervals.begin(), intervals.end(), less_pair);
> 
>     PAIR tmp = PAIR(-1,-1);
>     PAIR* last = &tmp;
> 
>     vector<iter> output;
>     for(auto it=intervals.begin();it!=intervals.end();it++){
>         if( (*it).first > (*last).second){
>             output.emplace_back(it);
>             last = &(*it);
>         }
>         else{
>             (*last).second = (*it).second;
>         }
>     }
>     for(auto it = output.begin(); it!=output.end(); it++){
>         cout<<intervals[(*it) - intervals.begin()]<<';';
>     }
>     cout<<endl;
>     return 0;
> }
> ```



### 3.4.5没有看

![img](./img/tear.png)

 