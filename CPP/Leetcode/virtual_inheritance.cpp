#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

class Base1 {
public:
    int base1_1;
    int base1_2;
    Base1(){}
    virtual void base1_fun1() {}
    virtual void base1_fun2() {}
};

class Base2 {
public:
    int base2_1;
    int base2_2;
    Base2(){}
    //virtual void base2_fun1() {}
    //virtual void base2_fun2() {}
};

class Derive1 : virtual public Base1
{
public:
    int derive1_1;
    int derive1_2;
    Derive1(){}
    //// 基类虚函数覆盖
    //virtual void base1_fun1() {}
    //virtual void base2_fun2() {}

    // 自身定义的虚函数
    virtual void derive1_fun1() {}
    virtual void derive1_fun2() {}
};
// 多继承
#define offsetof(s,m)   (size_t)(&reinterpret_cast<const volatile char&>((((s*)0x11)->m)) - 0x11)

int inheritance_test() {
    //A a = A();
    //cout << a.a1 << endl;
    //cout << offsetof(A, A::a1) << endl;
    //cout << offsetof(A, A::a2) << endl;
    //cout << sizeof(A) << endl;

    Derive1 d = Derive1();

    cout << sizeof(Derive1) << endl;

//    cout << offsetof(Derive1, base1_1) << endl;
//    cout << offsetof(Derive1, base1_2) << endl;
    //cout << offsetof(Derive1, Derive1::base2_1) << endl;
    //cout << offsetof(Derive1, Derive1::base2_2) << endl;
    cout<<offsetof(Derive1, derive1_1)<<endl;
    cout<<offsetof(Derive1, derive1_2)<<endl;

    int a;
    Derive1* pd1 = &d;
    a = d.base1_1;
    a = pd1->base1_1;
    pd1->base1_fun1();
    pd1->base1_fun2();
    pd1->derive1_fun1();
    pd1->derive1_fun2();
    //pd1->base2_fun1();
    //pd1->base2_fun2();

    return 0;
}