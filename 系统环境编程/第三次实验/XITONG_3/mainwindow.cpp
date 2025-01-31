
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QFont>
#include <QPushButton>
#include <QGroupBox>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentShape(DrawingWidget::YellowCircle) // 默认选中黄色圆形
{
    ui->setupUi(this);
    this->resize(600,800);

    // 创建中央小部件
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // 创建垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    // 上方区域：实时时间显示
    timeLabel = new QLabel(this);
    QFont timeFont = timeLabel->font();
    timeFont.setPointSize(14);
    timeFont.setBold(true);
    timeLabel->setFont(timeFont);
    timeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(timeLabel);

    // 添加分割线
    QFrame* splitFrame = new QFrame(this);
    splitFrame->setFrameShape(QFrame::HLine);
    splitFrame->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(splitFrame);

    // 添加10像素的垂直间距
    mainLayout->addSpacing(10);

    // 下方区域：绘图区域和学号姓名标签
    // 创建一个容器小部件
    QWidget *drawingContainer = new QWidget(this);
    //drawingContainer->setStyleSheet("background-color: darkgray;"); // 背景颜色
    drawingContainer->setFixedSize(600, 400); // 设置固定大小，或根据需要调整
    mainLayout->addWidget(drawingContainer, 1, Qt::AlignCenter); // 拉伸因子为1，居中对齐

    // 创建绘图控件
    drawingWidget = new DrawingWidget(drawingContainer);
    drawingWidget->setGeometry(0, 0, 600, 400); // 覆盖整个容器
    drawingWidget->raise(); // 确保绘图控件在最上层

    // 创建学号姓名标签
    infoLabel = new QLabel(QString::fromLocal8Bit("学号: \n姓名: "), drawingContainer);
    QFont infoFont = infoLabel->font();
    infoFont.setPointSize(10);
    infoLabel->setFont(infoFont);
    //infoLabel->setStyleSheet("color: black; background-color: rgba(255, 255, 255, 150);"); // 半透明背景
    infoLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    infoLabel->setGeometry(10, 10, 200, 50); // 左上角位置和大小

    // 添加分割线
    QFrame* splitFrame1 = new QFrame(this);
    splitFrame1->setFrameShape(QFrame::HLine);
    splitFrame1->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(splitFrame1);

    // 添加10像素的垂直间距
    mainLayout->addSpacing(10);

    // 添加控制区域：左右分割
    QWidget *controlContainer = new QWidget(this);
    controlContainer->setFixedSize(600, 200); // 设置固定大小
    mainLayout->addWidget(controlContainer, 0, Qt::AlignCenter); // 固定大小，不拉伸

    // 创建水平布局
    QHBoxLayout *controlLayout = new QHBoxLayout(controlContainer);
    controlLayout->setContentsMargins(10, 10, 10, 10);
    controlLayout->setSpacing(20);

    // 左边：RadioButtons
    QGroupBox *radioGroupBox = new QGroupBox(QString::fromLocal8Bit("选项"), controlContainer);
    QGridLayout *radioLayout = new QGridLayout(radioGroupBox);
    radioLayout->setSpacing(5); // 设置控件之间的垂直间距为5像素

    // 创建RadioButtons并添加到列表
    QRadioButton *radio1 = new QRadioButton(QString::fromLocal8Bit("黄色圆形"), radioGroupBox);
    QRadioButton *radio2 = new QRadioButton(QString::fromLocal8Bit("红色矩形"), radioGroupBox);
    QRadioButton *radio3 = new QRadioButton(QString::fromLocal8Bit("绿色矩形"), radioGroupBox);
    QRadioButton *radio4 = new QRadioButton(QString::fromLocal8Bit("深蓝色矩形"), radioGroupBox);
    QRadioButton *radio5 = new QRadioButton(QString::fromLocal8Bit("浅蓝色圆形"), radioGroupBox);

    radio1->setChecked(true); // 默认选中第一个

    // 将 RadioButtons 添加到网格布局中
    radioLayout->addWidget(radio1, 0, 0);
    radioLayout->addWidget(radio2, 1, 0);
    radioLayout->addWidget(radio3, 2, 0);
    radioLayout->addWidget(radio4, 0, 1);
    radioLayout->addWidget(radio5, 1, 1);
    radioLayout->setRowStretch(3, 1); // 添加伸缩

    radioGroupBox->setLayout(radioLayout);
    controlLayout->addWidget(radioGroupBox, 1); // 拉伸因子为1

    // 将 RadioButtons 添加到列表中
    radioButtons << radio1 << radio2 << radio3 << radio4 << radio5;

    // 连接 RadioButtons 的 toggled 信号到槽函数
    for(auto radio : radioButtons)
    {
        connect(radio, &QRadioButton::toggled, this, &MainWindow::onRadioButtonToggled);
    }

    // 右边：Sliders
    QWidget *sliderWidget = new QWidget(controlContainer);
    QVBoxLayout *sliderLayout = new QVBoxLayout(sliderWidget);
    sliderLayout->setSpacing(20);

    // 第一个滑动条 - 水平移动
    QLabel *sliderLabel1 = new QLabel(QString::fromLocal8Bit("水平移动"), sliderWidget);
    sliderHorizontal = new QSlider(Qt::Horizontal, sliderWidget);
    sliderHorizontal->setRange(-150, 150); // 设置范围，可根据需要调整
    sliderHorizontal->setValue(0); // 初始值
    sliderLayout->addWidget(sliderLabel1);
    sliderLayout->addWidget(sliderHorizontal);

    // 第二个滑动条 - 垂直移动
    QLabel *sliderLabel2 = new QLabel(QString::fromLocal8Bit("垂直移动"), sliderWidget);
    sliderVertical = new QSlider(Qt::Horizontal, sliderWidget);
    sliderVertical->setRange(-150, 150); // 设置范围，可根据需要调整
    sliderVertical->setValue(0); // 初始值
    sliderLayout->addWidget(sliderLabel2);
    sliderLayout->addWidget(sliderVertical);

    sliderLayout->addStretch(); // 推动滑动条到顶部
    sliderWidget->setLayout(sliderLayout);
    controlLayout->addWidget(sliderWidget, 2); // 拉伸因子为2

    // 连接滑动条的值变化信号到槽函数
    connect(sliderHorizontal, &QSlider::valueChanged, this, &MainWindow::onSliderHorizontalValueChanged);
    connect(sliderVertical, &QSlider::valueChanged, this, &MainWindow::onSliderVerticalValueChanged);

    // 初始化并启动定时器
    timer = new QTimer(this);
    QFont font("Arial", 16, QFont::Bold);
    timeLabel->setFont(font);

    // 设置文字颜色为红色
    QPalette palette = timeLabel->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    timeLabel->setPalette(palette);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000); // 每1000毫秒（1秒）触发一次
    updateTime(); // 初始更新时间
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    QString currentTime = QDateTime::currentDateTime().toString(QString::fromLocal8Bit("yyyy 年MM 月dd日 hh:mm:ss"));
    timeLabel->setText(currentTime);
}

