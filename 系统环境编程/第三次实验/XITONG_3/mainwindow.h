// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H

// #include <QMainWindow>
// #include<QLabel>
// #include<QTimer>
// #include"drawingwidget.h"
// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

// class MainWindow : public QMainWindow
// {
//     Q_OBJECT

// public:
//     MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// private slots:
//     void updateTime(); // 槽函数用于更新时间显示

// private:
//     Ui::MainWindow *ui;
//     QLabel *timeLabel;       // 显示时间的标签
//     QLabel *infoLabel;       // 显示学号和姓名的标签
//     DrawingWidget *drawingWidget; // 自定义绘图控件
//     QTimer *timer;           // 定时器用于更新时间
// };
// #endif // MAINWINDOW_H


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QRadioButton>
#include <QSlider>
#include "drawingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTime();
    void onRadioButtonToggled();
    void onSliderHorizontalValueChanged(int value);
    void onSliderVerticalValueChanged(int value);

private:
    Ui::MainWindow *ui;
    QLabel *timeLabel;
    QLabel *infoLabel;
    DrawingWidget *drawingWidget;
    QTimer *timer;

    QList<QRadioButton*> radioButtons;
    QSlider *sliderHorizontal;
    QSlider *sliderVertical;

    DrawingWidget::Shape currentShape;
};

#endif // MAINWINDOW_H
