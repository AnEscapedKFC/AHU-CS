#include "MsgHandle.h"
#include"command.h"
#include<QTimer>
#include<QMessageBox>




Session::Session(QWebSocket* p){
    pSocket =p;
}

Session::~Session(){
    delete pSocket;

}


void Session::sendMsg(void* buf, int bufLen, int type, int error, int mode) {
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



void Session::sendMsg(int command, int error, int mode) {
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



void Session::onMessageReceived(QByteArray message) {//处理数据包

    // 确保消息足够长，至少包含 DeMessageHead
    if (message.size() < sizeof(DeMessageHead)) {
        // 消息太短，无法包含有效的头
        return;
    }

    // 将消息数据复制到一个连续的缓冲区
    QByteArray buffer = message;
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    QChar headermark[2];
    // 临时变量，用于读取头信息
    DeMessageHead header;
    stream >> headermark[0]>>headermark[1] >> header.encoded >> header.version >> header.length;//从二进制流中读取数据

    // 检查标记是否匹配
    if (headermark[0]!='C'||headermark[1]!='A') {
        // 标记不匹配，可能是错误的消息
        qDebug()<<"NOT CA";
        return;
    }
    if(header.length==-1){//只请求，不传参
        DeMessagePacket packet;
        if (stream.device()->seek(sizeof(DeMessageHead))) {
            stream >> packet.mode >> packet.sequence >> packet.command >> packet.error;
            if(packet.command==command::CommandEnum_Paint){

            }

            else {
                // 未知命令处理
                qDebug() << "Unknown command received!";
            }
        }
        return;
    }
    // 检查消息长度是否正确
    if (header.length != buffer.size() - sizeof(DeMessageHead)-sizeof(DeMessagePacket)-4) {
        // 消息长度不匹配，可能是错误的消息
        qDebug()<<buffer.size() - sizeof(DeMessageHead)-sizeof(DeMessagePacket);
        qDebug()<<"Err Length";
        return;
    }

    // 读取消息体
    DeMessagePacket packet;
    if (stream.device()->seek(sizeof(DeMessageHead))) {
        stream >> packet.mode >> packet.sequence >> packet.command >> packet.error;
    }

    // 处理消息体中的数据
    //QByteArray bodyData = buffer.mid(sizeof(DeMessageHead), header.length);
    QByteArray msg;
    stream>>msg;
    //根据 packet->command 处理消息
    handlePacket(&packet, msg);
}


void Session::handlePacket(DeMessagePacket *packet, const QByteArray &bodyData) {

    //qDebug()<<QString(bodyData);
    switch (packet->command) {
    case CommandEnum_Paint:
        emit Paint(bodyData);
        break;

    default:
        // 未知命令处理
        break;
    }
}


void Session::handleMsg(const QByteArray &bodyData){

}
