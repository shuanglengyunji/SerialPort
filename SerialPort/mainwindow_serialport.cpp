#include "mainwindow.h"
#include "ui_mainwindow.h"

//读取并处理接收到的数据
void MainWindow::SerialPort_Read_Data()
{
    //读入数据并处理
    QByteArray buf = serial->readAll();    //读入全部数据
    if(!buf.isEmpty())
    {
        Read_Data(buf);
    }
    buf.clear();
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
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::SerialPort_Read_Data);

        SerialPortReady_Flag = true;    //串口状态标志
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

        SerialPortReady_Flag = false;
    }
}

//更新可用串口列表
void MainWindow::on_findport_clicked()
{
    //清空COM口列表
    ui->PortBox->clear();

    //把所有能用的端口都加入列表，不管是否被占用
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        ui->PortBox->addItem(serial.portName());
    }
}

//串口功能初始化
void MainWindow::SerialPort_Init()
{
    //把所有能用的端口都加入列表，不管是否被占用
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        ui->PortBox->addItem(serial.portName());
    }

    SerialPortReady_Flag = false;
}
