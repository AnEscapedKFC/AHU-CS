#include <iostream>
using namespace std;

class Complex {
private:
    double real; // 实部
    double imag; // 虚部
public:
    //使用函数重载，声明三个构造函数
    Complex(double r, double i);
    Complex(double r);
    Complex();
	~Complex(){
		cout<<"析构函数被调用"<<endl;
	}
    void add(Complex& other);
    void show();
};

//成员函数的实现
Complex::Complex(double r,double i):real(r),imag(i){}
Complex::Complex(double r):real(r),imag(0.00){}
Complex::Complex():real(0.00),imag(0.00){}
void Complex::add(Complex &c) {
    real += c.real;
    imag += c.imag;
    //!类的成员函数可以访问同一类的其他对象的私有成员!
}
void Complex::show() {
    cout << real << " + " << imag << "i" << endl;
}

int main() {
    Complex c1(3, 5);  // 用复数 3 + 5i 初始化 c1
    Complex c2 = 4.5;  // 用实数 4.5 初始化 c2
    c1.add(c2);  // 将 c1 与 c2 相加，结果保存在 c1 中
    c1.show();   // 输出 c1 (结果应该是 7.5 + 5i)
    return 0;
}

