#include <iostream>

class BaseClass {
public:
    // 基类成员函数
    void fn1() {
        std::cout << "调用基类的 fn1()" << std::endl;
    }

    void fn2() {
        std::cout << "调用基类的 fn2()" << std::endl;
    }
};

class DerivedClass : public BaseClass {
public:
    // 派生类成员函数
    void fn1() {
        std::cout << "调用派生类的 fn1()" << std::endl;
    }

    void fn2() {
        std::cout << "调用派生类的 fn2()" << std::endl;
    }
};

int main() {
    // 声明一个 DerivedClass 对象
    DerivedClass derivedObj;

    // 使用 DerivedClass 对象调用成员函数
    std::cout << "使用 DerivedClass 对象调用成员函数:" << std::endl;
    derivedObj.fn1();
    derivedObj.fn2();

    // 使用 BaseClass 指针调用成员函数
    std::cout << "使用 BaseClass 指针调用成员函数:" << std::endl;
    BaseClass* basePtr = &derivedObj;
    basePtr->fn1();
    basePtr->fn2();

    // 使用 DerivedClass 指针调用成员函数
    std::cout << "使用 DerivedClass 指针调用成员函数:" << std::endl;
    DerivedClass* derivedPtr = &derivedObj;
    derivedPtr->fn1();
    derivedPtr->fn2();

    return 0;
}
