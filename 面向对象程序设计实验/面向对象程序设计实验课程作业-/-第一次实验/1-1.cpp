#include <iostream>
using namespace std;

// 递归函数来计算 Fibonacci 数
int fibonacci(int n) {
    if (n == 0) {
        return 0; // 第 0 位的 Fibonacci 数
    } else if (n == 1) {
        return 1; // 第 1 位的 Fibonacci 数
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n;
    cout << "请输入要计算的 Fibonacci 数列的位置: ";
    cin >> n;

    if (n < 0) {
        cout << "位置不能是负数" << endl;
    } else {
        cout << "Fibonacci 数列第 " << n << " 位的值是: " << fibonacci(n) << endl;
    }
    return 0;
}

