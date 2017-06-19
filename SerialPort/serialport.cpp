#include "serialport.h"

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    SerialPortReady_Flag = false;
}


//读取并处理接收到的数据（串口模块将从串口收到的数据发给程序）
void SerialPort::SerialPort_Read_Data()
{
    //读入数据并处理
    QByteArray buf = serial->readAll();    //读入全部数据
    if(!buf.isEmpty())
    {
        //获取长度
        int size = buf.size();

        //按字节发出
        for(int i=0;i<size;i++)
        {
            emit SeriPort_signal((unsigned char)buf[i]);    //数据转发给程序
        }
    }
    buf.clear();
}

//串口发送（串口模块收到程序给的数据）
void SerialPort::SerialPort_Send_Data(unsigned char data)
{
    QByteArray tmp(1,data);
    serial->write(tmp);
}

bool SerialPort::SerialPort_Close()
{
    if(!SerialPortReady_Flag)
        return false;

    //关闭串口
    serial->clear();
    serial->close();
    serial->deleteLater();

    SerialPortReady_Flag = false;

    return true;
}

bool SerialPort::SerialPort_Open(QString PortName,int Baud,int BitNum,int Parity,int StopBitNum)
{
    if(SerialPortReady_Flag)
        return false;

    //serial是定义的串口对象指针
    serial = new QSerialPort;   //创建一个串口对象

    //设置串口名
    serial->setPortName(PortName);

    if(!serial->open(QIODevice::ReadWrite))//打开串口
    {
        return false;
    }

    //设置波特率
    serial->setBaudRate(Baud);

    //设置数据位数
    switch(BitNum)
    {
        case 8: serial->setDataBits(QSerialPort::Data8); break;
        default: break;
    }

    //设置奇偶校验
    switch(Parity)
    {
        case 0: serial->setParity(QSerialPort::NoParity); break;
        default: break;
    }

    //设置停止位
    switch(StopBitNum)
    {
        case 1: serial->setStopBits(QSerialPort::OneStop); break;
        case 2: serial->setStopBits(QSerialPort::TwoStop); break;
        default: break;
    }

    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);

    //连接信号槽
    //接收信号：serial的readyRead事件连接到Read_Data函数
    connect(serial, &QSerialPort::readyRead, this, &SerialPort::SerialPort_Read_Data);

    SerialPortReady_Flag = true;    //串口状态标志

    return true;
}

void SerialPort::SerialPort_Refresh()
{
    //把所有能用的端口都列出
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        emit SeriPort_Refesh_signal(serial.portName()); //发送信号
    }
}


