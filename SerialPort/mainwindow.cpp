#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //关闭发送按钮的使能
    ui->sendButton->setEnabled(false);

    //串口相关功能初始化
    SerialPort_Init();

    //TCP功能初始化
    TCP_Init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//清空接受窗口
void MainWindow::on_clearButton_clicked()
{
    ui->ReceiveBox->clear();
}

//发送数据按钮
void MainWindow::on_sendButton_clicked()
{
    //serial是窗口类中定义的，这个窗口里的所有对象都可以用
    //这里是调用串口对象的write函数来发送数据
    serial->write(ui->SendBox->toPlainText().toLatin1());
}

