#include "serialport.h"

SerialPort::SerialPort(QWidget *parent) : QMainWindow(parent)
{
    //把所有能用的端口都加入列表，不管是否被占用
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
//        ui->PortBox->addItem(serial.portName());
    }

    SerialPortReady_Flag = false;
}


//读取并处理接收到的数据
void SerialPort::SerialPort_Read()
{
    //读入数据并处理
    QByteArray buf = serial->readAll();    //读入全部数据
    if(!buf.isEmpty())
    {
//        Read_Data(buf);
    }
    buf.clear();
}

//串口发送
void SerialPort::SerialPort_Send(QByteArray data)
{
    serial->write(data);
}

//打开串口按钮
void SerialPort::OpenSerialport(int baud)
{

    //serial是定义的串口对象指针

    serial = new QSerialPort;   //创建一个串口对象
    if(!serial->open(QIODevice::ReadWrite))//打开串口
    {
        QMessageBox::information(this,tr("Error"),tr("COM口打开失败！端口已被占用或端口不存在。"),QMessageBox::Ok);
        return;
    }

    //设置波特率
    serial->setBaudRate(baud);    //从BaudBox读取波特率，设置到serial

    //默认使用8数据，无校验，1停止

    //设置数据位数
    serial->setDataBits(QSerialPort::Data8);

    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);

    //设置停止位
    serial->setStopBits(QSerialPort::OneStop);

    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);

    //连接信号槽

    //接收信号：serial的readyRead事件连接到Read_Data函数
//    QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::SerialPort_Read_Data);

    SerialPortReady_Flag = true;    //串口状态标志

}

void SerialPort::CloseSerialport()
{
    //关闭串口
    serial->close();

//    QObject::disconnect(serial, &QSerialPort::readyRead, this, &MainWindow::SerialPort_Read_Data);

    serial->clear();
    serial->deleteLater();

    SerialPortReady_Flag = false;
}

void SerialPort::refresh()
{
    //把所有能用的端口都加入列表，不管是否被占用
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
//        ui->PortBox->addItem(serial.portName());
    }
}


