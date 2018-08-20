前言知识

const的位置与区别

1)  const char * p  p 是一个指向常量字符的指针，不变的是 char 的值，

2)  char * const p  p 是一个指向字符的常量指针，不变的是 p 的值，即该指针不能再指向别的。

一个助记的方法——“以 * 分界，把一个声明从右向左读”。

# 1. 虚函数

内容来源 [陪她去流浪](https://blog.twofei.com/)  网址https://blog.twofei.com/496/ 

## 1.1 __vfptr是指向虚表的指针

没有虚函数的对象

```cpp
class Base1
{
public:
    int base1_1;
    int base1_2;

    void foo(){}cpp
};
```

| sizeof(Base1)            | 8    |
| ------------------------ | ---- |
| offsetof(Base1, base1_1) | 0    |
| offsetof(Base1, base1_2) | 4    |

仅有一个虚函数的类对象

```cpp
class Base1
{
public:
    int base1_1;
    int base1_2;

    virtual void base1_fun1() {}
    virtual void base1_fun2() {}
};
```

| sizeof(Base1)            | 12   |
| ------------------------ | ---- |
| offsetof(__vfptr)        | 0    |
| offsetof(Base1, base1_1) | 4    |
| offsetof(Base1, base1_2) | 8    |


 base1_1前面多了一个变量 __vfptr(常说的虚函数表vtable指针), 其类型为void**, 这说明它是一个void*指针

```cpp
// vfptr 的定义如下：
// 虚函数表
void*   __fun[1] = { &Base1::base1_fun1, &Base1::base1_fun2 };
// 指向虚函数表的定向指针
const void**  __vfptr = &__fun[0];
```

更加肯定前面我们所描述的: __vfptr只是一个指针, 她指向一个函数指针数组(即: 虚函数表)

只是简单地向该类对应的虚函数表中增加一项而已, 并不会影响到类对象的大小以及布局情况


## 1.2 同一个类的不同实例共用同一份虚函数表
她们都通过一个虚函数表指针__vfptr(定义为void\*\*类型)指向该虚函数表.
e.g. 定义两个类的实例 b1, b2 

![img](../img/CPP基础知识/4-4.png)

## 1.3 虚函数表的位置

1. 编译器在**编译时期**自动创建好的, 只存在一份
2. 定义类对象时, 编译器自动将类对象的__vfptr指向这个虚函数表

## 1.4 单继承

### 1.4.1 单继承且本身不含虚函数的继承类

```cpp
class Base1
{
public:
    int base1_1;
    int base1_2;

    virtual void base1_fun1() {}
    virtual void base1_fun2() {}
};

class Derive1 : public Base1
{
public:
    int derive1_1;
    int derive1_2;
};
```

内存布局

![img](../img/CPP基础知识/5-3.png)

### 1.4.2 单继承且只有继承而得来的基类虚函数的继承类

除经过继承而得来的基类虚函数以外, 自身没有再定义其它的虚函数.

```cpp
class Base1
{
public:
    int base1_1;
    int base1_2;

    virtual void base1_fun1() {}
    virtual void base1_fun2() {}
};

class Derive1 : public Base1
{
public:
    int derive1_1;
    int derive1_2;

    // 覆盖基类函数
    virtual void base1_fun1() {}
};
```

内存布局

![img](../img/CPP基础知识/5-3.png)

无论是通过Derive1的指针还是Base1的指针来调用此方法, 调用的都将是被继承类重写后的那个方法(函数), 

多态!!!

### 1.4.3 定义了基类没有的虚函数的单继承的类对象布局 

```cpp
class Base1
{
public:
    int base1_1;
    int base1_2;

    virtual void base1_fun1() {}
    virtual void base1_fun2() {}
};

class Derive1 : public Base1
{
public:
    int derive1_1;
    int derive1_2;

    virtual void derive1_fun1() {}
}; 
```

理论上多了一个自身定义的虚函数. 但是vs中却无法跟踪

![img](../img/CPP基础知识/7-1.png)

利用汇编来追踪

```
Derive1 d1;
Derive1* pd1 = &d1;
// d1.derivel_fun1()
pd1->derive1_fun1();
```

```asm
; pd1->derive1_fun1();
00825466  mov         eax,dword ptr [pd1]  ;由于pd1是指向d1的指针
;__vfptr是Base1的第1个成员,edx就得到了__vfptr的值, 也就是虚函数表的地址
00825469  mov         edx,dword ptr [eax]  
0082546B  mov         esi,esp  
;由于是__thiscall调用, 所以把this保存到ecx中.
0082546D  mov         ecx,dword ptr [pd1]  
;由于edx是虚函数表的地址, 那么 edx+8将是虚函数表的第3个元素, 也就是__vftable[2]!!!
00825470  mov         eax,dword ptr [edx+8]  
;第7行: 调用虚函数.
00825473  call        eax
```

1. 由于Base1只知道自己的两个虚函数索引[0][1], 所以就算在后面加上了[2], Base1根本不知情, 不会对她造成任何影响.
2. 如果**基类没有虚函数**呢? 这个问题我们留到第9小节再来讨论!

![img](../img/CPP基础知识/7-3.png)

### 1.4.4多继承且存在虚函数覆盖又自身定义的虚函数的类对象布局

```cpp
class Base1
{
public:
    int base1_1;
    int base1_2;

    virtual void base1_fun1() {}
    virtual void base1_fun2() {}
};

class Base2
{
public:
    int base2_1;
    int base2_2;

    virtual void base2_fun1() {}
    virtual void base2_fun2() {}
};

// 多继承
class Derive1 : public Base1, public Base2
{
public:
    int derive1_1;
    int derive1_2;

    // 基类虚函数覆盖
    virtual void base1_fun1() {}
    virtual void base2_fun2() {}

    // 自身定义的虚函数
    virtual void derive1_fun1() {}
    virtual void derive1_fun2() {}
};
```

初步了解一下对象大小及偏移信息:

![img](../img/CPP基础知识/8-1.png)

貌似, 若有所思? 不管, 来看看VS再想:

![img](../img/CPP基础知识/8-2.png)

结论:

1. 按照基类的声明顺序, 基类的成员依次分布在继承中.
2. 注意被我高亮的那两行, 已经发生了虚函数覆盖!

**我们自己定义的虚函数呢? **怎么还是看不见?!  好吧, 继承反汇编, 这次的调用代码如下:

```cpp
Derive1 d1;
Derive1* pd1 = &d1;
pd1->derive1_fun2();
```

```asm
; pd1->derive1_fun2();
00995306  mov         eax,dword ptr [pd1]  
00995309  mov         edx,dword ptr [eax]  
0099530B  mov         esi,esp  
0099530D  mov         ecx,dword ptr [pd1]  
00995310  mov         eax,dword ptr [edx+0Ch]  
00995313  call        eax
```

**Derive1的虚函数表依然是保存到第1个拥有虚函数表的那个基类的后面的.**

![img](../img/CPP基础知识/8-3.png)

### 1.4.5 多继承，但是基类没有虚函数，自己定义虚函数的

去掉1.4.4 中base1 中的虚函数。

```
class Base1
{
public:
    int base1_1;
    int base1_2;
};

class Base2
{
public:
    int base2_1;
    int base2_2;

    virtual void base2_fun1() {}
    virtual void base2_fun2() {}
};

// 多继承
class Derive1 : public Base1, public Base2
{
public:
    int derive1_1;
    int derive1_2;

    // 自身定义的虚函数
    virtual void derive1_fun1() {}
    virtual void derive1_fun2() {}
};
```

来看看VS的布局:

![img](../img/CPP基础知识/9-1.png)

现在的大小及偏移情况: 注意: `sizeof(Base1) == 8;`

![img](../img/CPP%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86/9-2.png)

重点是看虚函数的位置, 进入函数调用(和前一次是一样的):

 那么问题就来了! Base1 已经没有虚函数表了, 为什么还是把b1的第1个元素当作__vfptr呢? 不难猜测: 当前的布局已经发生了变化, 有虚函数表的基类放在对象内存前面!? , 不过事实是否属实? 需要仔细斟酌.

我们可以通过对基类成员变量求偏移来观察:

![img](../img/CPP%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86/9-3.png)

可以看到:

```
&d1==0x~d4
&d1.Base1::__vfptr==0x~d4
&d1.base2_1==0x~d8
&d1.base2_2==0x~dc
&d1.base1_1==0x~e0
&d1.base1_2==0x~e4
```

所以不难验证: 我们前面的推断是正确的, **谁有虚函数表, 谁就放在前面!**

现在类的布局情况:

![img](../img/CPP%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86/9-4.png)

那么, 如果两个基类都没有虚函数表呢?

```
class Base1
{
public:
    int base1_1;
    int base1_2;
};

class Base2
{
public:
    int base2_1;
    int base2_2;
};

// 多继承
class Derive1 : public Base1, public Base2
{
public:
    int derive1_1;
    int derive1_2;

    // 自身定义的虚函数
    virtual void derive1_fun1() {}
    virtual void derive1_fun2() {}
};
```

前面吃了个亏, 现在先来看看VS的基本布局:

![img](../img/CPP%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86/10-1.png)

可以看到, 现在__vfptr已经独立出来了, 不再属于Base1和Base2!

看看求偏移情况:

![img](../img/CPP%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86/10-2.png)

注意高亮的那两行, `&d1==&d1.__vfptr`, 说明虚函数始终在最前面!

对象布局:

![img](../img/CPP基础知识/10-3.png)

### 1.4.6 如果有三个基类: 虚函数表分别是有, 没有, 有!

只需要看看偏移就行了:

![img](../img/CPP%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86/11-1.png)

只需知道: 谁有虚函数表, 谁就往前靠!

## 1.5 C++中父子对象指针间的转换与函数调用

由于继承完全拥有父类的所有, 包括数据成员与虚函数表, 

所以:**把一个继承类强制转换为一个基类**是完全可行的.

如果有 :Derive1 *pd1 = new Derive1()

- 得到Base1的指针: Base1* pb1 = pd1;
- 得到Base2的指针: Base2* pb2 = pd1;
- 得到Base3的指针: Base3* pb3 = pd1;

非常值得注意的是:

这是在基类与继承类之间的转换, 这种转换会自动计算偏移! 按照前面的布局方式!
也就是说: 在这里极有可能: pb1 != pb2 != pb3 ~~, 不要以为她们都等于 pd1!

至于函数调用, 我想, 不用说大家应该知道了:

1. 如果不是虚函数, 直接调用指针对应的基本类的那个函数
2. 如果是虚函数, 则查找虚函数表, 并进行后续的调用. 虚函数表在定义一个时, 编译器就为我们创建好了的. 所有的, 同一个类, 共用同一份虚函数表.

## 1.6 抽象类

抽象类是一种特殊的类，它是为了抽象和设计的目的为建立的，它处于继承层次结构的较上层。

### 1.6.1 抽象类的定义：

称带有纯虚函数的类为抽象类。

### 1.6.2 抽象类的作用

抽象类的主要作用是将有关的操作作为结果接口组织在一个继承层次结构中，由它来为派生类提供一个公共的根，派生类将具体实现在其基类中作为接口的操作。所以派生类实际上刻画了一组子类的操作接口的通用语义，这些语义也传给子类，子类可以具体实现这些语义，也可以再将这些语义传给自己的子类。

## 1.7 虚函数与多态

### 1.7.1 基础知识

声明虚函数的目的在于，使派生类继承函数的接口和缺省实现。

1. 纯虚函数声明如下： virtual void funtion1()=0;

2. 纯虚函数一定没有定义，纯虚函数用来规范派生类的行为，即接口。包含纯虚函数的类是抽象类，抽象类不能定义实例，但可以声明指向实现该抽象类的具体类的指针或引用。

3. 定义他为虚函数是为了允许用基类的指针来调用子类的这个函数。 

4. 对于虚函数来说，父类和子类都有各自的版本。由多态方式调用的时候动态绑定。

   实例一旦绑定无法通过向上、向下转型修改调用的函数。而普通函数可以转换。

   ```cpp
   class A{
   public:
       void foo(){
           printf("1\n");
       }
       virtual void fuu(){
           printf("2\n");    
       }
   };
   
   class B:public A{
   public :
       void foo(){
           printf("3\n");
       }
       void fuu(){
           printf("4\n");
       }
   };
   int main(){
       A a;
       B b;
       A *p = &a;
       cout<< "p->foo()---" ; p->foo() ; 
       cout<<"p->fuu()---";p->fuu();    
       cout <<"-------向上转型-----------"<<endl;
       p=&b;
       cout<<"p->foo()---";p->foo();    
       cout<<"p->fuu()---";p->fuu();    
       cout <<"--------向下转型----------"<<endl;
       B *ptr =(B *)&a;
       cout<<"ptr->foo()----";ptr->foo();
       cout<<"ptr->fuu()-----";ptr->fuu();
       return 0;
   }
   ```

   ![img](../img/virtual_func.png)

   

5. 实现了纯虚函数的子类，该纯虚函数在子类中就编程了虚函数，子类的子类即孙子类可以覆盖该虚函数，由多态方式调用的时候动态绑定。

6. 虚函数是C++中用于实现多态(polymorphism)的机制。核心理念就是通过基类访问派生类定义的函数。

7. 友元不是成员函数，只有成员函数才可以是虚拟的，因此友元不能是虚拟函数。但可以通过让友元函数调用虚拟成员函数来解决友元的虚拟问题。

8. 在有动态分配堆上内存的时候，析构函数必须是虚函数，但没有必要是纯虚的。析构函数应当是虚函数，将调用相应对象类型的析构函数，因此，如果指针指向的是子类对象，将调用子类的析构函数，然后自动调用基类的析构函数。

### 1.7.2 关于重载虚函数的两个常见错误

#### 1.7.2.1 无意中重载

你可能只是通过声明了一个与基类的某个虚成员函数具有相同的名字和签名的成员函数而无意中重载了这个虚函数。

```cpp
struct A
{ 

virtual void func();
};             
struct B: A{};
struct F{};
struct D: A, F
{
  void func();//meant to declare a new function but 

 //accidentally overrides A::func};
```

#### 1.7.2.2 签名不匹配

这种情况下，程序员本打算在类H中重载G::func()的。然而，由于H::func()拥有不同的签名，结果创建了一个新的虚函数，而非对基类函数的重载：

```cpp
struct G{
 virtual void func(int);
};
struct H: G {
 virtual void func(double); //accidentally creates a new virtual function
};
```

我们来看看override如何消除签名不匹配bug的：

```cpp
struct G{
 virtual void func(int);
};
struct H: G{
 virtual void func(double) override; //compilation error
};
```

当处理到H::func()声明时，编译器会 

在一个基类

查找与之匹配的虚函数。回想一下，“匹配”在上下文中的意思是：

- 相同的函数名
- 在声明该函数的第一个基类中的一个虚拟说明符
- 基类函数和派生类重载函数具有相同的参数列表、返回类型（一种情况例外）、cv资格等。

如果这三个条件中任意一个不满足，编译器就会报错。

### 1.7.3 final 禁止继承 

C++11的关键字final有两个用途。第一，它阻止了从类继承；第二，阻止一个虚函数的重载。

override和final不是普通关键字。事实上官方地说，它们根本不是关键字。C++11把它们作为只是为了在特定上下文和位置下获取特殊意义的标示符。在任何其他位置或上下文，它们都被当成标示符。



# 2 强制转换

## 2.1 const_cast

1、常量指针被转化成非常量的指针，并且仍然指向原来的对象； 
2、常量引用被转换成非常量的引用，并且仍然指向原来的对象； 
3、const_cast一般用于修改指针。如const char *p形式。

```cpp
ostream& operator<<(ostream& out, const vector<int> arr){
    for(auto it = arr.begin(); it!=arr.end(); it++){
        out<<(*it)<<' ';
    }
    return out;
}
int main(){
    vector<int> arr = {1,2,3,4};
    const vector<int> *ptr = &arr;
    // (*ptr)[0] = 12; compilation error 
    cout<<*ptr<<endl;
    //用 const_cast<> 取消const约束
    vector<int> *what = const_cast< vector<int>* >(ptr);
    (*what)[0] =10;
    cout<<*ptr<<endl;
    return 0;
}
```

对于 const int a=10 这样的常量，不同的编译器有不同的效果。可能改变也可能不变。

运行环境： CLion-GUN 4.8.5， 也可用volatile禁止编译器优化，强制读取地址中内容。

```cpp
int main(){
    const int a = 10;
    int *p = const_cast< int* >(&a);
    int &r = const_cast< int& >(a);
    cout<<a<<' '<<*p <<' '<< r<<endl;
    (*p) = 2;
    cout<<a<<' '<<*p <<' '<< r<<endl;
    r = 3;
    cout<<a<<' '<<*p <<' '<< r<<endl;
    return 0;
}
```

```
10 10 10
10 2 2
10 3 3
```

## 2.2 static_cast

1. static_cast 作用和C语言风格强制转换的效果基本一样，由于没有运行时类型检查来保证转换的安全性，所以这类型的强制转换和C语言风格的强制转换都有安全隐患。
2. 用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换。注意：进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。
3. 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性需要开发者来维护。
4. static_cast不能转换掉原有类型的const、volatile、或者 __unaligned属性。(前两种可以使用const_cast 来去除)
5. 在c++ primer 中说道：c++ 的任何的隐式转换都是使用 *static_cast* 来实现。

```cpp
/* 常规的使用方法 */
float f_pi=3.141592f
int   i_pi=static_cast<int>(f_pi); /// i_pi 的值为 3
/* class 的上下行转换 */
class Base{
    // something
};
class Sub:public Base{
    // something
}

//  上行 Sub -> Base
//编译通过，安全
Sub sub;
Base *base_ptr = static_cast<Base*>(&sub);  

//  下行 Base -> Sub
//编译通过，不安全
Base base;
Sub *sub_ptr = static_cast<Sub*>(&base);  
```

## 2.3 dynamic_cast

*dynamic_cast*强制转换,应该是这四种中最特殊的一个,因为他涉及到面向对象的多态性和程序运行时的状态,也与编译器的属性设置有关.所以不能完全使用C语言的强制转换替代,它也是最常有用的,最不可缺少的一种强制转换.

1. 虚函数经过子类重写后，绑定，上转型指向不变。

2. 下转型编译通过，但是如下例所示，一旦出现override 并且父类dynamic_cast 

   运行过程中找不到函数地址而报错。

```
int main(){
    A a;
    B b;
    A *p = &a;
    cout<< "p->foo()---" ; p->foo() ;
    cout<<"p->fuu()---";p->fuu();
    cout <<"-------向上转型-----------"<<endl;
    p=&b;
    cout<<"p->foo()---";p->foo();
    cout<<"p->fuu()---";p->fuu();
    cout <<"---向上转型(dynamic_cast)---"<<endl;
    p= dynamic_cast<A*> (&b);
    cout<<"p->foo()---";p->foo();
    cout<<"p->fuu()---";p->fuu();
    cout <<"--------向下转型----------"<<endl;
    B *ptr =(B *)&a;
    cout<<"ptr->foo()----";ptr->foo();
    cout<<"ptr->fuu()-----";ptr->fuu();
    cout <<"---向下转型(dynamic_cast)---"<<endl;
    ptr =dynamic_cast<B *>(&a);
    cout<<"ptr->foo()----";ptr->foo();
    //cout<<"ptr->fuu()-----";ptr->fuu(); runtime error
    return 0;
}
```

```
p->foo()---1
p->fuu()---2
-------向上转型-----------
p->foo()---1
p->fuu()---4
---向上转型(dynamic_cast)---
p->foo()---1
p->fuu()---4
--------向下转型----------
ptr->foo()----3
ptr->fuu()-----2
---向下转型(dynamic_cast)---
ptr->foo()----3
```

## 2.4 reinterpret_cast

reinterpret_cast是强制类型转换符用来处理无关类型转换的，通常为操作数的位模式提供较低层次的重新解释！但是他仅仅是**重新解释了给出的对象的比特模型**，并没有进行二进制的转换！  他是用在任意的指针之间的转换，引用之间的转换，指针和足够大的int型之间的转换，整数到指针的转换，在在面的文章中将给出. 

```cpp
int main() {
    int *ptr = new int(233);
    // 将地址重新解释为 uint64_t 类型的整数
    uint64_t ptr_addr = reinterpret_cast<uint64_t>(ptr);
    cout << "ptr 的地址: " << ptr << endl
         << "ptr_addr 的值(hex): " << hex << ptr_addr << endl;
    delete ptr;
    return 0;
}
/*
ptr 的地址: 0xffbe70
ptr_addr 的值(hex): ffbe70
*/
```

适用情况

1. 指针转向足够大的整数类型
2. 从整形或者enum枚举类型转换为指针
3. 从指向函数的指针转向另一个不同类型的指向函数的指针
4. 从一个指向成员的指针转向另一个指向类成员的指针！或者是类型

```cpp
// expre_reinterpret_cast_Operator.cpp   哈希函数辅助
// compile with: /EHsc  
#include <iostream>  

// Returns a hash code based on an address  
uint_64_t short Hash(void *p) {
    uint64_t val = reinterpret_cast<uint64_t>(p);
    return (unsigned short)(val ^ (val >> 16));
}
using namespace std;
int main() {
    int a[20];
    for (int i = 0; i < 20; i++)
        cout << Hash(a + i) << endl;
}
```

# 3 三种访问权限和三种继承

## 3.1 三种访问权限 

| 访问权限       | public | protected | private |
| -------------- | ------ | --------- | ------- |
| 对本类         | 可见   | 可见      | 可见    |
| 对子类         | 可见   | 可见      | 不可见  |
| 对外部(调用方) | 可见   | 不可见    | 不可见  |

## 3.2 三种继承 

1. 三种继承方式不影响子类对父类的访问权限，子类对父类只看父类的访问控制权
2. public、protected、private三种继承方式，相当于把父类的public访问权限在子类中变成了对应的权限。 如protected继承，把父类中的public成员在本类中变成了protected的访问控制权限；private继承，把父类的public成员和protected成员在本类中变成了private访问控制权。

```
class Person {
public:
    Person(const string& name, int age) : m_name(name), m_age(age) {}
    void ShowInfo() {
        cout << "姓名：" << m_name << endl;
        cout << "年龄：" << m_age << endl;
    }
protected:
    string  m_name;     //姓名
private:
    int     m_age;      //年龄
};

class Teacher : public Person{
public:
    Teacher(const string& name, int age, const string& title)
            : Person(name, age), m_title(title){}

    void ShowTeacherInfo(){
        ShowInfo();                             //正确，public属性子类可见
        cout << "姓名：" << m_name << endl;        //正确，protected属性子类可见
        //cout << "年龄：" << m_age << endl;     //错误，private属性子类不可见
        cout << "职称：" << m_title << endl;   //正确，本类中可见自己的所有成员
    }
private:
    string  m_title;        //职称
};
int main(){
    Teacher t("张三", 22,"讲师");
    t.ShowInfo();                  //public属性,对外部可见
    //cout << t.m_name << endl;      //protected属性,对外部不可见
    //cout << t.m_age << endl;       //private属性,对外部不可见
}
```

改为  protect

```
class Teacher : protect Person{
public:
    Teacher(const string& name, int age, const string& title)
            : Person(name, age), m_title(title){}

    void ShowTeacherInfo(){
        ShowInfo();                             //正确，父类public->protected 子类可见
        cout << "姓名：" << m_name << endl;        //正确，protected属性子类可见
        //cout << "年龄：" << m_age << endl;     //错误，private属性子类不可见
        cout << "职称：" << m_title << endl;   //正确，本类中可见自己的所有成员
    }
private:
    string  m_title;        //职称
};
int main(){
    Teacher t("张三", 22,"讲师");
    //t.ShowInfo();                  //protect属性,对外部不可见
    //cout << t.m_name << endl;      //protected属性,对外部不可见
    //cout << t.m_age << endl;       //private属性,对外部不可见
}
```







