#include "widget.h"
#include<QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qssFile(":/style.qss");//1.
    if(qssFile.open(QFile::ReadOnly)){//2.
        a.setStyleSheet(qssFile.readAll());//3.加载qss样式表文件
    }
    qssFile.close();//4.

    Widget w;
    QString title = QString::fromLocal8Bit("信息简表");
    w.setWindowTitle(title);
    w.show();
    return a.exec();
}
