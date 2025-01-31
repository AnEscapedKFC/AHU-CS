#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    pSocket = new QWebSocket;
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &Widget::onMessageReceived);

    connect(pSocket, &QWebSocket::connected, this, [=]{ //!!!确保与CA端成功建立连接后再发送请求
        qDebug()<<QString::fromLocal8Bit("连接到服务器");
    });

    // 处理失败情况
    connect(pSocket, &QWebSocket::disconnected, this, [=]{
        qDebug() << "WebSocket disconnected";
        qDebug()<<QString::fromLocal8Bit("连接丢失");
        QApplication::quit();
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::onMessageReceived(QByteArray message) {//处理数据包

}


void Widget::handlePacket(DeMessagePacket *packet, const QByteArray &bodyData){

}



void Widget::sendMsg(void* buf, int bufLen, int type, int error, int mode) {
    // 创建包头并赋值

    char* charPath = static_cast<char*>(buf); //强制类型转换
    //QString qstrFilePath(charPath);
    DeMessageHead header;
    header.encoded = '0';
    header.version = '0';
    header.length = bufLen;
    //qDebug()<<sizeof(header);
    // 创建消息体
    DeMessagePacket packet;
    packet.mode = mode;
    packet.sequence = 0;
    packet.command = type;
    packet.error = error;
    // 将消息头和消息体序列化为 QByteArray
    QByteArray messageData;
    QDataStream stream(&messageData, QIODevice::WriteOnly);
    stream<<header.mark[0];
    stream<<header.mark[1];
    stream << header.encoded;
    stream << header.version;
    stream << header.length;

    // 序列化消息体
    stream << packet.mode;
    stream << packet.sequence;
    stream << packet.command;
    stream << packet.error;

    if (buf) {
        // 将用户数据复制到消息体部分
        QByteArray userData(charPath);
        stream << userData; // 序列化用户数据
        //qDebug()<<sizeof(userData);
    }

    // 发送消息
    qDebug()<<sizeof(messageData);
    this->pSocket->sendBinaryMessage(messageData); // 假设 pSocket 是有效的 QWebSocket 指针
}



void Widget::sendMsg(int command, int error, int mode) {
    // 设定消息头
    DeMessageHead header;
    header.encoded = '0';
    header.version = '0';
    header.length = -1;  // length 设为 -1 表示无用户数据

    qDebug() << sizeof(header);

    // 创建消息体
    DeMessagePacket packet;
    packet.mode = mode;
    packet.sequence = 0;
    packet.command = command;
    packet.error = error;

    // 将消息头和消息体序列化为 QByteArray
    QByteArray messageData;
    QDataStream stream(&messageData, QIODevice::WriteOnly);
    stream << header.mark[0];
    stream << header.mark[1];
    stream << header.encoded;
    stream << header.version;
    stream << header.length;

    // 序列化消息体
    stream << packet.mode;
    stream << packet.sequence;
    stream << packet.command;
    stream << packet.error;

    // 发送消息，无用户数据
    pSocket->sendBinaryMessage(messageData);  // 假设 pSocket 是有效的 QWebSocket 指针
}


void Widget::on_pushButton_clicked()//连接到服务端
{
    QString IPAddr = ui->lineEdit->text();
    QString Port = ui->lineEdit_2->text();
    QString path = "ws://"+IPAddr+":"+Port;
    qDebug()<<path;
    //"ws://127.0.0.1:443";
    QUrl url = QUrl(path);
    pSocket->open(url);
}




void Widget::on_pushButton_2_clicked()//发送消息到服务器
{
    //获取输入，打包为Json
    QJsonObject json;

    // 获取姓名
    QString name = ui->lineEdit_3->text().trimmed();
    if(name.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("姓名不能为空"));
        return;
    }
    json["name"] = name;

    // 获取学号
    QString studentId = ui->lineEdit_4->text().trimmed();
    if(studentId.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("学号不能为空"));
        return;
    }
    json["studentId"] = studentId;

    // 获取专业
    QString major = ui->lineEdit_5->text().trimmed();
    if(major.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("专业不能为空"));
        return;
    }
    json["major"] = major;

    // 获取红色RGB值
    QString red = ui->lineEdit_6->text().trimmed();
    if(red.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("红色RGB值不能为空"));
        return;
    }
    json["red"] = red;

    // 获取绿色RGB值
    QString green = ui->lineEdit_7->text().trimmed();
    if(green.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("绿色RGB值不能为空"));
        return;
    }
    json["green"] = green;

    // 获取蓝色RGB值
    QString blue = ui->lineEdit_8->text().trimmed();
    if(blue.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("蓝色RGB值不能为空"));
        return;
    }
    json["blue"] = blue;

    // 获取左上角X坐标
    QString leftTopX = ui->lineEdit_9->text().trimmed();
    if(leftTopX.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("左上角X坐标不能为空"));
        return;
    }
    json["leftTopX"] = leftTopX;

    // 获取左上角Y坐标
    QString leftTopY = ui->lineEdit_10->text().trimmed();
    if(leftTopY.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("左上角Y坐标不能为空"));
        return;
    }
    json["leftTopY"] = leftTopY;

    // 获取右下角X坐标
    QString rightBottomX = ui->lineEdit_11->text().trimmed();
    if(rightBottomX.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("右下角X坐标不能为空"));
        return;
    }
    json["rightBottomX"] = rightBottomX;

    // 获取右下角Y坐标
    QString rightBottomY = ui->lineEdit_12->text().trimmed();
    if(rightBottomY.isEmpty()) {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("右下角Y坐标不能为空"));
        return;
    }
    json["rightBottomY"] = rightBottomY;
    //获取图形种类
    if(ui->radioButton->isChecked())
        json["shape"]= QString::fromLocal8Bit("圆形");
    else
        json["shape"]=QString::fromLocal8Bit("矩形");
    QJsonDocument jsonDoc(json);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    sendMsg(byteArray.data(), byteArray.size(), CommandEnum_Paint, 0, 0);
}

