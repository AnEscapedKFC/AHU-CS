#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonObject>
#include<QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QDir>
#include <QDateTime>
#include<QDialog>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
   // ui->widget->setWindowTitle("dsfvwsfaa");


    // 创建 QLineEdit 控件

    // 设置输入掩码："000.000.000.000;."
    // '0' 表示必填数字，'.' 为固定的点
    connect(ui->pushButton_4,&QPushButton::clicked,this,&Widget::StoreInfo);
    QRegularExpression ipRegex("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}"
                               "(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(ipRegex, this);
    ui->lineEdit_3->setValidator(validator);
    ui->lineEdit_3->setInputMask("000.000.000.000;");

    // 设置占位符文本
    ui->lineEdit_3->setPlaceholderText("000.000.000.000");
    ui->lineEdit_4->setValidator(validator);
    ui->lineEdit_4->setInputMask("000.000.000.000;");//0表示可忽略，且输入只能是0-9

    // 设置占位符文本
    ui->lineEdit_4->setPlaceholderText("000.000.000.000");
    //获取输入时，记得去空格
    ui->lineEdit_6->setInputMask("HH-HH-HH-HH-HH-HH;");//H表示不可忽略，且限制16进制字符
}

Widget::~Widget()
{
    delete ui;
}


QRegularExpression Widget::createIPRegex()
{
    // 每个区间的正则表达式
    QString octet = R"((25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d))";

    // 完整的IP地址正则表达式
    QString ipPattern = QString("^%1\\.%2\\.%3\\.%4$")
                            .arg(octet)
                            .arg(octet)
                            .arg(octet)
                            .arg(octet);

    QRegularExpression regex(ipPattern);
    return regex;
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    ui->lineEdit_10->setText(QString::number(position));
}


void Widget::on_lineEdit_10_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok);

    if (ok) {

        // 设置滑动条的值（自动处理范围，因为 QIntValidator 已限制输入）
        ui->horizontalSlider->setValue(value);


    } else {
        qDebug() << "Invalid input in lineEdit_10:" << arg1;
    }
}


int Widget::CheckGender(){
    if(ui->radioButton->isChecked()){
        return 0;
    }
    else if(ui->radioButton_2->isChecked())
        return 1;
    else
        return 2;
}


void Widget::StoreInfo(){

    QJsonObject jsonObj;//创建json对象存储个人信息
    //从各个控件中获取个人信息
    QString Grade = ui->comboBox->currentText();
    Grade.toLocal8Bit().constData();//!!!!!对中文转码
    jsonObj["Grade"]=Grade;
    qDebug()<<Grade;

    QString Subject = ui->comboBox_2->currentText();
    Subject.toLocal8Bit().constData();
    jsonObj["Subject"]=Subject;
    qDebug()<<Subject;

    QString Gender;
    switch(CheckGender()){
    case 0:
        Gender = QString::fromLocal8Bit("男");
        break;
    case 1:
        Gender = QString::fromLocal8Bit("女");
        break;
    case 2:
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("我们不支持LGBT！")); // 警告信息
        return;
        break;
    }
    jsonObj["Gender"]=Gender;
    qDebug()<<Gender;

    if(ui->lineEdit_10->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("AGE！"));
        return;
    }// 警告信息
    jsonObj["age"]=ui->lineEdit_10->text();
    qDebug()<<ui->lineEdit_10->text();

    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("我们不录入无名之辈！"));
        return;
    }
    jsonObj["name"]=ui->lineEdit->text();//!!!从控件中输入的中文可以不用转码

    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("number"));
        return;
    }
    jsonObj["number"]=ui->lineEdit_2->text();

    if(ui->lineEdit_3->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("IP！"));
        return;
    }
    QString IPAddr = ui->lineEdit_3->text().remove(QRegExp("^ +\\s*")); //使用正则表达式去除空格
    jsonObj["IPAddr"]=IPAddr;//IP地址

    if(ui->lineEdit_6->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("MAC！"));
        return;
    }
    jsonObj["MAC"]=ui->lineEdit_6->text();//物理地址

    if(ui->lineEdit_4->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("subnet"));
        return;
    }
    jsonObj["SubNetMask"]=ui->lineEdit_4->text().remove(QRegExp("^ +\\s*"));//子网掩码

    if(ui->lineEdit_5->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("籍贯！"));
        return;
    }
    jsonObj["From"]=ui->lineEdit_5->text();//籍贯

    if(ui->lineEdit_8->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("政治面貌?"));
        return;
    }
    jsonObj["zzmm"]=ui->lineEdit_8->text();

    if(ui->lineEdit_9->text().isEmpty()){
        QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("大隐隐于市？"));
        return;
    }
    jsonObj["Contact"]=ui->lineEdit_9->text();

    QJsonDocument jsonDoc(jsonObj);

    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact); //转为字节数组，方便写入到文件

    QString selectedDir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "",
                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);//打开选择路径对话框
    selectedDir.toLocal8Bit().constData();  //!!!!!十分重要，对中文路径进行转码】
    if (selectedDir.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("No directory selected."));
        return;
    }
    // 获取当前时间并格式化为字符串,唯一标识文件名
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString fileName = QString("info_%1.txt").arg(timestamp);//拼接，组成文件名

    // 构建完整的文件路径
    QString filePath = QDir(selectedDir).filePath(fileName);
    qDebug() << "File Path:" << filePath;


    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file for writing: ") + file.errorString());
        return;
    }

    // 写入 QByteArray 到文件
    qint64 bytesWritten = file.write(byteArray);
    if (bytesWritten == -1) {
        QMessageBox::warning(this, tr("Warning"), tr("Failed to write data to file."));
        file.close();
        return;
    }

    file.close();
    qDebug() << "Data written to" << filePath;

    QMessageBox::information(this, tr("Success"), tr("Information saved successfully as ") + fileName);
    return;
}


