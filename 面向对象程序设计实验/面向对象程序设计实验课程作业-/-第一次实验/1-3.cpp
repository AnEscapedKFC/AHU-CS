#include <iostream>
using namespace std;

// 整型版本的 getPower 函数，当 y < 0 时，返回 0
int getPower(int x, int y) {
    if (y < 0) {
        return 0;
    }
    if (y == 0) {
        return 1;
    }
    return x * getPower(x, y - 1);
}

// 实型版本的 getPower 函数
double getPower(double x, int y) {
    if (y == 0) {
        return 1.0;
    }
    if (y > 0) {
        return x * getPower(x, y - 1);
    }
    // 当 y < 0 时，计算 x 的负指数次方
    return 1.0 / getPower(x, -y);
}

int main() {
    int a, m;
    double b;

    cout << "请输入一个整数 a 作为底数: ";
    cin >> a;
    cout << "请输入一个实数 b 作为底数: ";
    cin >> b;
    cout << "请输入一个整数 m 作为指数: ";
    cin >> m;

    // 调用整型版本的 getPower
    int resultInt = getPower(a, m);
    cout << "a^m (整型版本) = " << resultInt << endl;

    // 调用实型版本的 getPower
    double resultDouble = getPower(b, m);
    cout << "b^m (实型版本) = " << resultDouble << endl;

    // 为了得到一个实型结果，使用实型版本的 getPower 计算 a^m
    double resultIntAsDouble = getPower(static_cast<double>(a), m);
    cout << "a^m (实型结果) = " << resultIntAsDouble << endl;

    return 0;
}
