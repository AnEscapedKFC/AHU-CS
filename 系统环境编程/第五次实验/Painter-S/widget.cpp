#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_WebSocketServer = new QWebSocketServer("server", QWebSocketServer::NonSecureMode); //创建一个新的QWebSocketServer实例，表示WebSocket服务器
    m_WebSocketServer->setMaxPendingConnections(10);//设置等待接受的连接数的最大值为10（请求依次入队
    m_WebSocketServer->setProxy(QNetworkProxy::NoProxy);//不设置代理
    pixmap = new QPixmap(ui->drawingLabel->size());//设置画布大小（以标签作为绘制区域）
    pixmap->fill(Qt::white);//绘图背景设置为白色
    ui->drawingLabel->setPixmap(*pixmap);//对标签设置画布
}

Widget::~Widget()
{
    delete ui;
}


int Widget::addSession(Session* newSession){
    if (!newSession)
    {
        return -1;
    }
    m_clients.append(newSession);
    return 0;
}


int Widget::delSession(Session* newSession){
    //QMutexLocker locker(&m_gSessionMapLock);
    int iter = m_clients.indexOf(newSession);
    if (iter !=1)//找到
    {
        m_clients.removeOne(newSession);
        return 0;
    }
    else
        return -1;
}


void Widget::on_pushButton_clicked() //打开服务器
{
    int i_port = 443;//获取端口
    m_WebSocketServer->listen(QHostAddress::AnyIPv4, i_port);
    connect(m_WebSocketServer, &QWebSocketServer::newConnection, this, &Widget::onnewconnection);
    ui->textEdit->append(QString::fromLocal8Bit("<b>打开服务器</b>"));
}



void Widget::onnewconnection(){
    pSocket = m_WebSocketServer->nextPendingConnection();
    Session *s=new Session(pSocket);//获取等待接受的第一个连接请求，并将其赋值给 pSocket 指针（当前连接的客户端对象）。表示服务器已经接受了这个连接，并且现在可以与客户端进行通信。
    QHostAddress clientAddress = pSocket->peerAddress();//客户端的IP地址
    connect(s->pSocket,&QWebSocket::binaryMessageReceived,s,&Session::onMessageReceived);
    connect(s,&Session::Paint,this,&Widget::handleMsg);
    if(!m_clients.contains(s))
        m_clients << s; //加入到已经建立连接的容器中
    ui->textEdit->append("onnew"+clientAddress.toString());
    addSession(s);
    return;
}


void Widget::handleMsg(const QByteArray &bodyData)
{
    // 解析 JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bodyData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << QString::fromLocal8Bit("JSON 解析错误: ") << parseError.errorString();
        return;
    }

    // 确保数据为 JSON 对象
    if (!jsonDoc.isObject()) {
        qDebug() << QString::fromLocal8Bit("无效的 JSON 格式: 不是一个对象");
        return;
    }

    // 解析 JSON 对象
    QJsonObject jsonObj = jsonDoc.object();
    QString currentTime = QDateTime::currentDateTime().toString(QString::fromLocal8Bit("yyyy-MM-dd--hh时-mm分-ss秒"));

    // 提取各个字段
    QString name = jsonObj.value("name").toString();
    QString studentId = jsonObj.value("studentId").toString();
    QString major = jsonObj.value("major").toString();
    QString red = jsonObj.value("red").toString();
    QString green = jsonObj.value("green").toString();
    QString blue = jsonObj.value("blue").toString();
    QString leftTopX = jsonObj.value("leftTopX").toString();
    QString leftTopY = jsonObj.value("leftTopY").toString();
    QString rightBottomX = jsonObj.value("rightBottomX").toString();
    QString rightBottomY = jsonObj.value("rightBottomY").toString();
    QString shape = jsonObj.value("shape").toString();
    // 构建显示字符串
    QString displayText;
    displayText += QString::fromLocal8Bit("时间: %1\n").arg(currentTime);
    displayText += QString::fromLocal8Bit("姓名: %1\n").arg(name);
    displayText += QString::fromLocal8Bit("学号: %1\n").arg(studentId);
    displayText += QString::fromLocal8Bit("专业: %1\n").arg(major);
    displayText += QString::fromLocal8Bit("图型: %1\n").arg(shape);
    displayText += QString::fromLocal8Bit("红色RGB值: %1\n").arg(red);
    displayText += QString::fromLocal8Bit("绿色RGB值: %1\n").arg(green);
    displayText += QString::fromLocal8Bit("蓝色RGB值: %1\n").arg(blue);
    displayText += QString::fromLocal8Bit("左上角X坐标: %1\n").arg(leftTopX);
    displayText += QString::fromLocal8Bit("左上角Y坐标: %1\n").arg(leftTopY);
    displayText += QString::fromLocal8Bit("右下角X坐标: %1\n").arg(rightBottomX);
    displayText += QString::fromLocal8Bit("右下角Y坐标: %1\n").arg(rightBottomY);
    ui->textEdit->append(QString::fromLocal8Bit("<b>检测到一条新的请求</b>"));
    ui->textEdit->append(displayText);

    bool ok;
    int redc = red.toInt(&ok);
    if (!ok) redc = 0;
    int greenc = green.toInt(&ok);
    if (!ok) greenc = 0;
    int bluec = blue.toInt(&ok);
    if (!ok) bluec = 0;
    QColor color(redc, greenc, bluec);

    // 转换坐标
    int leftTopXI = leftTopX.toInt(&ok);
    if (!ok) leftTopXI = 0;
    int leftTopYI = leftTopY.toInt(&ok);
    if (!ok) leftTopYI = 0;
    int rightBottomXI = rightBottomX.toInt(&ok);
    if (!ok) rightBottomXI = 0;
    int rightBottomYI = rightBottomY.toInt(&ok);
    if (!ok) rightBottomYI = 0;

    // 计算宽度和高度
    int width = rightBottomXI - leftTopXI;
    int height = rightBottomYI - leftTopYI;

    // 使用 QPainter 在累积的 QPixmap 上绘制新图形
    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    painter.setBrush(color);//图形颜色
    painter.setPen(Qt::black); // 边框颜色
    if(shape==QString::fromLocal8Bit("圆形"))
    {
        int diameter = qMin(width, height); // 计算圆的半径，以宽度和高度中的较小值为基准
        painter.drawEllipse(QPoint(leftTopXI + diameter / 2, leftTopYI + diameter / 2), diameter / 2, diameter / 2);
    }
    else
    {
        painter.drawRect(leftTopXI, leftTopYI, width, height);
    }
    painter.end();

    // 将绘制好的 QPixmap 设置到 QLabel 上
    ui->drawingLabel->setPixmap(*pixmap);
}
