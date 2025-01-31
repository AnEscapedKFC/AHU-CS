/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QTextEdit *textEdit;
    QGroupBox *groupBox;
    QLabel *drawingLabel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1039, 600);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 20, 151, 40));
        pushButton->setMinimumSize(QSize(60, 40));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 20, 151, 40));
        pushButton_2->setMinimumSize(QSize(60, 40));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 70, 81, 21));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 120, 441, 461));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(500, 110, 431, 471));
        drawingLabel = new QLabel(groupBox);
        drawingLabel->setObjectName(QString::fromUtf8("drawingLabel"));
        drawingLabel->setGeometry(QRect(10, 20, 411, 431));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255\346\234\215\345\212\241\345\231\250", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\216\245\346\224\266\346\266\210\346\201\257", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\347\273\230\345\233\276\345\214\272", nullptr));
        drawingLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
