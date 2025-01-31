#include "mainwindow.h"
#include<QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile qssFile(":/style.qss");//1.
    if(qssFile.open(QFile::ReadOnly)){//2.
        a.setStyleSheet(qssFile.readAll());//3.加载qss样式表文件
    }
    qssFile.close();//4.
    w.show();
    return a.exec();
}
