#include "mainwindow.h"
#include "ui_mainwindow.h"


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

void MainWindow::enable_serialport_setting_panel()
{
    ui->PortBox->setEnabled(true);
    ui->BaudBox->setEnabled(true);
    ui->BitNumBox->setEnabled(true);
    ui->ParityBox->setEnabled(true);
    ui->StopBox->setEnabled(true);
    ui->findport->setEnabled(true);
    ui->sendButton->setEnabled(false);

    ui->openButton->setText(tr("打开串口"));
}