void MainWindow::onRadioButtonToggled()
{
    // 确定哪个 RadioButton 被选中
    for(int i = 0; i < radioButtons.size(); ++i)
    {
        if(radioButtons[i]->isChecked())
        {
            currentShape = static_cast<DrawingWidget::Shape>(i);

            // 获取当前图形的偏移量
            QPoint offset = drawingWidget->getShapeOffset(currentShape);

            // 更新滑动条的值，阻塞信号以避免触发槽函数
            sliderHorizontal->blockSignals(true);
            sliderVertical->blockSignals(true);
            sliderHorizontal->setValue(offset.x());
            sliderVertical->setValue(offset.y());
            sliderHorizontal->blockSignals(false);
            sliderVertical->blockSignals(false);

            break;
        }
    }
}

void MainWindow::onSliderHorizontalValueChanged(int value)
{
    // 获取当前图形的垂直偏移量
    QPoint currentOffset = drawingWidget->getShapeOffset(currentShape);

    // 设置新的水平偏移量
    drawingWidget->setShapeOffset(currentShape, value, currentOffset.y());
}

void MainWindow::onSliderVerticalValueChanged(int value)
{
    // 获取当前图形的水平偏移量
    QPoint currentOffset = drawingWidget->getShapeOffset(currentShape);

    // 设置新的垂直偏移量
    drawingWidget->setShapeOffset(currentShape, currentOffset.x(), value);
}

