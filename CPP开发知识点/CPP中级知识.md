引用网址: https://blog.csdn.net/ac540101928/article/details/52381805

# 1. 编译后程序的内存布局

## 1.1 C/C++ 内存布局

一个经过编译的C/C++的程序占用的内存分成以下几个部分：

1. 栈区（stack）：

   由编译器自动分配和释放 ，存放函数的参数值、局部变量的值等，甚至函数的调用过程都是用栈来完成。其操作方式类似于数据结构中的栈。

2. 堆区（heap） ：

   一般由程序员手动申请以及释放， **若程序员不释放，程序结束时可能由OS回收 **。注意它与数据结构中的堆是两回事，分配方式类似于链表。

3. 全局区（静态区）（static）：

   **全局变量**和**静态变量**的存储是放在一块的，**初始化的**全局变量和静态变量在一块区域， **未初始化的**全局变量和未初始化的静态变量在相邻的另一块区域。程序结束后由系统释放空间。

4. 文字常量区：

   常量字符串就是放在这里的。 程序结束后由系统释放空间。

5. 程序代码区：

   存放函数体的二进制代码。

## 1.2 内存段式管理

目前通用系统（Linux或者Window）多采用段页式内存管理方式，即段式管理与页式管理的组合。每个程序的内存空间分为若干段，进行内存的分配与释放管理；每个段又分为若干页，进行虚拟页与实际页面的映射。段式管理程序以段为单位分配内存，依赖地址映射机制完成段式虚拟地址与实际内存地址的转换。段式管理（程序分段思想）在无OS的嵌入式开发和微系统开发中具有广泛的应用。

* 代码段（code/text segment）

  用来存放执行代码的一块内存区域。该区域的大小在程序运行前就已经确定，并且内存区域属于只读。其中可能包含一些只读的常数变量（如字符串常量）。

* 数据段（data segment）

  * 动态内存分配 : 堆 malloc
  * 静态内存分配
    * 初始化为非零的数据区
    * BSS（Block Started by Symbol）区域一般存放未初始化的全局数据和静态数据

* 栈段（stack segment）

```
int a = 0; 全局初始化区
char *p1; 全局未初始化区
main()
{
    int b; //栈中
    char s[] = "abc"; //栈中
    char *p2; //栈中
    char *p3 = "123456"; //123456/0在常量区，p3在栈上
    static int c =0； //全局（静态）初始化区
    //以下分配得到的10和20字节的区域就在堆区
    p1 = (char *)malloc(10);
    p2 = new char[20];//(char *)malloc(20);
    //123456/0放在常量区，编译器可能会将它与p3所指向的"123456"优化成一个地方。
    strcpy(p1, "123456"); 
}
```

注意p1本身在全局区，而p2本身是在栈中的，只是它们指向的空间是在堆中。

## 1.3 堆和栈的内存分配方式

### 1.3.1 位置

临时变量, 内部变量,系统栈在栈段中

动态分配在数据段的堆中,

全局,静态变量在数据段的BSS和非零数据区,

### 1.3.2 系统响应

* 栈（stack）:只要栈的剩余空间大于所申请空间，系统将为程序提供内存，否则将报异常提示栈溢出。 
* 堆（heap）: 首先应该知道操作系统有一个记录空闲内存地址的链表，当系统收到程序的申请时，会遍历该链表，寻找第一个空间大于所申请空间的堆结点，然后将该结点从空闲结点链表中删除，并将该结点的空间分配给程序。

### 1.3.3 申请大小限制

* 栈（stack）:在Windows下,栈是高地址向低地址扩展的数据结构，是一块连续的内存的区域。

  栈顶的地址和栈的最大容量是系统预先规定好的，在WINDOWS下，栈的大小是2M

  打开工程，依次操作菜单如下：Project->Setting->Link，在Category 中选中Output，然后在Reserve中设定堆栈的最大值和commit。

*  堆是向高地址扩展的数据结构，是不连续的内存区域（空闲部分用链表串联起来）。由系统是用链表来存储空闲内存，而链表的遍历方向是由低地址向高地址。一般来讲在32位系统下，堆内存可以达到4G的空间

