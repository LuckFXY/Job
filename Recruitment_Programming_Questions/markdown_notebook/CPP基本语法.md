# 1. 输入

## 1.1 输入一个行由空格分割的数字

```
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

```
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

```
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

```
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

## 2.1 sort

## 2.2 max_element



# 3. 常用的数据结构

## 2.1 pair

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

### 2.3.1 构造方法

| map <string , int >mapstring | map <int ,string >mapint | map <sring, char> mapstring |
| :--------------------------------------- | :------------------------------------ | :---------------------------------- |
|map< char ,string>mapchar   | map <char ,int>mapchar | map <int ,char > mapint |

### 2.3.2 插入数据

```cpp
// case 1: pair大法好 唯一性
Map<int,string> test；
test.insert(pair<int, string>(1, "test"));
// case 2: array风格 可以覆盖
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

### 6.map的sort问题

Map中的元素是自动按key升序排序,所以不能对map用sort函数

 ### 7. map的基本操作函数：      

C++ Maps是一种关联式容器，包含“关键字/值”对      

1.  begin()          返回指向map头部的迭代器       
2. clear(）         删除所有元素       
3. count()          返回指定元素出现的次数       
4. empty()          如果map为空则返回true       
5. end()            返回指向map末尾的迭代器       
6. equal_range()    返回特殊条目的迭代器对       
7. erase()          删除一个元素       
8. find()           查找一个元素      
9.  get_allocator()  返回map的配置器      
10.  insert()         插入元素       
11. key_comp()       返回比较元素key的函数      
12. lower_bound()    返回键值>=给定元素的第一个位置       
13. max_size()       返回可以容纳的最大元素个数      
14. rbegin()         返回一个指向map尾部的逆向迭代器       
15. rend()           返回一个指向map头部的逆向迭代器       
16. size()           返回map中元素的个数       
17. swap()            交换两个map       
18. upper_bound()     返回键值>给定元素的第一个位置       
19. value_comp()      返回比较元素value的函数 

 

 

 

 




　　