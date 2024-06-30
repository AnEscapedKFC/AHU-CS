
#include <iostream>

using namespace std;

class Counter {
public:
    Counter(int cnt = 0) : cnt(cnt) {} // 允许进行隐式转换，所以不用explicit标记
    friend Counter operator+(const Counter& c1, const Counter& c2);

private:
    int cnt;
};

Counter operator+(const Counter& c1, const Counter& c2) {
    return { c1.cnt + c2.cnt }; // 为避免重复声明返回类型，这里返回初始化列表而非临时无名对象
}

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual double getPerim() const = 0;
    virtual int getVertexCount() const = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double len, double w) : length(len), width(w) {}
    Rectangle() : length(0.0), width(0.0) {}

    double getArea() const override { return length * width; }
    double getPerim() const override { return 2 * (length + width); }
    int getVertexCount() const override;

private:
    double length;
    double width;
};

int Rectangle::getVertexCount() const {
    return 4;
}

const double PI = 3.1415926;

class Circle : public Shape {
public:
    explicit Circle(double r = 2.0) : radius(r) {}

    double getArea() const override { return PI * radius * radius; }
    double getPerim() const override { return 2 * PI * radius; }
    int getVertexCount() const override;

private:
    double radius;
};

int Circle::getVertexCount() const {
    return 0;
}

class Square : public Rectangle {
public:
    explicit Square(double a = 0.0) : Rectangle(a, a) {}

    int getVertexCount() const override;
};

int Square::getVertexCount() const {
    return 4;
}

int getVertexCount1(Shape* shape) {
    auto* rectangle = dynamic_cast<Rectangle*>(shape);
    if (rectangle) return rectangle->getVertexCount();
    auto* square = dynamic_cast<Square*>(shape);
    if (square) return square->getVertexCount();
    auto* circle = dynamic_cast<Circle*>(shape);
    if (circle) return circle->getVertexCount();
    return -1;
}

int getVertexCount2(Shape* shape) {
    if (typeid(*shape) == typeid(Rectangle))
        return dynamic_cast<Rectangle*>(shape)->getVertexCount();
    else if (typeid(*shape) == typeid(Square))
        return dynamic_cast<Square*>(shape)->getVertexCount();
    else if (typeid(*shape) == typeid(Circle))
        return dynamic_cast<Circle*>(shape)->getVertexCount();
    else
        return -1;
}

int getVertexCount3(Shape* shape) {
    return shape->getVertexCount();
}

class Point {
public:
    explicit Point(double xx = 0, double yy = 0) { // 构造函数
        x = xx;
        y = yy;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    Point& operator++(); // 前置++
    Point operator++(int); // 后置++
    Point& operator--();
    Point operator--(int);

    friend ostream& operator<<(ostream& out, const Point& p);
    friend Point operator+(const Point& p1, const Point& p2);

private:
    double x, y;
};

Point& Point::operator++() {
    x++;
    y++;
    return *this;
}

Point Point::operator++(int) {
    Point old = *this;
    ++(*this);
    return old;
}

Point& Point::operator--() {
    x--;
    y--;
    return *this;
}

Point Point::operator--(int) {
    Point old = *this;
    --(*this);
    return old;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

Point operator+(const Point& p1, const Point& p2) {
    return Point(p1.x + p2.x, p1.y + p2.y);
}

class BaseClass {
public:
    virtual void fn1() const;
    void fn2() const {
        cout << "BaseClass::fn2()" << endl;
    }
};

void BaseClass::fn1() const {
    cout << "BaseClass::fn1()" << endl;
}

class DerivedClass : public BaseClass {
public:
    void fn1() const override;
    void fn2() const {
        cout << "DerivedClass::fn2()" << endl;
    }
};

void DerivedClass::fn1() const {
    cout << "DerivedClass::fn1()" << endl;
}

void printShapeDetails(const Shape& shape) {
    cout << "Area: " << shape.getArea() << endl;
    cout << "Perimeter: " << shape.getPerim() << endl;
    cout << "Vertex Count: " << shape.getVertexCount() << endl;
}

int main() {
    Rectangle r(3.0, 4.0);
    cout << "Rectangle details:" << endl;
    printShapeDetails(r);
    cout << endl;

    Circle c(5.0);
    cout << "Circle details:" << endl;
    printShapeDetails(c);
    cout << endl;

    Square s(4.0);
    cout << "Square details:" << endl;
    printShapeDetails(s);
    cout << endl;

    return 0;
}
