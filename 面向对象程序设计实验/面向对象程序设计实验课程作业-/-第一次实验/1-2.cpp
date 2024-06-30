#include <iostream>
using namespace std;

// 递归函数来计算 Legendre 多项式 P_n(x)
double legendre(int n, double x) {
    if (n == 0) {
        return 1.0; // P_0(x) = 1
    } else if (n == 1) {
        return x; // P_1(x) = x
    } else {
        // 递归关系 P_n(x) = ((2n - 1) * x * P_{n-1}(x) - (n - 1) * P_{n-2}(x)) / n
        return ((2.0 * n - 1.0) * x * legendre(n - 1, x) - (n - 1.0) * legendre(n - 2, x)) / n;
    }
}

int main() {
    int n;
    double x;

    cout << "请输入要计算的 Legendre 多项式的次数 n: ";
    cin >> n;
    cout << "请输入自变量 x 的值: ";
    cin >> x;

    cout << "Legendre 多项式 P_" << n << "(" << x << ") 的值是: " << legendre(n, x) << endl;

    return 0;
}
