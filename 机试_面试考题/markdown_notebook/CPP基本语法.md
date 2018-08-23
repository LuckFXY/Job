# 1. 输入

## 1.1 输入一个行由空格分割的数字

```cpp
int main(){
    vector<int> data;
    int i=0, tmp;
    while(cin >> tmp){
        data.emplace_back(tmp);
        i += 1;
    }
    for(vector<int>::iterator it = data.begin(); it != data.end(); it++){
        cout<< *it <<' ';
    }
    cout<<endl;
    return 0;
}
```

tmp, whlie( cin >> tmp ) 输入正确的时候继续，否则退出。

## 1.2 输入由非空格分割的数据 
输入格式为一组数组用逗号分割，每组数据之间用分号分割 e.g. 1,2;3,4;5,6 

### 1.2.1 scanf 拯救世界

```cpp
#include <cstdio>
typedef pair<int, int> PAIR;
ostream& operator << (ostream& out, const PAIR src){
    out<<src.first<<' '<<src.second;
    return out;
}
int main(){
    vector<PAIR> data;
    int a,b;
    char ch;
    while(scanf("%d,%d",&a, &b) == 2){
        data.emplace_back(PAIR(a,b));
        ch = getchar();
    }
    for(vector<PAIR>::iterator it = data.begin(); it != data.end(); it++){
        cout<< *it <<endl;
    }
    return 0;
}
```

### 1.2.2 sstream 孤注一掷

```cpp
#include <sstream>
#include <string>
int main(){
    vector<PAIR> data;
    int a,b;
    char ch;
    string s;
    stringstream ss;
    cin >> s;
    ss.clear();
    ss.str(s);
    while(ss >> a >> ch >> b){
        data.emplace_back(PAIR(a,b));
        if(ss.peek() == ';')
            ss.ignore();
    }
    for(vector<PAIR>::iterator it = data.begin(); it != data.end(); it++){
        cout<< *it <<endl;
    }
    return 0;
}
```

## 1.3 输入三角形形状的数据

一共m行，每一行的元素个数比上一行多一个，第一行只有一个元素。

1

2 3

4 5 6

```cpp
void mprint(vector<vector<int>> m){
    for(auto row = m.begin(); row != m.end(); row ++){
        for(auto v = (*row).begin(); v != (*row).end(); v++){
            cout<< *v << ' ';
        }
        cout<<endl;
    }
}
int main(){
    int m;
    cin >> m;
    vector<vector<int>> data(m, vector<int>(1,0));
    for(int i=0; i<m; i++){
        data[i].resize(i+1);
        for(int j=0; j<i+1; j++){
            cin >> data[i][j];
        }
    }
    mprint(data);
    return 0;
}
```

# 2. 常用的算法

#include <alogrithm>

## 2.1 sort

sort(begin ,start, custom_compare_fucntion)

## 2.2 返回边界值的函数

### 2.2.1 无序序列最值

1. max_element(v.begin(), v.end()) 返回第一个最大值的地址
2. min_element(v.begin(), v.end()) 返回第一个最小值的地址

### 2.2.2 有序序列重复元素上下界

非递减序列[first,last)

![lower_bound](../img/lower_bound.png)

1. lower_bound(begin, end, key) 第一个大于等于key的元素位置
2. upper_bound(begin, end, key) 第一个大于key的元素位置

## 2.3 Priority_Queue

template<typename _Tp,
             typename _Sequence = vector<_Tp>,
             typename _Compare  = less<typename _Sequence::value_type> >

第一个参数 _Tp： 指定存储的类型名称；

第二个参数 _Sequence： 指定存储的数据结构，该结果必须支持随机存取迭代器；

第三个参数 _Compare ： 比较函数，对于自定义类型有两种方法实现大小顶堆，第一个是重载操作符，第二个是写一个结构实现比较。

```cpp
// 默认是最大堆
priority_queue<int,vector<int>> pqueue_int;
for(int i = 0 ; i < 10 ; ++i){
    pqueue_int.push(rand()%100);
}
while(!(pqueue_int.empty()))
{
    cout<<pqueue_int.top()<<"\t";
    pqueue_int.pop();
}
cout<<endl;
//最小堆
template<typename _Tp>
struct mygreater
{
    bool
    // 当新元素 __y 小于父节点 __x，向上调整
    operator()(const _Tp& __x, const _Tp& __y) const
    { return __x > __y; }
};
priority_queue<int,vector<int>,mygreater<int>> pqueue_int;
```

