# 1 统计用户喜好

为了不断优化推荐效果，今日头条每天要存储和处理海量数据。假设有这样一种场景：我们对用户按照它们的注册时间先后来标号，对于一类文章，每个用户都有不同的喜好值，我们会想知道某一段时间内注册的用户（标号相连的一批用户）中，有多少用户对这类文章喜好值为k。因为一些特殊的原因，不会出现一个查询的用户区间完全覆盖另一个查询的用户区间(不存在L1<=L2<=R2<=R1)。 

```
/*
1、首先存储的时候，每个喜好值分别一个vector，分别存入map中，对于每个喜好值的vector，存入的是，用户的id，因为输入是从小到大输入的，所以就可以保证vector有序，然后用二分查找区间的左右端点。
2、这里的二分不是常规的二分查找，对于区间左端点，在vector查找的是小于target的点的最大下标，如果target小于vector最小值，直接返回-1
3、对于区间右端点，查找的是小于等于target的最大下标，如果target大于vector的最大值，直接返回vector最大值的下标
 
*/
#include<iostream>
#include<map>
#include<vector>
using namespace std;
 
int find_low(vector<int>& v,int target){
    int low=0;
    int high=v.size()-1;
    int mid;
    if(target<=v[low]) return -1;
    if(target>v[high]) return high;
    while(low<high){
        mid=(low+high+1)>>1;
        //cout<<low<<" "<<high<<"  "<<mid<<endl;
        if(target<=v[mid]){
            high=mid-1;
        }else{
            low=mid;
        }
    }
    return high;
}
 
int find_high(vector<int>& v,int target){
    int low=0;
    int high=v.size()-1;
    int mid;
    if(target<v[low]) return -1;
    if(target>=v[high]) return high;
    while(low<high){
        mid=(low+high+1)>>1;
        //cout<<low<<"  "<<high<<"  "<<mid<<endl;
        if(target==v[mid]){
            return mid;
        }else if(target<v[mid]){
            high=mid-1;
        }else{
            low=mid;
        }
    }
    return high;
}
 
int main()
{
    int n,q,t;
    map<int,vector<int> > count;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>t;
        if(count.count(t)==0){
            vector<int> v;
            v.push_back(i);
            count[t]=v;
        }else{
            count[t].push_back(i);
        }
    }
    cin>>q;
    int l,r,k;
    int sum;
    for(int i=0;i<q;i++){
        cin>>l>>r>>k;
        sum=0;
        if(count.count(k)>0){
            vector<int> v=count[k];
            int low=find_low(v,l);
            int high=find_high(v,r);
            //cout<<low<<" "<<high<<endl;
            sum=high-low;
        }
        cout<<sum<<endl;
    }
    return 0;
}
```

# 2. 不合适的手珠

作为一个手串艺人，有金主向你订购了一条包含n个杂色串珠的手串——每个串珠要么无色，要么涂了若干种颜色。为了使手串的色彩看起来不那么单调，金主要求，手串上的任意一种颜色（不包含无色），在任意连续的m个串珠里至多出现一次（注意这里手串是一个环形）。手串上的颜色一共有c种。现在按顺时针序告诉你n个串珠的手串上，每个串珠用所包含的颜色分别有哪些。请你判断该手串上有多少种颜色不符合要求。即询问有多少种颜色在任意连续m个串珠中出现了至少两次。 

```cpp
#include <iostream>
#include <vector>
#include <set>

using namespace std;
int main(){
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> first(c+1, 0);  //记录颜色第一次出现的珠子序号
    vector<int> record(c+1, 0);  //记录颜色出现的珠子序号
    set<int> res;  //记录不符合要求的颜色的序号
    for(int i=1; i<=n; i++)
    {
        int num; cin >> num;  //珠子的颜色数量
        for(int j=0; j<num; j++)
        {  //遍历每个颜色
            int tmp; cin >> tmp;
            if(record[tmp] == 0)
            {
                record[tmp] = i;   //初始化颜色出现的位置
                first[tmp] = i;   //
            }
            else
            {
                if(i-record[tmp]<m)   //出现位置的差小于m个
                {
                    res.insert(tmp);  //记录这种颜色，不符合条件
                }
                else
                {
                    record[tmp] = i;   //符合条件就更新
                }
            }
        }
    }
    //对比颜色出现的最后一次珠子位置和出现第一次位置的距离差
    for(int i=1; i<=c; i++)
    {
        int a = record[i];
        int b = first[i];
        if(n-a+b <m)
            res.insert(i);
    }
    cout << res.size();  //返回多少个颜色不符合
    return 0;
}
```

