#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);

signals:
    void SeriPort_signal(unsigned char data);
    void SeriPort_Refesh_signal(QString PortName);  //发送可用串口名称
public slots:
    void SerialPort_Read_Data();    //串口读取数据槽函数（连接至串口控件收到数据信号）
    void SerialPort_Send_Data(unsigned char data);
    void SerialPort_Open(QString PortName, int Baud, int BitNum, int Parity, int StopBitNum);
    void SerialPort_Close();
    void SerialPort_Refresh();
private:
    QSerialPort *serial;
    bool SerialPortReady_Flag;
};

#endif // SERIALPORT_H
