#ifndef WIDGET_H
#define WIDGET_H
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QWidget>

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
    QRegularExpression createIPRegex();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_lineEdit_10_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    void StoreInfo();
    int CheckGender();
};
#endif // WIDGET_H
