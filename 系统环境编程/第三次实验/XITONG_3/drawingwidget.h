
#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMap>

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    enum Shape {
        YellowCircle,
        RedRectangle,
        GreenRectangle,
        DeepBlueRectangle,
        LightBlueCircle,
        ShapeCount // 用于计数
    };

    explicit DrawingWidget(QWidget *parent = nullptr);

    // 设置指定图形的偏移量
    void setShapeOffset(Shape shape, int deltaX, int deltaY);

    // 获取指定图形的当前偏移量
    QPoint getShapeOffset(Shape shape) const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPoint initialCenter; // 绘图区域的中心点

    // 每个图形的偏移量
    QMap<Shape, QPoint> shapeOffsets;

    // 每个图形的尺寸
    QMap<Shape, QSize> shapeSizes;

    // 边界检查
    bool withinBounds(Shape shape, int newX, int newY) const;

    // 放大系数
    const double scaleFactor = 1.6;
};

#endif // DRAWINGWIDGET_H
