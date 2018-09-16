
//
// Created by Administrator on 2018/9/15.
//

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