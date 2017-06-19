#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTimer>
#include <QThread>

#include "serialport.h"

#define Img_Width       80
#define Img_Height      48
#define Img_Size        Img_Width*Img_Height
#define Img_Buf_Size    Img_Size*3

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void StringToHex(QString str, QByteArray &senddata);    //字符串转16进制
    char ConvertHexChar(char ch);

/*UI*/
signals:
private slots:
    void on_Tab_Function_currentChanged(int index);
private:
    Ui::MainWindow *ui;
    void Tab_Init();
    int Tab_Num;

//Settting
signals:
    void refresh_serialport_name();
private slots:
    void on_openButton_clicked();   //开启窗口按钮
    void on_findport_clicked();     //搜索串口按钮
    void on_connnectButton_clicked();   //连接按钮
    void add_portbox_item(QString PortName);    //向可用串口列表添加内容
private:
    void disable_serialport_setting_panel();
    void enable_serialport_setting_panel();

//Image
signals:
private slots:
    void on_pathchangeButton_clicked();                 //路径选择
    void on_checkBox_imagesave_stateChanged(int arg1);  //保存图片
    void on_numberclearButton_clicked();                //清空计数
    void on_openimage_clicked();
    void testFunction();
    void Image_Read_Data(unsigned char data);
private:
    QString file_path;  //文件保存路径
    bool image_save_flag;
    int image_counter;
    unsigned char imageTmpArray[Img_Size];      //临时存储发来的图像数据用的数组
    unsigned char imageByteArray[Img_Buf_Size];  //图像像素数组
    QImage DisImage;        //像素数组生成的QImage对象
    QImage imgScaled;       //DisImage缩放后实际显示的图像
    void Image_Init();
    void DisplayImage();
    void GetImage();

//DataDisplay
signals:
    void Datadisplay_signal(unsigned char data);   //数据监控窗口的数据发送信号
private slots:
    void on_clearButton_clicked();  //清空接收
    void on_sendButton_clicked();   //发送按钮
    void Datadisplay_Read_Data(unsigned char data);   //数据监控窗口的数据输入信号
private:


/*SerialPort*/
//signals:
//    void SeriPort_signal(unsigned char data);
//    void SeriPort_Refesh_signal(QString PortName);  //发送可用串口名称
//private slots:
//    void SerialPort_Read_Data();    //串口读取数据槽函数（连接至串口控件收到数据信号）
//    void SerialPort_Send_Data(unsigned char data);
//    void SerialPort_Open(QString PortName, int Baud, int BitNum, int Parity, int StopBitNum);
//    void SerialPort_Close();
//    void SerialPort_Refresh();
//private:
//    QSerialPort *serial;
//    bool SerialPortReady_Flag;
//    void SerialPort_Init();

/*TCP*/
signals:
    void TCP_signal(unsigned char data);
private slots:
    void TCP_Read_Data();       //接收到数据
    void TCP_Send_Data(unsigned char data);

    void connectUpdata();       //连接成功后通过槽调用此函数，表示连接成功，并进行相关处理
    void disconnectUpdata();    //断开连接成功处理
    void ErrorHandle(QAbstractSocket::SocketError);    //出现错误
private:
    QTcpSocket *tcpSocket;//直接建立TCP套接字类
    QString tcpIp;//存储IP地址
    QString tcpPort;//存储端口地址
    bool TCPReady_Flag;
    void TCP_Init();

    SerialPort port;

};

#endif // MAINWINDOW_H