### 1.3.4 特殊内容

栈（stack）:在函数调用时，第一个进栈的是主函数中子函数调用后的下一条指令的地址，然后是子函数的各个形参。在大多数的C编译器中，参数是由右往左入栈的，然后是子函数中的局部变量。**注意：静态变量是不入栈的**。当本次函数调用结束后，局部变量先出栈，然后是参数，最后栈顶指针指向最开始存的地址，也就是主函数中子函数调用完成的下一条指令，程序由该点继续运行。 

堆（heap）:一般是在堆的头部用一个字节存放堆的大小，堆中的具体内容有程序员安排。

## 1.4 常见错误

1. 内存的申请和分配并没有成功，但程序员却使用了它。 判断指针的值是否为NULL可以有效地避免这种错误
2. 内存的分配已经成功，但是却没有进行初始化就直接使用它了。 主观地认为自己申请的内存的缺省值为0，这样想是没有什么道理的，内存分配后的值是不确定的
3. 申请了内存，使用完了却忘记了释放，导致内存泄露。它会慢慢地吞噬你的系统资源，直到你的程序彻底完蛋
4. 你很小心地释放了内存，但是却又使用了它。由于程序很复杂或者调用顺序出错，这样可能导致出现上面的错误。

# 2 Dll入口函数参数详解

https://blog.csdn.net/friendan/article/details/7659190

DLL程序入口点函数：DllMain，注意：大小写是区别的(仅导出资源的DLL可以没有DllMain函数)。

## 2.1 函数原型:

```cpp
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    return TRUE;
}
```

### 参数意义:

①hModule参数：指向DLL本身的实例句柄；

②ul_reason_for_call参数：指明了DLL被调用的原因，可以有以下4个取值：

## 2.2 DLL_PROCESS_ATTACH

当DLL被进程 <<第一次>> 调用时，导致DllMain函数被调用，

同时ul_reason_for_call的值为DLL_PROCESS_ATTACH，

如果同一个进程后来再次调用此DLL时，操作系统只会增加DLL的使用次数，

不会再用DLL_PROCESS_ATTACH调用DLL的DllMain函数。

## 2.3 DLL_PROCESS_DETACH：

当DLL被从进程的地址空间解除映射时，系统调用了它的DllMain，传递的ul_reason_for_call值是DLL_PROCESS_DETACH。
★如果进程的终结是因为调用了TerminateProcess，系统就不会用DLL_PROCESS_DETACH来调用DLL的DllMain函数。这就意味着DLL在进程结束前没有机会执行任何清理工作。

## 2.4 DLL_THREAD_ATTACH：

当进程创建一线程时，系统查看当前映射到进程地址空间中的所有DLL文件映像，

并用值DLL_THREAD_ATTACH调用DLL的DllMain函数。 

新创建的线程负责执行这次的DLL的DllMain函数，

只有当所有的DLL都处理完这一通知后，系统才允许线程开始执行它的线程函数。

## 2.5 DLL_THREAD_DETACH：

如果线程调用了ExitThread来结束线程（线程函数返回时，系统也会自动调用ExitThread），

系统查看当前映射到进程空间中的所有DLL文件映像，

并用DLL_THREAD_DETACH来调用DllMain函数，

通知所有的DLL去执行线程级的清理工作。

★注意：如果线程的结束是因为系统中的一个线程调用了TerminateThread，

系统就不会用值DLL_THREAD_DETACH来调用所有DLL的DllMain函数。

# 3 引用

转载请注明出处。https://www.cnblogs.com/qicosmos/p/4283455.html 还有《程序员》2015年1月刊。

## 3.1 右值引用

区分左值和右值的一个简单办法是：看能不能对表达式取地址，如果能，则为左值，否则为右值。 

在C++11中所有的值必属于左值、将亡值、纯右值三者之一 

```
int i = getVar(); 右值赋值完后消失
T&& k = getVar(); //右值引用，k是右值的引用
```

