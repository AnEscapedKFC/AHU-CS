#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QMessageBox>
#include<QStack>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void onDigitOrOperatorClicked();
    void onEqualsClicked();
    void onCleanClicked();
    void updateFunctionButtons();
    double evaluateExpression(const QString &expr, bool &ok);
    ~MainWindow();

private:
    QString currentExpression;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
