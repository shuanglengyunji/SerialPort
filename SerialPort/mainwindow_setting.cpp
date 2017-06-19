#include "mainwindow.h"
#include "ui_mainwindow.h"

//打开串口按钮
void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text()==tr("打开串口"))
    {
        //获取串口设置参数
        QString Port = ui->PortBox->currentText();
        int Baud = ui->BaudBox->currentText().toInt();
        int BitNum = ui->BitNumBox->currentIndex();
        int Parity = ui->ParityBox->currentIndex();
        int StopBitNum = ui->StopBox->currentIndex();

        //打开串口
        if(!port.SerialPort_Open(Port,Baud,BitNum,Parity,StopBitNum))
            return;

        //禁用设置菜单
        disable_serialport_setting_panel();
    }
    else
    {
        //关闭串口
        if(!port.SerialPort_Close())
            return;

        //恢复设置使能
        enable_serialport_setting_panel();
    }
}

//更新可用串口列表按钮
void MainWindow::on_findport_clicked()
{
    //清空COM口列表
    ui->PortBox->clear();

    emit refresh_serialport_name();
}

//将发来的可用串口号加入下拉菜单
void MainWindow::add_portbox_item(QString PortName)
{
    ui->PortBox->addItem(PortName);
}

//打开串口后的处理（关闭串口设置面板）
void MainWindow::disable_serialport_setting_panel()
{
    ui->PortBox->setEnabled(false);
    ui->BaudBox->setEnabled(false);
    ui->BitNumBox->setEnabled(false);
    ui->ParityBox->setEnabled(false);
    ui->StopBox->setEnabled(false);
    ui->findport->setEnabled(false);

    ui->openButton->setText(tr("关闭串口"));
}

//关闭串口后的处理（启用串口设置面板）
void MainWindow::enable_serialport_setting_panel()
{
    ui->PortBox->setEnabled(true);
    ui->BaudBox->setEnabled(true);
    ui->BitNumBox->setEnabled(true);
    ui->ParityBox->setEnabled(true);
    ui->StopBox->setEnabled(true);
    ui->findport->setEnabled(true);

    ui->openButton->setText(tr("打开串口"));
}
