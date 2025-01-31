#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->textEdit->setReadOnly(true);
    QMenuBar * MenuBar = new QMenuBar(this); //
    this->setMenuBar(MenuBar);
    this->setWindowTitle(QString::fromLocal8Bit("计算器"));
    this->setWindowIcon(QIcon(":/Pic/D:/Pictures/OIP-C.jpg"));
    //创建菜单
    QMenu *menu1 = new QMenu(QString::fromLocal8Bit("编辑(E)"),this);
    QMenu *menu2 = new QMenu(QString::fromLocal8Bit("查看(V)"),this);
    QMenu *menu3 = new QMenu(QString::fromLocal8Bit("帮助(H)"),this);


    //菜单栏添加菜单
    MenuBar->addMenu(menu1);
    MenuBar->addMenu(menu2);
    MenuBar->addMenu(menu3);

    //创建菜单项
    QAction *action1 = new QAction(QString::fromLocal8Bit("新建文件或项目"),this);//
    QAction *action2 = new QAction(QString::fromLocal8Bit("打开文件或项目"),this);

    //菜单添加菜单项
    menu1->addAction(action1);
    menu1->addAction(action2);
    menu1->addSeparator();//插入分割线

    // 连接数字按钮和操作按钮到同一个槽
    QList<QPushButton*> buttons = {
        ui->pushButton,      // 1
        ui->pushButton_2,    // 2
        ui->pushButton_3,    // 3
        ui->pushButton_4,    // 4
        ui->pushButton_5,    // 5
        ui->pushButton_6,    // 6
        ui->pushButton_7,    // 7
        ui->pushButton_8,    // 8
        ui->pushButton_9,    // 9
        ui->pushButton_0,    // 0
        ui->pushButton_10,   // .
        ui->pushButton_11,   // +
        ui->pushButton_14,   // -
        ui->pushButton_15,   // *
        ui->pushButton_16,   // /
        ui->pushButton_17    // %
    };

    for(auto button : buttons){
        connect(button, &QPushButton::clicked, this, &MainWindow::onDigitOrOperatorClicked);
    }
    connect(ui->pushButton_13,&QPushButton::clicked,this,&MainWindow::onCleanClicked);
    // 连接等号按钮到计算结果的槽
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);//
    updateFunctionButtons();

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onDigitOrOperatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button){
        QString text = button->text();//获取按钮文本
        currentExpression += text;
        ui->textEdit->setText(currentExpression);
        updateFunctionButtons();
    }
}


void MainWindow::onEqualsClicked()
{
    if(currentExpression.isEmpty()){
        return;
    }

    bool ok;
    double result = evaluateExpression(currentExpression, ok);
    if(ok){
        ui->textEdit->append("\n" + QString::number(result));
        currentExpression = QString::number(result);
    }
    else{
        onCleanClicked();
        if(result==0){
        QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("除数不能为零。"));
        }
        else{
            QMessageBox::warning(this, "计算错误", "表达式无效或无法计算。");
        }
    }
}


double MainWindow::evaluateExpression(const QString &expr, bool &ok) // 表达式求值
{
    // 使用栈实现逆波兰表达式求值
    QStack<double> operands;
    QStack<QChar> operators;

    //使用lambda表达式
    // 定义运算符优先级
    auto precedence = [](QChar op) -> int { //返回类型为int
        if(op == '+' || op == '-') return 1;
        if(op == '*' || op == '/' || op == '%') return 2;
        return 0;
    };

    // 定义运算函数
    auto applyOp = [&](QChar op, double a, double b) -> double {
        switch(op.toLatin1()){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if(b != 0){
                return a / b;
            } else {
                ok = false; // 设置错误标志
                return 0;   // 返回默认值
            }
        case '%':
            if(b != 0){
                return static_cast<int>(a) % static_cast<int>(b);
            } else {
                ok = false; // 设置错误标志
                return 0;   // 返回默认值
            }
        default:
            ok = false; // 未知运算符，设置错误标志
            return 0;
        }
    };

    // 初始化 ok 为 true
    ok = true;

    // 解析表达式
    QRegExp tokenRegex("(\\d+\\.\\d+)|(\\d+)|([+\\-*/%])");//解析数字和运算符
    int pos = 0;
    while(pos < expr.length()){
        if(expr[pos].isSpace()){ //遇到空格跳过
            pos++;
            continue;
        }

        if(expr[pos].isDigit() || expr[pos] == '.'){
            // 解析数字
            if(tokenRegex.indexIn(expr, pos) == pos){ //成功匹配一个数字
                QString numberStr = tokenRegex.cap(0);//捕获
                bool okNum;
                double number = numberStr.toDouble(&okNum);
                if(!okNum){
                    ok = false;
                    return 0;
                }
                operands.push(number);//入栈
                pos += numberStr.length();//移动下标
            }
            else{
                ok = false;
                return 0;
            }
        }
        else if(QString("+-*/%").contains(expr[pos])){
            //解析运算符
            QChar currentOp = expr[pos];
            while(!operators.isEmpty() && precedence(operators.top()) >= precedence(currentOp)){//如果栈顶运算符的优先级大于或等于当前运算符的优先级（>=），则需要先对栈中的运算符进行运算（因为优先级高的运算符需要先执行）
                if(operands.size() < 2){//是否有足够的操作数（至少需要2个）
                    ok = false;
                    return 0;
                }
                //出栈
                double b = operands.pop();
                double a = operands.pop();
                QChar op = operators.pop();
                double res = applyOp(op, a, b);
                //新的运算数入栈
                operands.push(res);
                if(!ok){
                    return 0;
                }
            }
            operators.push(currentOp);
            pos++;//移动下标，处理下一个字符
        }
        else{
            // 无效字符
            ok = false;
            return 0;
        }
    }

    // 处理剩余的运算符
    while(!operators.isEmpty()){
        if(operands.size() < 2){
            ok = false;
            return 0;
        }
        double b = operands.pop();
        double a = operands.pop();
        QChar op = operators.pop();
        double res = applyOp(op, a, b);
        operands.push(res);
        if(!ok){
            return 0;
        }
    }

    if(operands.size() != 1){ //最后运算数栈中应该只剩下一个元素
        ok = false;
        return 0;
    }

    return operands.pop();
}


void MainWindow::onCleanClicked(){
    currentExpression.clear();
    ui->textEdit->clear();
    updateFunctionButtons();
}

void MainWindow::updateFunctionButtons()
{
    bool hasInput = !currentExpression.isEmpty();//判空，若无输入，禁用功能按钮
    // 启用或禁用运算符按钮和等号按钮
    ui->pushButton_11->setEnabled(hasInput); // +
    ui->pushButton_14->setEnabled(hasInput); // -
    ui->pushButton_15->setEnabled(hasInput); // *
    ui->pushButton_16->setEnabled(hasInput); // /
    ui->pushButton_17->setEnabled(hasInput); // %
    ui->pushButton_12->setEnabled(hasInput); // =
}
