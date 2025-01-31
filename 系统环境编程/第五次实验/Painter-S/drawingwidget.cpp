// #include "drawingwidget.h"
// #include <QPainter>
// #include <QPaintEvent>
// #include <QMap>

// DrawingWidget::DrawingWidget(QWidget *parent)
//     : QWidget(parent)
// {
//     // 初始化图形尺寸
//     shapeSizes[Circle] = QSize(static_cast<int>(200 * scaleFactor), static_cast<int>(200 * scaleFactor));
//     shapeSizes[Rectangle] = QSize(static_cast<int>(141 * scaleFactor), static_cast<int>(141 * scaleFactor));

//     // 初始化所有图形的偏移量为(0,0)
//     for(int i = 0; i < ShapeCount; ++i)
//     {
//         shapeOffsets[static_cast<Shape>(i)] = QPoint(0, 0);
//     }

//     // 初始化所有图形的颜色为默认颜色
//     shapeColors[Circle] = QColor(255, 255, 0); // 黄色
//     shapeColors[Rectangle] = QColor(255, 0, 0); // 红色

//     // 初始时不激活任何图形
// }

// void DrawingWidget::setShapeOffset(Shape shape, int deltaX, int deltaY)
// {
//     // 检查新位置是否在边界内
//     if(withinBounds(shape, deltaX, deltaY))
//     {
//         shapeOffsets[shape] = QPoint(deltaX, deltaY);
//         //update(); // 触发重绘
//     }
// }

// QPoint DrawingWidget::getShapeOffset(Shape shape) const
// {
//     return shapeOffsets.value(shape, QPoint(0, 0));
// }

// void DrawingWidget::setShapeColor(Shape shape, const QColor &color)
// {
//     if(shapeColors.contains(shape))
//     {
//         shapeColors[shape] = color;
//         //update(); // 触发重绘
//     }
// }

// QColor DrawingWidget::getShapeColor(Shape shape) const
// {
//     return shapeColors.value(shape, QColor(Qt::black));
// }

// void DrawingWidget::activateShape(Shape shape)
// {
//     if(shape < ShapeCount)
//     {
//         activeShapes.insert(shape);
//         update(); // 触发重绘
//     }
// }

// void DrawingWidget::deactivateShape(Shape shape)
// {
//     if(activeShapes.contains(shape))
//     {
//         activeShapes.remove(shape);
//         update(); // 触发重绘
//     }
// }

// bool DrawingWidget::isShapeActive(Shape shape) const
// {
//     return activeShapes.contains(shape);
// }

// bool DrawingWidget::withinBounds(Shape shape, int newX, int newY) const
// {
//     // 计算图形的中心位置
//     QPoint newPos = initialCenter + QPoint(newX, newY);
//     QSize size = shapeSizes.value(shape, QSize(50, 50));
//     int halfWidth = size.width() / 2;
//     int halfHeight = size.height() / 2;

//     // 确保图形不会超出绘图区域
//     if(newPos.x() - halfWidth < 0 || newPos.x() + halfWidth > width())
//         return false;
//     if(newPos.y() - halfHeight < 0 || newPos.y() + halfHeight > height())
//         return false;
//     return true;
// }

// void DrawingWidget::paintEvent(QPaintEvent *event)
// {
//     Q_UNUSED(event);

//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing, true);

//     // 更新绘图区域的中心点
//     initialCenter = QPoint(width() / 2, height() / 2);

//     // 遍历所有激活的图形并绘制
//     for(auto shape : activeShapes)
//     {
//         QPoint pos = initialCenter + shapeOffsets[shape];
//         QRect rect(pos.x() - shapeSizes[shape].width()/2,
//                    pos.y() - shapeSizes[shape].height()/2,
//                    shapeSizes[shape].width(),
//                    shapeSizes[shape].height());

//         painter.setBrush(shapeColors[shape]);
//         painter.setPen(Qt::NoPen);

//         switch(shape)
//         {
//         case Circle:
//             painter.drawEllipse(rect);
//             break;
//         case Rectangle:
//             painter.drawRect(rect);
//             break;
//         default:
//             break;
//         }
//     }
// }


#include "DrawingWidget.h"
#include <QPainter>
#include <QPaintEvent>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化每种图形的信息
    m_shapeInfo[Circle] = ShapeInfo();
    m_shapeInfo[Rectangle] = ShapeInfo();
}

void DrawingWidget::setShapeColor(Shape shape, const QColor &color)
{
    m_shapeInfo[shape].color = color;
    update(); // 更新绘制
}

void DrawingWidget::setShapeOffset(Shape shape, int offsetX, int offsetY)
{
    m_shapeInfo[shape].offsetX = offsetX;
    m_shapeInfo[shape].offsetY = offsetY;
    update(); // 更新绘制
}

void DrawingWidget::activateShape(Shape shape)
{
    m_shapeInfo[shape].active = true;
    update(); // 更新绘制
}

void DrawingWidget::deactivateShape(Shape shape)
{
    m_shapeInfo[shape].active = false;
    update(); // 更新绘制
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 根据信息绘制圆形
    if (m_shapeInfo[Circle].active) {
        painter.setBrush(m_shapeInfo[Circle].color);
        painter.setPen(Qt::NoPen);

        // 假设圆形半径固定为50像素，圆心为(offsetX, offsetY)
        int radius = 50;
        int cx = m_shapeInfo[Circle].offsetX;
        int cy = m_shapeInfo[Circle].offsetY;
        painter.drawEllipse(cx - radius, cy - radius, radius * 2, radius * 2);
    }

    // 根据信息绘制矩形
    if (m_shapeInfo[Rectangle].active) {
        painter.setBrush(m_shapeInfo[Rectangle].color);
        painter.setPen(Qt::NoPen);

        // 假设矩形宽高可以根据需要设定，这里简单示例为100x60
        // 左上角为(offsetX, offsetY)
        int x = m_shapeInfo[Rectangle].offsetX;
        int y = m_shapeInfo[Rectangle].offsetY;
        int width = 100;
        int height = 60;
        painter.drawRect(x, y, width, height);
    }
}
