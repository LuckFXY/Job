#include <iostream>
#include <vector>
using namespace std;
class A{
public:
	int a1 = 1;
	int a2 = 2;

	virtual void a_fun1() {
		cout << "a1" << endl;
	}
	virtual void a_fun2() {
		cout << "a2" << endl;
	}
};

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
	int base2_1=1;
	int base2_2;

	//virtual void base2_fun1() {}
	//virtual void base2_fun2() {}
};

class Derive1 : virtual public Base1
{
public:
	int derive1_1;
	int derive1_2;

	//// 基类虚函数覆盖
	//virtual void base1_fun1() {}
	//virtual void base2_fun2() {}

	// 自身定义的虚函数
	virtual void derive1_fun1() {}
	virtual void derive1_fun2() {}
};
// 多继承

uint32_t my_offset(void* a, void* b) {

	uint32_t n1 = reinterpret_cast<uint32_t>(a);
	uint32_t n2 = reinterpret_cast<uint32_t>(b);
	return (n1 - n2);
}
int main() {
	//A a = A();
	//cout << a.a1 << endl;
	//cout << offsetof(A, A::a1) << endl;
	//cout << offsetof(A, A::a2) << endl;
	//cout << sizeof(A) << endl;
	
	Derive1 d = Derive1();
	int a;
	cout << sizeof(Derive1) << endl;
	//cout << offsetof(Derive1, Derive1::base1_1) << endl;
	//cout << offsetof(Derive1, Derive1::base1_2) << endl;
	//cout << offsetof(Derive1, Derive1::base2_1) << endl;
	//cout << offsetof(Derive1, Derive1::base2_2) << endl;
	cout << offsetof(Derive1, Derive1::derive1_1) << endl;
	cout << offsetof(Derive1, Derive1::derive1_2) << endl;
	
	Derive1* pd1 = &d;
	a = d.base1_1;
	cout << a << endl;
	a = pd1->base1_1;
	cout << a << endl;
	pd1->base1_fun1();
	pd1->base1_fun2();
	pd1->derive1_fun1();
	pd1->derive1_fun2();
	//pd1->base2_fun1();
	//pd1->base2_fun2();


	return 0;
}