通过右值引用，比之前少了一次拷贝构造和一次析构，原因在于右值引用绑定了右值，让临时右值的生命周期延长了。我们可以利用这个特点做一些性能优化，即避免临时对象的拷贝构造和析构 

### 指针悬挂

一个带有堆内存的类，必须提供一个深拷贝拷贝构造函数，因为默认的拷贝构造函数是浅拷贝，会发生“指针悬挂”的问题。 （一次是临时右值析构的时候删除一次，第二次外面构造的a对象释放时删除一次，而这两个对象的m_ptr是同一个指针，这就是所谓的指针悬挂问题 ）

```c++
class A{
public:
    A():m_ptr(new int(0)){cout << "construct" << endl;}
    A(const A& a):m_ptr(new int(*a.m_ptr)){ //深拷贝的拷贝构造函数
        cout << "copy construct" << endl;
    }
    ~A(){ delete m_ptr;}
private:
    int* m_ptr;
};
int main() {
    A a = GetA();
    return 0;
}
输出：
construct
copy construct
copy construct
```

### 移动构造函数

右值引用消除多余的拷贝

```
class A{
public:
    A() :m_ptr(new int(0)){}
    A(const A& a):m_ptr(new int(*a.m_ptr)) {
    //深拷贝的拷贝构造函数
        cout << "copy construct" << endl;
    }
    A(A&& a) :m_ptr(a.m_ptr){
        a.m_ptr = nullptr;
        cout << "move construct" << endl;
    }
    ~A(){ delete m_ptr;}
private:
    int* m_ptr;
};
int main(){
    A a = Get(false); 
} 
输出：
construct
move construct
move construct
```

移动构造函数并没有做深拷贝，仅仅是将指针的所有者转移到了另外一个对象，同时，将参数对象a的指针置为空，这里仅仅是做了浅拷贝。

可以用c++11的move去移动语义

```c++
{
    std::list< std::string> tokens;
    //省略初始化...
    std::list< std::string> t = tokens; //这里存在拷贝 
}
std::list< std::string> tokens;
std::list< std::string> t = std::move(tokens);  //这里没有拷贝
```

### 模板类的移动

C++11之前调用模板函数时，存在一个比较头疼的问题，如何正确的传递参数 ,C++11引入了完美转发：在函数模板中，完全依照模板的参数的类型（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。 

```c++
void processValue(int& a){ cout << "lvalue" << endl; }
void processValue(int&& a){ cout << "rvalue" << endl; }
template <typename T>
void forwardValue(T&& val)
{
    processValue(std::forward<T>(val)); //照参数本来的类型进行转发。
}
void Testdelcl()
{
    int i = 0;
    forwardValue(i); //传入左值 
    forwardValue(0);//传入右值 
}
输出：
lvaue 
rvalue
```

# 4 智能指针

https://www.cnblogs.com/QG-whz/p/4777312.html

- 简化跟踪堆中（也即C++中new出来的）的对象的过程。一旦一个对象通过调用new被分配出来，记录谁拥有这个对象是很重要的，因为其所有者要负责对它进行delete。但是对象所有者可以有多个，且所有权能够被传递，这就使得内存跟踪变得困难。引用计数可以跟踪对象所有权，并能够自动销毁对象。可以说引用计数是个简单的垃圾回收体系。这也是本文的讨论重点。