# 3. 常用的数据结构

## 2.0 pair

```cpp
typedef pair<int, int> PAIR;
ostream& operator << (ostream& out, const PAIR src){
    out<<src.first<<' '<<src.second;
    return out;
}
bool comp(PAIR a, PAIR b){
    if( a.first == b.first){
        return a.second < b.second;
    }
    else{
        return a.first < b.first;
    }
}
// sort 
#include <algorithm>
// comp is a custom compare function, None is ok for pair
sort(vec.begin(), vec.end(), comp)
```

## 2.1 queue 

queue模板类的定义在<queue>头文件中。 

入队，如例：q.push(x); 将x接到队列的末端。

出队，如例：q.pop(); 弹出队列的第一个元素，注意，并不会返回被弹出元素的值。

访问队首元素，如例：q.front()，即最早被压入队列的元素。

访问队尾元素，如例：q.back()，即最后被压入队列的元素。

判断队列空，如例：q.empty()，当队列空时，返回true。

访问队列中的元素个数，如例：q.size()

## 2.2 vector

vector属于std命名域的 ，

### 2.2.1 初始化和赋值

#### 2.2.1.1 重复 

vec.assign(n,elem)   将n个elem的拷贝赋值给c。

vec(n, elem) 初始化 ~~

#### 2.2.1.2 区间

int a[] = {1,2,3,,4,5}

vec.assign(a, a+3) 将[0,3)区间中的数据赋值给vec。 

vec(a, a+3)  初始化 ~~

#### 2.2.1.3 容量大小和扩容

vec.size() 返回元素个数， vec.resize(n) 扩展vec的容量到n

### 2.2.2 迭代器和返回首尾元素

类型为 ： vector<template>::iterator

|        | 地址  | 元素值 |        弹出        |            插入            |
| :----: | :---: | :----: | :----------------: | :------------------------: |
| 首元素 | begin | front  | erase(vec.begin()) | insert(vec.begin(),  elem) |
| 尾元素 |  end  |  back  |      pop_back      |        emplace_back        |

### 2.2.3 其他常用函数

1. 返回指定元素的值  vec.at()

2. 是否为空 vec.empty()

3. 删除元素 

   1. 指定位置 vec.erase(pos)
   2. 区间         vec.erase(beg, end)

4. 使用构造函数返回一个拷贝。 

   get_allocator ()

5. 插入元素

   1.  c.insert(pos,elem)       pos位置插入一个elem拷贝，传回新数据位置
   2.  c.insert(pos,n,elem)    pos位置插入n个elem数据。无返回值 
   3.  c.insert(pos,beg,end)  pos位置插入在[beg,end)区间的数据。无返回值。 

6. 互换元素

   c1.swap(c2) 

7. 清空

   clear（）

## 2.3 map

Map是c++的一个标准容器，她提供了很好一对一的关系,

- 第一个为关键字（key），再函数中只能map出现一次（）
- 第二个为该关键字的值 （value）

### 2.3.1 初始化

| map <string , int >mapstring | map <int ,string >mapint | map <sring, char> mapstring |
| :--------------------------------------- | :------------------------------------ | :---------------------------------- |
|map< char ,string>mapchar   | map <char ,int>mapchar | map <int ,char > mapint |

```
// 可以直接赋初值
std::map<int, string> int_to_string = {
{1, "what"},
{2, "a"},
{3, "fuck"},
{4, "day"},
....
};
```

### 2.3.2 插入数据

```cpp
// case 1: pair大法好 唯一性
Map<int,string> test；
test.insert(pair<int, string>(1, "test"));
// case 2: map 构造函数
enumMap.insert(map<int, CString> :: value_type(2, "Two"))
my_Map.insert(map<string,int>::value_type("b",2));
// case 3: array风格 可以覆盖
test[0]= "xusupeng";
```

### 2.3.3 查找和遍历

```cpp

// case 1 find 失败返回 test.end()
test.find(key)
// case 2: just use key as the index of map 
test[key]
// iterator
for(auto it = test.begin(); it != test.end(); it++){
	cout<<it.first()<<' '<<it.second();
}
```

### 2.3.4 删除数据

```cpp
map<int ,string >::iterator l_it;;
l_it=test.find(112);
if(l_it==test.end())
	cout<<"we do not find 112"<<endl;
else  
    maplive.erase(l_it);  //delete 112;
```

