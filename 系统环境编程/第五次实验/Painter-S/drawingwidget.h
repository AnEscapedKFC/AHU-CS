// #ifndef DRAWINGWIDGET_H
// #define DRAWINGWIDGET_H

// #include <QWidget>
// #include <QPoint>
// #include <QMap>
// #include <QColor>
// #include <QSize>
// #include <QSet>

// class DrawingWidget : public QWidget
// {
//     Q_OBJECT

// public:
//     enum Shape {
//         Circle,
//         Rectangle,
//         ShapeCount // 用于计数
//     };

//     explicit DrawingWidget(QWidget *parent = nullptr);

//     // 设置指定图形的偏移量
//     void setShapeOffset(Shape shape, int deltaX, int deltaY);

//     // 获取指定图形的当前偏移量
//     QPoint getShapeOffset(Shape shape) const;

//     // 设置指定图形的颜色
//     void setShapeColor(Shape shape, const QColor &color);

//     // 获取指定图形的颜色
//     QColor getShapeColor(Shape shape) const;

//     // 激活指定图形
//     void activateShape(Shape shape);

//     // 禁用指定图形
//     void deactivateShape(Shape shape);

//     // 检查指定图形是否被激活
//     bool isShapeActive(Shape shape) const;

// protected:
//     void paintEvent(QPaintEvent *event) override;

// private:
//     QPoint initialCenter; // 绘图区域的中心点

//     // 每个图形的偏移量
//     QMap<Shape, QPoint> shapeOffsets;

//     // 每个图形的尺寸
//     QMap<Shape, QSize> shapeSizes;

//     // 每个图形的颜色
//     QMap<Shape, QColor> shapeColors;

//     // 激活的图形集合
//     QSet<Shape> activeShapes;

//     // 边界检查
//     bool withinBounds(Shape shape, int newX, int newY) const;

//     // 放大系数
//     const double scaleFactor = 1.6;
// };

// #endif // DRAWINGWIDGET_H


#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QColor>
#include <QMap>

class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget *parent = nullptr);

    enum Shape {
        Circle,
        Rectangle
    };
    Q_ENUM(Shape)

    // 设置图形的颜色
    void setShapeColor(Shape shape, const QColor &color);
    // 设置图形的偏移坐标
    void setShapeOffset(Shape shape, int offsetX, int offsetY);
    // 激活某种图形
    void activateShape(Shape shape);
    // 停用某种图形
    void deactivateShape(Shape shape);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    struct ShapeInfo {
        bool active = false;    // 是否激活
        QColor color = Qt::black;
        int offsetX = 0;
        int offsetY = 0;
    };

    QMap<Shape, ShapeInfo> m_shapeInfo;
};

#endif // DRAWINGWIDGET_H