void Widget::on_pushButton_2_clicked()//打开文件
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Info File"), "",
                                                    tr("Info Files (info_*.txt)")); //打开选择文件对话框
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("No file selected."));
        return;
    }

    //打开并读取文件内容
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file for reading: ") + file.errorString());
        return;
    }

    QByteArray byteArray = file.readAll();
    file.close();


    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        QMessageBox::warning(this, tr("Warning"), tr("Failed to parse JSON data: ") + jsonError.errorString());
        return;
    }


    if (!jsonDoc.isObject()) {
        QMessageBox::warning(this, tr("Warning"), tr("Invalid JSON format: not an object."));
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();//创建json对象，接收从文件中读取的信息

    QString Grade = jsonObj.value("Grade").toString();
    QString Subject = jsonObj.value("Subject").toString();
    QString Gender = jsonObj.value("Gender").toString();
    QString age = jsonObj.value("age").toString();
    QString name = jsonObj.value("name").toString();
    QString number = jsonObj.value("number").toString();
    QString IPAddr = jsonObj.value("IPAddr").toString();
    QString MAC = jsonObj.value("MAC").toString();
    QString SubNetMask = jsonObj.value("SubNetMask").toString();
    QString From = jsonObj.value("From").toString();
    QString zzmm = jsonObj.value("zzmm").toString();
    QString Contact = jsonObj.value("Contact").toString();

    // qDebug() << "Grade:" << Grade;
    // qDebug() << "Subject:" << Subject;
    // qDebug() << "Gender:" << Gender;
    // qDebug() << "Age:" << age;
    // qDebug() << "Name:" << name;
    // qDebug() << "Number:" << number;
    // qDebug() << "IPAddr:" << IPAddr;
    // qDebug() << "MAC:" << MAC;
    // qDebug() << "SubNetMask:" << SubNetMask;
    // qDebug() << "From:" << From;
    // qDebug() << "zzmm:" << zzmm;
    // qDebug() << "Contact:" << Contact;

    //设置各个控件的信息
    ui->comboBox->setCurrentText(Grade);
    ui->comboBox_2->setCurrentText(Subject);

    if (Gender == QString::fromLocal8Bit("男")) {
        ui->radioButton->setChecked(true);
    } else if (Gender == QString::fromLocal8Bit("女")) {
        ui->radioButton_2->setChecked(true);
    }
    ui->lineEdit_10->setText(age);
    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(number);
    ui->lineEdit_3->setText(IPAddr);
    ui->lineEdit_6->setText(MAC);
    ui->lineEdit_4->setText(SubNetMask);
    ui->lineEdit_5->setText(From);
    ui->lineEdit_8->setText(zzmm);
    ui->lineEdit_9->setText(Contact);

    QMessageBox::information(this, tr("Success"), tr("Information loaded successfully from ") + fileName);
}


void Widget::on_pushButton_3_clicked()//弹出一个非模态对话窗口
{
    QDialog *dia=new QDialog(this);
    dia->resize(400,300);
    dia->setWindowTitle(QString::fromLocal8Bit("非模态对话窗口"));
    dia->setAttribute(Qt::WA_DeleteOnClose);//!!!对于非模态对话窗口，关闭窗口后并不会释放在堆区开辟的资源。因此，需要通过setAttribute设置
    dia->show();
}

