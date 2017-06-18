#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::TCP_Init()
{
    TCPReady_Flag = false;

    //输入初始IP和端口
    ui->IPLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("777");

    //TCP套接字类指针
    tcpSocket = NULL;//使用前先清空
}

void MainWindow::on_connnectButton_clicked()
{
    if(!TCPReady_Flag)
    {
        //创建TCP类
        if(tcpSocket) delete tcpSocket;//如果有指向其他空间直接删除
        tcpSocket = new QTcpSocket(this);//申请堆空间有TCP发送和接受操作

        //获取IP和Port字符串并判断是否可用
        tcpIp = ui->IPLineEdit->text();
        tcpPort = ui->portLineEdit->text();
        if(tcpIp==NULL||tcpPort==NULL)//判断IP和PORT是否为空
        {
            QMessageBox msgBox;
            msgBox.setText("IP or PORT is Empty");
            msgBox.exec();
            return;
        }

        //根据tcpIp连接主机
        tcpSocket->connectToHost(tcpIp,tcpPort.toInt());//连接主机

        //建立槽

        //连接成功信号
        //connected()信号是在成功建立同host的连接后发出的
        connect(tcpSocket,SIGNAL(connected()),this,SLOT(connectUpdata()));
    }
    else
    {
        tcpSocket->abort();
        tcpSocket->deleteLater();   //这个删除方式更温和一些
        tcpSocket=NULL;

        disconnectUpdata();
    }

}

//TCP接收
void MainWindow::TCP_Read_Data()
{
    //读入数据并处理
    QByteArray buf = tcpSocket->readAll();    //读入全部数据
    if(!buf.isEmpty())
    {
        //获取长度
        int size = buf.size();

        //按字节发出
        for(int i=0;i<size;i++)
        {
            emit TCP_signal((unsigned char)buf[i]); //数据转发给程序
        }
    }
    buf.clear();
}

//TCP发送
void MainWindow::TCP_Send_Data(unsigned char data)
{
    QByteArray tmp(1,data);
    tcpSocket->write(tmp);
}

//连接成功后通过槽调用此函数，处理按钮状态的改变
void MainWindow::connectUpdata()
{
    ui->connnectButton->setText("断开连接");  //连接
    ui->IPLineEdit->setEnabled(false);      //地址框编辑禁止
    ui->portLineEdit->setEnabled(false);    //端口号编辑禁止

    TCPReady_Flag=true;

    //读取信息信号
    //收到信息时发出readyRead()信号
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(TCP_Read_Data()));  //TCP对象给信号用的槽
    connect(this,TCP_signal,this,Datadisplay_Read_Data);    //向程序内发送的信号连接到数据监控窗口
    connect(this,TCP_signal,this,Image_Read_Data);          //向程序内发送信号的槽连接到图像显示窗口
    connect(this,Datadisplay_signal,this,TCP_Send_Data);    //从程序中接收数据的槽

    //错误信号
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ErrorHandle(QAbstractSocket::SocketError)));

}

//断开连接函数
void MainWindow::disconnectUpdata()
{
    ui->connnectButton->setText("连接");
    ui->IPLineEdit->setEnabled(true);
    ui->portLineEdit->setEnabled(true);

    TCPReady_Flag=false;
}

//处理错误
void MainWindow::ErrorHandle(QAbstractSocket::SocketError)
{
    QMessageBox::warning (this, tr("Warnning"), tcpSocket->errorString ());
    tcpSocket->close();

    ui->connnectButton->setText("连接");
    ui->portLineEdit->setEnabled(true);
    ui->IPLineEdit->setEnabled(true);

    TCPReady_Flag = false;
}