### 2.3.5 容器的交换

Map中的swap不是一个容器中的元素交换，而是两个容器交换； 

```cpp
map<int string> m1, m2, m3;
m1.swap(m2);
```

### 2.3.6.map的sort问题

Map中的元素是自动按key升序排序,所以不能对map用sort函数

 ### 2.3.7. map的基本操作函数：      

C++ Maps是一种关联式容器，包含“关键字/值”对      

1.  begin()          返回指向map头部的迭代器       
2.  clear(）         删除所有元素       
3.  count()          返回指定元素出现的次数       
4.  empty()          如果map为空则返回true       
5.  end()            返回指向map末尾的迭代器       
6.  equal_range()    返回特殊条目的迭代器对       
7.  erase()          删除一个元素       
8.  find()           查找一个元素      
9.  get_allocator()  返回map的配置器      
10.  insert()         插入元素       
11.  key_comp()       返回比较元素key的函数      
12.  lower_bound()    返回键值>=给定元素的第一个位置       
13.  max_size()       返回可以容纳的最大元素个数      
14.  rbegin()         返回一个指向map尾部的逆向迭代器       
15.  rend()           返回一个指向map头部的逆向迭代器       
16.  size()           返回map中元素的个数       
17.  swap()            交换两个map       
18.  upper_bound()     返回键值>给定元素的第一个位置       
19.  value_comp()      返回比较元素value的函数 

### 2.3.8 插入二重map

```cpp
#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
using namespace std;
int main(){
    map<int , map<int, int>> graph;
    vector<vector<int>> data={
            {0,1},{0,5},{1,2},{1,3},{2,3},{3,4},{3,5}
    };
    int weight[6] = {2,8,3,5,6,1};
    for(int i=0; i<6; i++){
        int start = data[i][0], end = data[i][1];
        if(graph.find(start) == graph.end()){
            graph.insert(
                    make_pair(
                            start, map<int, int>()
                    ));
            graph[start][end] = weight[end];
        }
        else{
            map<int, int>& inner = graph[start];
            inner.insert(make_pair(end, weight[end]));
        }
    }

    for(auto it = graph.begin(); it != graph.end(); it++){
        printf("%d : ", (*it).first);
        for(auto jt = (*it).second.begin(); jt != (*it).second.end(); jt++ ){
            printf("(%d %d) ",(*jt).first, (*jt).second);
        }
        cout<<endl;
    }
    return 0;
}
```

```
0 : (1 8) (5 1) 
1 : (2 3) (3 5) 
2 : (3 5) 
3 : (4 6) 
```

## 2.4 set 

* 必须说明的是set关联式容器。set作为一个容器也是用来存储同一数据类型的数据类型，并且能从一个数据集合中取出数据，在set中每个元素的值都唯一，而且系统能根据元素的值自动进行排序。**不过set不支持随机访问**
* iterator这里就相当于指向节点的指针，内存没有变，每次insert之后，以前保存的iterator不会失效

### 2.4.1 常用方法

set<int> t      ------      定义一个int类型的容器，（默认）里面元素从小到大

set<int, greater<int> > t      ------      定义一个int类型的容器，里面元素从大到小

t.insert(k)      ------      插入元素k，多次插入同一个元素后面无效

begin()     　　 ,返回set容器的第一个元素的标记位置，地址

end() 、rbegin、rend()　　　返回set容器的最后一个元素的地址

size() 　　　　 ,返回当前set容器中的元素个数

count()             查询一个键值出现的次数，set中只能出现0,1

t.erase(k)      ------      删除元素k，若不存在则删除无效

t.clear()      ------      清空容器

t.empty()      ------      判断容器是否为空

**lower_bound(k) **     ------      返回第一个大于等于k的元素的迭代器

**upper_bound(k) **     ------      返回第一个大于k的元素的迭代器

**t.find(k) **     ------      寻找k，若找到返回对应的迭代器，否则返回end();

### 2.4.2 algorithm 常用方法

std::set_intersection() :这个函数是求两个集合的交集。
std::set_union() :求两个集合的并集
std::set_difference（）：差集
std::set_symmetric_difference（）：得到的结果是 第一个迭代器相对于第二个的差集 并上第二个相对于第一个的差集

### 2.4.3 实例

```cpp
#include <iostream>
#include <set>
#include <algorithm>
#define len(arr, type) (sizeof(arr) / sizeof(type))
using namespace std;
ostream& operator <<(ostream &out, const set<int> s){
    cout<<"{ ";
    for(auto it = s.begin(); it != s.end(); it++){
        cout<<(*it)<<',';
    }
    cout<<"\b }";
}
int main(){
    int aa[] = {9,1, 7,0,4,2};
    int bb[] = {8,6,3,5,7,9};
    set<int> a,b,c,union_set,intersect;
    for(int i=0; i<len(aa, int); i++){
        a.insert(aa[i]);
    }
    for(int i=0; i<len(bb, int); i++){
        b.insert(bb[i]);
    }

    cout<<"A = "<<a<<endl;
    cout<<"B = "<<b<<endl;

    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(union_set, union_set.end()));
    cout<<"A v B = "<<union_set<<endl;

    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(intersect, intersect.end()));
    cout<<"A ^ B = "<<intersect<<endl;

    c.clear();
    set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.end()));
    cout<<"A - B = " << c<< endl;

    c.clear();
    set_difference(b.begin(), b.end(), a.begin(), a.end(), inserter(c, c.end()));
    cout<<"B - A = " << c<< endl;

    c.clear();
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.end()));
    cout<<"(A - B) v (B - A) = "<<c<<endl;
    c.clear();
    set_difference(
            union_set.begin(), union_set.end(),
            intersect.begin(), intersect.end(),
            inserter(c, c.end())
            );
    cout<<"(A v B) - (A ^ B) = "<<c<<endl;
    return 0;
}
```

 ```
A = { 0,1,2,4,7,9 }
B = { 3,5,6,7,8,9 }
A v B = { 0,1,2,3,4,5,6,7,8,9 }
A ^ B = { 7,9 }
A - B = { 0,1,2,4 }
B - A = { 3,5,6,8 }
(A - B) v (B - A) = { 0,1,2,3,4,5,6,8 }
(A v B) - (A ^ B) = { 0,1,2,3,4,5,6,8 }
 ```

## 2. 5 string

CSDN 作者 wust_tanyao

引用网址 https://blog.csdn.net/u011032846/article/details/48712819

### 2.5.1 构函数如下：

1. string s;    //生成一个空字符串s 
2. string s(str) //拷贝构造函数 生成str的复制品
3. string s(str,stridx) //将字符串str内“始于位置stridx”的部分当作字符串的初值
4. string s(str,stridx,strlen) //将字符串str内“始于stridx且长度顶多strlen”的部分作为字符串的初值
5. string s(cstr) //将C字符串作为s的初值 
6. string s(chars,chars_len) //将C字符串前chars_len个字符作为字符串s的初值。
7. string s(num,c) //生成一个字符串，包含num个c字符
8. string s(beg,end) //以区间beg;end(不包含end)内的字符作为字符串s的初值
9. s.~string() //销毁所有字符，释放内存 

### 2.5.2 赋值

s.assign(str); //不说 s.assign(str,1,3);//如果str是”iamangel” 就是把”ama”赋给字符串 s.assign(str,2,string::npos);//把字符串str从索引值2开始到结尾赋给s s.assign(“gaint”); //不说 s.assign(“nico”,5);//把'n' ‘I' ‘c' ‘o' ‘/0'赋给字符串 s.assign(5,'x');//把五个x赋给字符串

### 2.5.3 存取和比较

* 操作符[] 有效索引0~str.length()）如果索引失效，会引起未定义的行为
* at()会检查，如果使用 at()的时候索引无效，会抛出out_of_range异常。
* 在使用>,>=,<,<=这些操作符的时候是根据“当前字符特性”将字符按字典顺序进行逐一得 

```cpp
string s(“abcd”);
s.compare(“abcd”); //返回0
s.compare(“dcba”); //返回一个小于0的值
s.compare(“ab”); //返回大于0的值
s.compare(s); //相等
s.compare(0,2,s,2,2); //用”ab”和”cd”进行比较 小于零
s.compare(1,2,”bcx”,2); //用”bc”和”bc”比较。
```

### 2.5.4 string的连接

1. string &operator+=(const string &s);//把字符串s连接到当前字符串的结尾  
2. string &append(const char *s);            //把c类型字符串s连接到当前字符串结尾 
3. string &append(const char *s,int n);//把c类型字符串s的前n个字符连接到当前字符串结尾 
4. string &append(const string &s);    //同operator+=() 
5. string &append(const string &s,int pos,int n);//把字符串s中从pos开始的n个字符连接到当前字符串的结尾 
6. string &append(int n,char c);        //在当前字符串结尾添加n个字符c 
7. string &append(const_iterator first,const_iterator last);//把迭代器first和last之间的部分连接到当前字符串的结尾

### 2.5.5 交换、查找、替换

**string的交换：**void swap(string &s2);    //交换当前字符串与s2的值

**string类的查找函**  

find(char\* sub [, int pos])函数：找到返回位置，否则-1；

find(string s, [, int pos]) : 找到返回 string::size_type 类型的数字

```
#include <iostream>
#include <string>
using namespace std;
int main(){
    string s = "I am ready for learning c++ again start from the struct of data";
    string::size_type idx;
    idx = s.find("ready");
    cout<<idx<<endl;
    return 0;
}
```

**string类的替换函数：**

 string &replace(int p0, int n0,const char *s);//删除从p0开始的n0个字符，然后在p0处插入串s
string &replace(int p0, int n0,const char *s, int n);//删除p0开始的n0个字符，然后在p0处插入字符串s的前n个字符
string &replace(int p0, int n0,const string &s);//删除从p0开始的n0个字符，然后在p0处插入串s
string &replace(int p0, int n0,const string &s, int pos, int n);//删除p0开始的n0个字符，然后在p0处插入串s中从pos开始的n个字符
string &replace(int p0, int n0,int n, char c);//删除p0开始的n0个字符，然后在p0处插入n个字符c
string &replace(iterator first0, iterator last0,const char *s);//把[first0，last0）之间的部分替换为字符串s
string &replace(iterator first0, iterator last0,const char *s, int n);//把[first0，last0）之间的部分替换为s的前n个字符
string &replace(iterator first0, iterator last0,const string &s);//把[first0，last0）之间的部分替换为串s
string &replace(iterator first0, iterator last0,int n, char c);//把[first0，last0）之间的部分替换为n个字符c
string &replace(iterator first0, iterator last0,const_iterator first, const_iterator last);//把[first0，last0）之间的部分替换成[first，last）之间的字符串

**string类的插入函数：** string &insert(int p0, const char *s);
string &insert(int p0, const char *s, int n);
string &insert(int p0,const string &s);
string &insert(int p0,const string &s, int pos, int n);
//前4个函数在p0位置插入字符串s中pos开始的前n个字符
string &insert(int p0, int n, char c);//此函数在p0处插入n个字符c
iterator insert(iterator it, char c);//在it处插入字符c，返回插入后迭代器的位置
void insert(iterator it, const_iterator first, const_iterator last);//在it处插入[first，last）之间的字符
void insert(iterator it, int n, char c);//在it处插入n个字符c

**string类的删除函数** iterator erase(iterator first, iterator last);//删除[first，last）之间的所有字符，返回删除后迭代器的位置
iterator erase(iterator it);//删除it指向的字符，返回删除后迭代器的位置
string &erase(int pos = 0, int n = npos);//删除pos开始的n个字符，返回修改后的字符串

**string类的迭代器处理：** string类提供了向前和向后遍历的迭代器iterator，迭代器提供了访问各个字符的语法，类似于指针操作，迭代器不检查范围。

用string::iterator或string::const_iterator声明迭代器变量，const_iterator不允许改变迭代的内容。常用迭代器函数有：
const_iterator begin()const;
iterator begin();                //返回string的起始位置
const_iterator end()const;
iterator end();                    //返回string的最后一个字符后面的位置
const_iterator rbegin()const;
iterator rbegin();                //返回string的最后一个字符的位置
const_iterator rend()const;
iterator rend();                    //返回string第一个字符位置的前面
rbegin和rend用于从后向前的迭代访问，通过设置迭代器string::reverse_iterator,string::const_reverse_iterator实现

**字符串流处理：** 通过定义ostringstream和istringstream变量实现，<sstream>头文件中
**例如：**
string input("hello,this is a test");
istringstream is(input);
string s1,s2,s3,s4;
is>>s1>>s2>>s3>>s4;//s1="hello,this",s2="is",s3="a",s4="test"
ostringstream os;
os<<s1<<s2<<s3<<s4;
cout<<os.str();