/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_8;
    QPushButton *pushButton_6;
    QPushButton *pushButton_2;
    QPushButton *pushButton_10;
    QPushButton *pushButton_0;
    QPushButton *pushButton_12;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_13;
    QPushButton *pushButton_11;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 609);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 40, 771, 71));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 130, 471, 401));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 2, 0, 1, 1);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_9 = new QPushButton(widget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 2, 2, 1, 1);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_8 = new QPushButton(widget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 2, 1, 1, 1);

        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_10 = new QPushButton(widget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 3, 0, 1, 1);

        pushButton_0 = new QPushButton(widget);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));

        gridLayout->addWidget(pushButton_0, 3, 1, 1, 1);

        pushButton_12 = new QPushButton(widget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));

        gridLayout->addWidget(pushButton_12, 3, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(540, 130, 261, 401));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        pushButton_13 = new QPushButton(widget_2);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));

        verticalLayout->addWidget(pushButton_13);

        pushButton_11 = new QPushButton(widget_2);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

        verticalLayout->addWidget(pushButton_11);

        pushButton_14 = new QPushButton(widget_2);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));

        verticalLayout->addWidget(pushButton_14);

        pushButton_15 = new QPushButton(widget_2);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));

        verticalLayout->addWidget(pushButton_15);

        pushButton_16 = new QPushButton(widget_2);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));

        verticalLayout->addWidget(pushButton_16);

        pushButton_17 = new QPushButton(widget_2);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));

        verticalLayout->addWidget(pushButton_17);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        pushButton_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
