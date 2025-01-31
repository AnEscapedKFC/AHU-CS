
#include "drawingwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMap>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化图形尺寸（包含放大系数）
    //QSize：包含宽高两个成员
    shapeSizes[YellowCircle] = QSize(static_cast<int>(200 * scaleFactor), static_cast<int>(200 * scaleFactor));
    shapeSizes[RedRectangle] = QSize(static_cast<int>(141 * scaleFactor), static_cast<int>(141 * scaleFactor));
    shapeSizes[GreenRectangle] = QSize(static_cast<int>(119 * scaleFactor), static_cast<int>(119 * scaleFactor));
    shapeSizes[DeepBlueRectangle] = QSize(static_cast<int>(79 * scaleFactor), static_cast<int>(79 * scaleFactor));
    shapeSizes[LightBlueCircle] = QSize(static_cast<int>(79 * scaleFactor), static_cast<int>(79 * scaleFactor));

    // 初始化所有图形的偏移量为(0,0)
    for(int i = 0; i < ShapeCount; ++i)
    {
        shapeOffsets[static_cast<Shape>(i)] = QPoint(0, 0);
    }
}

void DrawingWidget::setShapeOffset(Shape shape, int deltaX, int deltaY)
{
    // 检查新位置是否在边界内
    if(withinBounds(shape, deltaX, deltaY))
    {
        shapeOffsets[shape] = QPoint(deltaX, deltaY);
        update(); // 触发重绘
    }
}

QPoint DrawingWidget::getShapeOffset(Shape shape) const
{
    return shapeOffsets.value(shape, QPoint(0, 0));
}

bool DrawingWidget::withinBounds(Shape shape, int newX, int newY) const
{
    // 计算图形的中心位置
    QPoint newPos = initialCenter + QPoint(newX, newY);
    QSize size = shapeSizes.value(shape, QSize(50, 50));
    int halfWidth = size.width() / 2;
    int halfHeight = size.height() / 2;

    // 确保图形不会超出绘图区域
    if(newPos.x() - halfWidth < 0 || newPos.x() + halfWidth > width())
        return false;
    if(newPos.y() - halfHeight < 0 || newPos.y() + halfHeight > height())
        return false;
    return true;
}


void DrawingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 更新绘图区域的中心点
    initialCenter = QPoint(width() / 2, height() / 2);

    // 绘制每个图形
    //绘制逻辑：
    //以 pos 为中心，减去半宽和半高得到左上角坐标，宽高保持不变。
    // 1. 黄色圆形
    QPoint pos = initialCenter + shapeOffsets[YellowCircle];
    //QRect构造函数：（左上角坐标，宽，高）
    QRect yellowCircleRect(pos.x() - shapeSizes[YellowCircle].width()/2,
                           pos.y() - shapeSizes[YellowCircle].height()/2,
                           shapeSizes[YellowCircle].width(),
                           shapeSizes[YellowCircle].height());
    painter.setBrush(QColor(255, 255, 0)); // 黄色
    painter.setPen(Qt::NoPen);
    //圆形内嵌于矩形区域内
    painter.drawEllipse(yellowCircleRect);

    // 2. 红色矩形
    pos = initialCenter + shapeOffsets[RedRectangle];
    QRect redRect(pos.x() - shapeSizes[RedRectangle].width()/2,
                  pos.y() - shapeSizes[RedRectangle].height()/2,
                  shapeSizes[RedRectangle].width(),
                  shapeSizes[RedRectangle].height());
    painter.setBrush(QColor(255, 0, 0)); // 红色
    painter.drawRect(redRect);

    // 3. 绿色矩形
    pos = initialCenter + shapeOffsets[GreenRectangle];
    QRect greenRect(pos.x() - shapeSizes[GreenRectangle].width()/2,
                    pos.y() - shapeSizes[GreenRectangle].height()/2,
                    shapeSizes[GreenRectangle].width(),
                    shapeSizes[GreenRectangle].height());
    painter.setBrush(QColor(0, 255, 0)); // 绿色
    painter.drawRect(greenRect);

    // 4. 深蓝色矩形
    pos = initialCenter + shapeOffsets[DeepBlueRectangle];
    QRect deepBlueRect(pos.x() - shapeSizes[DeepBlueRectangle].width()/2,
                       pos.y() - shapeSizes[DeepBlueRectangle].height()/2,
                       shapeSizes[DeepBlueRectangle].width(),
                       shapeSizes[DeepBlueRectangle].height());
    painter.setBrush(QColor(0, 0, 255)); // 深蓝色
    painter.drawRect(deepBlueRect);

    // 5. 浅蓝色圆形
    pos = initialCenter + shapeOffsets[LightBlueCircle];
    QRect lightBlueCircleRect(pos.x() - shapeSizes[LightBlueCircle].width()/2,
                              pos.y() - shapeSizes[LightBlueCircle].height()/2,
                              shapeSizes[LightBlueCircle].width(),
                              shapeSizes[LightBlueCircle].height());
    painter.setBrush(QColor(0, 255, 255)); // 浅蓝色
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(lightBlueCircleRect);
}
