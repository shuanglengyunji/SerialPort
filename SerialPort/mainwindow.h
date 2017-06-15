#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTimer>

#define Img_Width   48
#define Img_Height  40
#define Img_Size    Img_Width*Img_Height*3

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

    //Image
    void on_openimage_clicked();

    void testFunction();

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


    //构造DisImage初始化数组
    unsigned char imageByteArray[Img_Size];  //图像像素数组
    QImage DisImage;        //像素数组生成的QImage对象
    QImage imgScaled;       //DisImage缩放后实际显示的图像

    void Image_Init();

    void DisplayImage();
};

#endif // MAINWINDOW_H
