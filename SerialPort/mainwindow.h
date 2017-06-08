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

private:
    Ui::MainWindow *ui;

    //SerialPort
    QSerialPort *serial;

    void SerialPort_Init(void);

    //TCP功能
    QTcpSocket *tcpSocket;//直接建立TCP套接字类
    QString tcpIp;//存储IP地址
    QString tcpPort;//存储端口地址
    bool TCPReady_Flag;

    void TCP_Init();
};

#endif // MAINWINDOW_H
