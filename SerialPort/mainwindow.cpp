#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //界面整体初始化函数
    Tab_Init();

//    //串口相关功能初始化
//    SerialPort_Init();

    //TCP功能初始化
    TCP_Init();

    //显示图像功能初始化
    Image_Init();

    QThread * Portthread = new QThread(this);
    port.moveToThread(Portthread);
    Portthread->start();

    connect(this,SIGNAL(refresh_serialport_name()),&port,SLOT(SerialPort_Refresh()));  //连接到SerialPort的槽

    //port对象发送可用传口号
    connect(&port,SerialPort::SeriPort_Refesh_signal,this,MainWindow::add_portbox_item);

    //port对象发送
    connect(&port,SerialPort::SeriPort_signal,this,Datadisplay_Read_Data);
    connect(&port,SerialPort::SeriPort_signal,this,Image_Read_Data);          //向程序内发送信号的槽连接到图像显示窗口

    //向port发送内容
    connect(this,Datadisplay_signal,&port,SerialPort::SerialPort_Send_Data);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Tab_Init()
{
    //设置默认标签为标签1(Tab_Num是0)
    ui->Tab_Function->setCurrentWidget(ui->tab_1);

    Tab_Num = 0;        //从0开始编号
}

//识别当前界面Tab
void MainWindow::on_Tab_Function_currentChanged(int index)
{
    Tab_Num = index;
}