```cpp
#include<iostream>
using namespace std;

class Point
{
public:
    Point(int xVal = 0, int yVal = 0) :x(xVal), y(yVal) { }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }
    friend ostream& operator<< (ostream& out, const Point & p);
private:
    int x, y;
};
ostream& operator<< (ostream& out, const Point & p){
    out << p.x <<' '<< p.y;
    return out;
}

template<typename T>
class SmartPtr;

template<typename T>
class U_Ptr{
private:
    friend class SmartPtr<T>;
    U_Ptr(T *ptr) : p(ptr), count(1){}
    ~U_Ptr() {delete p;}

    int count;
    T *p;
};
template<typename T>
class SmartPtr{
public:
    SmartPtr(T *ptr) : rp(new U_Ptr<T>(ptr)) {}
    //当对象作为另一个对象的副本时，复制构造函数复制副本指针，并增加与指针相应的引用计数（加1）
    SmartPtr(const SmartPtr<T> &sp) : rp(sp.rp) {++rp->count;}

    /*
     * 先使左操作数的指针的引用计数减1（为何减1：因为指针已经指向别的地方），
     * 如果减1后引用计数为0，则释放指针所指对象内存。
     * 然后增加右操作数所指对象的引用计数（为何增加：因为此时做操作数指向对象即右操作数指向对象）。
     */
    SmartPtr& operator=(const SmartPtr<T>& rhs){
        ++rhs.rp->count;
        if(--rp->count == 0)
            delete rp;
        rp = rhs.rp;
        return *this;
    }
    ~SmartPtr(){
        if( --rp->count == 0)
            delete rp;
        else
            cout<<"The count of pointer which point to the basic element is " << rp->count<<endl;
    }
    T & operator *(){
        return *(rp->p);
    }
    T* operator ->(){
        return rp->p;
    }
private:
    U_Ptr<T> *rp;
};

int main(){
    Point * pa = new Point(10,20);
    //作用区域
    {//构造函数
        SmartPtr<Point> sptr1(pa); //count=1
        {//复制构造
            SmartPtr<Point> sptr2(sptr1); //count=2
            {//赋值操作符
                SmartPtr<Point> sptr3 = sptr1; //count=3
                cout<< *sptr2 <<endl;
                sptr1->setX(233);
                cout<< *sptr2<<endl;
            }
            //count=2
        }
        //count=1
    }
    //count=0
    cout<<pa->getX();
    return 0;
}
-----------------------------
10 20
233 20
The count of pointer which point to the basic element is 2
The count of pointer which point to the basic element is 1
4857920
```

# 5 指针大全

https://www.cnblogs.com/hongcha717/archive/2010/10/24/1859780.html

## 5.1 数组的指针

数组指针（也称行指针） 定义 int (*p)[n]; ()优先级高，首先说明p是一个指针，指向一个整型的一维数组，这个一维数组的长度是n，也可以说是p的步长。也就是说执行p+1时，p要跨过n个整型数据的长度。 

## 5.2 指针数组 

[]优先级高，先与p结合成为一个数组，再由int*说明这是一个整型指针数组，它有n个指针类型的数组元素 

这里执行p+1是错误的，这样赋值也是错误的：p=a；因为p是个不可知的表示，只存在p[0]、p[1]、p[2]...p[n-1] 

## 5.3 函数指针

void (*funP)(int);   //声明也可写成void(*funP)(int x)，但习惯上一般不这样。

赋值时，可以写成funP=&myFun形式，也可以写成funP=myFun。 

函数指针变量也可以存入一个数组内。数组的声明方法：int (*fArray[10]) ( int ); 

# 6. 并发实现

 C++中对共享数据的存取在并发条件下可能会引起data race的undifined行为，需要限制并发程序以某种特定的顺序执行，有两种方式：使用mutex保护共享数据，原子操作

## 1 原子操作

https://blog.csdn.net/liuxuejiang158blog/article/details/17413149

### 1. std::atomic_flag

* std::atomic_flag是一个bool原子类型有两个状态：set(flag=true) 和 clear(flag=false)，必须被ATOMIC_FLAG_INIT初始化此时flag为clear状态，相当于静态初始化。不支持拷贝、赋值等操作，这和所有atomic类型一样，因为两个原子类型之间操作不能保证原子化。atomic_flag的可操作性不强导致其应用局限性，还不如atomic\<bool\>
* 一旦atomic_flag初始化后只有三个操作：test_and_set,clear,析构 
* atomic_flag::test_and_set
  * 检查flag是否被设置，若被设置直接返回true 
  * 若没有设置则设置flag为true后再返回false。atomic_clear()清楚flag标志即flag=false。 
* atomic_clear()清楚flag标志即flag=false 

### 2. atomic\<T\>模板类

atomic\<T\>模板类，生成一个T类型的原子对象，并提供了系列原子操作函数。其中T是trivially  copyable type满足：要么全部定义了拷贝/移动/赋值函数，要么全部没定义;没有虚成员;基类或其它任何非static成员都是trivally copyable。 

