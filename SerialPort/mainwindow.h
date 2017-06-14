#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();  //清空接收
    void on_sendButton_clicked();   //发送按钮

    //SerialPort
    void on_openButton_clicked();
    void on_findport_clicked();
    void SerialPort_Read_Data();

    //TCP
    void on_connnectButton_clicked();
    void TCP_Read_Data();

    void connectUpdata();
    void disconnectUpdata();
    void ErrorHandle(QAbstractSocket::SocketError);    //出现错误

    void on_openimage_clicked();

private:
    Ui::MainWindow *ui;

    void Read_Data(QByteArray buf);   //公共的数据处理函数

    //字符串转16进制
    void StringToHex(QString str, QByteArray &senddata);
    char ConvertHexChar(char ch);

    //SerialPort
    QSerialPort *serial;
    bool SerialPortReady_Flag;

    void SerialPort_Init();
    void SerialPort_Send(QByteArray data);

    //TCP
    QTcpSocket *tcpSocket;//直接建立TCP套接字类
    QString tcpIp;//存储IP地址
    QString tcpPort;//存储端口地址
    bool TCPReady_Flag;

    void TCP_Init();
    void TCP_Send(QByteArray data);

    //Image
    QImage DisImage;

    void Image_Init();

    void DisplayImage();
};

#endif // MAINWINDOW_H
