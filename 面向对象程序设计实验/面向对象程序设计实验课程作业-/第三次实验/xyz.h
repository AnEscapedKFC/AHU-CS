#include<iostream>
using namespace std;
//另外建一个名为xyz.h的头文件

#ifndef XYZ_H
#define XYZ_H

class X;
class Y
{
public:
    void g(X* p);

};
class Z
{
public:
    void f(X* p);

};

class X
{
public:
    X() :i(0) {}
    friend void Y::g(X* p);
    friend class Z;
    friend void h(X* p);
    void show()
    {
        cout << i << endl;
    }
private:
    int i;
};

void Y::g(X* p)
{
    p->i++;
}

void Z::f(X* p)
{
    p->i += 5;
}

void h(X* p)
{
    p->i += 10;
}

#endif // XYZ_H