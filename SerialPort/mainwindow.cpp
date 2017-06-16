#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //关闭发送按钮的使能
    ui->sendButton->setEnabled(false);

    //串口相关功能初始化
    SerialPort_Init();

    //TCP功能初始化
    TCP_Init();

    //显示图像功能初始化
    Image_Init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//字符串转16进制（处理字符串部分）
void MainWindow::StringToHex(QString str, QByteArray &senddata) //字符串转换为十六进制数据0-F
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;

    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();

        //忽略空格
        if(hstr == ' ')
        {
            i++;
            continue;
        }

        //长度计数
        i++;
        if(i >= len)
            break;

        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);

        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;

        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

//字符串转16进制（ASCII码转换部分）
char MainWindow::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return ch-ch;//不在0-f范围内的会发送成0
}

//清空接受窗口
void MainWindow::on_clearButton_clicked()
{
    ui->ReceiveBox->clear();
}

//发送数据按钮
void MainWindow::on_sendButton_clicked()
{
    QString str = ui->SendBox->text();//从LineEdit得到字符串

    int len = str.length();
    if(len%2 == 1)   //如果发送的数据个数为奇数的，则在前面最后落单的字符前添加一个字符0
    {
        str = str.insert(len-1,'0'); //insert(int position, const QString & str)
    }

    QByteArray data;
    StringToHex(str,data);//将str字符串转换为16进制的形式

    if(TCPReady_Flag)
        TCP_Send(data);

    if(SerialPortReady_Flag)
        SerialPort_Send(data);
}

//所以接收到的数据会被传输到这个函数中处理
void MainWindow::Read_Data(QByteArray buf)
{
    //buf存入char数组，读取数组长度
    int size = buf.size();

    //把接收到的16进制数显示在窗口上
    QString str;
    for(int i=0;i<size;i++)
    {
        str += QString::number(buf[i], 16).toUpper();
        str += " ";
    }
    ui->ReceiveBox->append(str);                  //显示全部内容
    str.clear();

    buf.clear();

    //检查对话框中的数据量，过大则清除
    if(ui->ReceiveBox->toPlainText().length()>2000)
        ui->ReceiveBox->clear();
}


