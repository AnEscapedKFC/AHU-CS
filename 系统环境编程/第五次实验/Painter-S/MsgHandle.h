#ifndef MSGHANDLE_H
#define MSGHANDLE_H

#include<QObject>
#include<QtWebSockets/QWebSocket>
#include<QtWebSockets/QWebSocketServer>
#include "command.h"
class Session:public QObject{ //负责处理与单个客户端之间的通讯（处理当前接收到的包）
    Q_OBJECT
public:
    friend class Widget;
    Session(QWebSocket *pSocket);
    ~Session();
    void sendMsg(void*buf,int bufLen,int type,int error = 0,int mode = 2); //
    void sendMsg(int command, int error, int mode);
    void onMessageReceived(QByteArray message);
    void handlePacket(DeMessagePacket *packet, const QByteArray &bodyData);
    void handleMsg(const QByteArray &bodyData);
signals:
    void Paint(const QByteArray &bodyData);
private:
    QWebSocket *pSocket;//能用于引用当前活动的WebSocket连接。
    // mapFriendInfo m_friendInfoMap;
};




#endif // MSGHANDLE_H
