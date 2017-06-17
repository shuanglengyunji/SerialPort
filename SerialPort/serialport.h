#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

class SerialPort : public QMainWindow
{
    Q_OBJECT
public:
    explicit SerialPort(QWidget *parent = nullptr);

    bool SerialPortReady_Flag;  //用于指示串口是否打开

signals:

public slots:
    void refresh();         //刷新串口列表
    void SerialPort_Read();
    void SerialPort_Send(QByteArray data);
    void OpenSerialport(int baud);
    void CloseSerialport();

private:
    QSerialPort *serial;



};

#endif // SERIALPORT_H
