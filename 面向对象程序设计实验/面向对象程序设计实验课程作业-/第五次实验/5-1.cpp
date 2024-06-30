#include <iostream>
class Object {
protected:
    double weight;

public:
    // 构造函数
    Object(double w) : weight(w) {
        std::cout << "Object 构造函数被调用，重量: " << weight << std::endl;
    }

    // 析构函数
    virtual ~Object() {
        std::cout << "Object 析构函数被调用" << std::endl;
    }

    // 设置重量
    void setWeight(double w) {
        weight = w;
    }

    // 获取重量
    double getWeight() const {
        return weight;
    }
};

class Box : public Object {
private:
    double height;
    double width;

public:
    // 构造函数
    Box(double w, double h, double wd) : Object(w), height(h), width(wd) {
        std::cout << "Box 构造函数被调用，高度: " << height << "，宽度: " << width << std::endl;
    }

    // 析构函数
    ~Box() {
        std::cout << "Box 析构函数被调用" << std::endl;
    }

    // 设置高度
    void setHeight(double h) {
        height = h;
    }

    // 获取高度
    double getHeight() const {
        return height;
    }

    // 设置宽度
    void setWidth(double wd) {
        width = wd;
    }

    // 获取宽度
    double getWidth() const {
        return width;
    }
};

int main() {
    Box myBox(10.5, 5.0, 3.0);
    std::cout << "Box 对象已创建，重量: " << myBox.getWeight() << "，高度: " << myBox.getHeight() << "，宽度: " << myBox.getWidth() << std::endl;
    return 0;
}
