#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    //查找可用的串口
//    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//    {
//        QSerialPort serial;
//        serial.setPort(info);
//        if(serial.open(QIODevice::ReadWrite))
//        {
//            ui->PortBox->addItem(serial.portName());
//            serial.close();
//        }
//    }

    //把所有能用的端口都加入列表，不管是否被占用
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        ui->PortBox->addItem(serial.portName());
    }

    //设置波特率下拉菜单默认显示第0项
    ui->BaudBox->setCurrentIndex(0);

    //关闭发送按钮的使能
    ui->sendButton->setEnabled(false);

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

//读取接收到的数据
void MainWindow::Read_Data()
{
    //读入数据并处理
    QByteArray buf = serial->readAll();    //读入全部数据
    if(!buf.isEmpty())
    {
        //存入char数组，读取数组长度
        unsigned char *data = (unsigned char *)buf.data();
        int size = buf.size();

        //把接收到的16进制数显示在窗口上
        QString str;
        for(int i=0;i<size;i++)
        {
            str += QString::number(data[i], 16).toUpper();
            str += " ";
        }
        ui->ReceiveBox->append(str);                  //显示全部内容
        str.clear();

        delete [] data;  //清除数组空间
    }
    buf.clear();

    //检查对话框中的数据量，过大则清除
    if(ui->ReceiveBox->toPlainText().length()>2000)
        ui->ReceiveBox->clear();
}

//打开串口按钮
void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text()==tr("打开串口"))
    {
        //serial是定义的串口对象指针

        serial = new QSerialPort;   //创建一个串口对象
        serial->setPortName(ui->PortBox->currentText());//设置串口名
        if(!serial->open(QIODevice::ReadWrite))//打开串口
        {
            QMessageBox::information(this,tr("Error"),tr("COM口打开失败！端口已被占用或端口不存在。"),QMessageBox::Ok);
            return;
        }

        //设置波特率
        serial->setBaudRate(ui->BaudBox->currentText().toInt());    //从BaudBox读取波特率，设置到serial
        //设置数据位数
        switch(ui->BitNumBox->currentIndex())
        {
            case 8: serial->setDataBits(QSerialPort::Data8); break;
            default: break;
        }
        //设置奇偶校验
        switch(ui->ParityBox->currentIndex())
        {
            case 0: serial->setParity(QSerialPort::NoParity); break;
            default: break;
        }
        //设置停止位
        switch(ui->StopBox->currentIndex())
        {
            case 1: serial->setStopBits(QSerialPort::OneStop); break;
            case 2: serial->setStopBits(QSerialPort::TwoStop); break;
            default: break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitNumBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->findport->setEnabled(false);
        ui->openButton->setText(tr("关闭串口"));

        //使能发送按钮
        ui->sendButton->setEnabled(true);

        //连接信号槽

        //接收信号：serial的readyRead事件连接到Read_Data函数
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitNumBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->findport->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
        ui->sendButton->setEnabled(false);
    }
}

void MainWindow::on_findport_clicked()
{
    //清空列表
    ui->PortBox->clear();

    //把所有能用的端口都加入列表，不管是否被占用
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        ui->PortBox->addItem(serial.portName());
    }
}
