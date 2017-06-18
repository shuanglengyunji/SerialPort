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