有一条规则：不要在保护数据中通过用户自定义类型T通过参数指针或引用使得共享数据超出保护的作用域。 

### 3. std::atomic针对整数和指针的特化：

不能像传统那样拷贝和赋值，可以通过内置成员函数load(),store(),exchange()完成赋值，支持复合赋值运算，自增自减运算，还有特有的fetch系列函数



### 4.atomic\<bool\>

 atomic\<bool>同样不可以赋值(这里指两个atomic\<bool>间的赋值)、拷贝，但是其可以直接初始化，如：atomic\<bool> flag(false); flag=true。atomic_flag::test_and_set()被atomic::exchange()替代，更多操作见atomic\<T>。 

compare_exchange_weak可能失败，特别是线程数多于CPU核心数时compare-exchange这个指令序列可能CPU不能保证原子化，所以经常在循环中：

```cpp
std::atomic<bool> b;
bool x=b.load(std::memory_order_acquire);
b.store(true);
x=b.exchange(false,std::memory_order_acq_rel);//更改为false并返回原来的值
```

 compare_exchange_strong可以保证当atomic不等于expected时返回false，不需要循环保护。
    std::atomic_flag是lock free的，但是atomic<bool>不一定是lock free的，可以用atomic<T>::is_lock_free()判断。

##### 读者写者 

```cpp
#include <vector>
#include <atomic>
#include <iostream>
std::vector<int> data;
std::atomic<bool> data_ready(false);
void reader_thread()
{
  while(!data_ready.load()) 
  {
    std::this_thread::sleep(std::milliseconds(1));
  }
  std::cout<<”The answer=”<<data[0]<<”\n”;// 1 
}
void writer_thread()
{
  data.push_back(42);//2  由于1和2处发生了data race，所以需要线程同步，可以使用mutex，此处使用atomic<bool>强制线程间有个顺序关系 
  data_ready=true; 
}
```

# 7 new 和 malloc

new的功能是在堆区新建一个对象，并返回该对象的指针。

所谓的【新建对象】的意思就是，将调用该类的构造函数，因为如果不构造的话，就不能称之为一个对象。

而malloc只是机械的分配一块内存，如果用mallco在堆区创建一个对象的话，是不会调用构造函数的

```
CA *p1 = new CA;   //这里会分配内存和执行构造函数 
CA *p2 = operator new(sizeof(CA));   //这里只是执行了普通的堆内存分配而不会调用构造函数 
```

| 特征                 | new/delete                            | malloc/free                          |
| -------------------- | ------------------------------------- | ------------------------------------ |
| 分配内存的位置       | 自由存储区                            | 堆                                   |
| 内存分配成功的返回值 | 完整类型指针                          | void*                                |
| 内存分配失败的返回值 | 默认抛出异常                          | 返回NULL                             |
| 分配内存的大小       | 由编译器根据类型计算得出              | 必须显式指定字节数                   |
| 处理数组             | 有处理数组的new版本new[]              | 需要用户计算数组的大小后进行内存分配 |
| 已分配内存的扩充     | 无法直观地处理                        | 使用realloc简单完成                  |
| 是否相互调用         | 可以，看具体的operator new/delete实现 | 不可调用new                          |
| 分配内存时内存不足   | 客户能够指定处理函数或重新制定分配器  | 无法通过用户代码进行处理             |
| 函数重载             | 允许                                  | 不允许                               |
| 构造函数与析构函数   | 调用                                  | 不调用                               |

# 8. 实现 new 和 delete

事实上，当使用 malloc/new/new[] 申请了一块内存的时候，编译器实际上会在这块内存的头部保存一个 size_t 信息，记录了这块内存的大小。这个size信息是需要占用额外的空间的



在对 p 指针进行free/delete/delete []操作的时候，实际上会先通过 *(p-sizeof(size_t))来获得这块内存的大小，然后将内存归还给系统。从这一步上来说，free，delete，delete [] 没有任何区别——也就是说，对于下面的两行代码：