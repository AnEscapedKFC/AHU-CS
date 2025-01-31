#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QtWebSockets/QWebSocket>
#include<QtWebSockets/QWebSocketServer>
#include<QDataStream>
#include<QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include "command.h"
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
    void sendMsg(void*buf,int bufLen,int type,int error = 0,int mode = 2); //
    void sendMsg(int command, int error, int mode);
    void onMessageReceived(const QByteArray message);
    void handlePacket(DeMessagePacket *packet, const QByteArray &bodyData);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QWebSocket *pSocket=nullptr;
};
#endif // WIDGET_H
