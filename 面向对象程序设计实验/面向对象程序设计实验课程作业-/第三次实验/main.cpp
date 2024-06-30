//mainÎÄ¼þ
#include<iostream>
using namespace std;
#include"xyz.h"
int main()
{
    X d;
    d.show();

    Y d1;
    d1.g(&d);
    d.show();

    Z d2;
    d2.f(&d);
    d.show();

    h(&d);
    d.show();

    return 0;
}