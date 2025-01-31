#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"MsgHandle.h"
#include"command.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QString>
#include <QTextEdit>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int addSession(Session* newSession);
    int delSession(Session* newSession);
    void handleMsg(const QByteArray &bodyData);
private slots:
    void on_pushButton_clicked();
    void onnewconnection();

private:
    QPixmap *pixmap;//QPixmap 充当了一个持久化的图形状态存储器
    Ui::Widget *ui;
    QList<Session *> m_clients; //创建容器，存放与客户端的连接实例
    QWebSocketServer *m_WebSocketServer; //服务端对象
    QWebSocket *pSocket;//能用于引用当前活动的WebSocket连接。
};
#endif // WIDGET_H
