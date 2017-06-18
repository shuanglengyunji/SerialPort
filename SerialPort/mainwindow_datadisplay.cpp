#include "mainwindow.h"
#include "ui_mainwindow.h"

//清空接收窗口
void MainWindow::on_clearButton_clicked()
{
    ui->ReceiveBox->clear();
}

//从发送窗口读取数据转发给程序其他部分
void MainWindow::on_sendButton_clicked()
{
    QString str = ui->SendBox->text();//从LineEdit得到字符串

    //删除空格
    str.remove(QChar(' '), Qt::CaseSensitive);

    //将str转换为16进制数，存入data
    int len = str.length();
    if(len%2 == 1)   //如果发送的数据个数为奇数的，则在前面最后落单的字符前添加一个字符0
    {
        str = str.insert(len-1,'0'); //insert(int position, const QString & str)
    }
    QByteArray data;
    StringToHex(str,data);//将str字符串转换为16进制的形式

    //将data逐个发送
    int size = data.size();
    for(int i=0;i<size;i++)
    {
        emit Datadisplay_signal(data[i]);    //将数据发送出去
    }
}

//接收转发来的数据显示在接收窗口
void MainWindow::Datadisplay_Read_Data(unsigned char data)
{
    //把接收到的16进制数显示在窗口上
    QString str = QString::number(data, 16).toUpper();
    ui->ReceiveBox->append(str);                  //显示全部内容

    //检查对话框中的数据量，过大则清除
    if(ui->ReceiveBox->toPlainText().length()>2000)
        ui->ReceiveBox->clear();
}
