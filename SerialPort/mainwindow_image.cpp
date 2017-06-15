#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>



void MainWindow::Image_Init()
{
    //初始化图像数组
    for(int i=0;i<Img_Size;i++)
    {
        imageByteArray[i] = i/45;
    }

    //显示imageByteArray中存储的图像
    DisplayImage();

    QTimer *testTimer = new QTimer(this);    //创建定时器
    connect( testTimer,SIGNAL(timeout()), this, SLOT(testFunction()) ); //将定时器超时信号与槽(功能函数)联系起来
    testTimer->start(10); //开始运行定时器，定时时间间隔为1000ms

}

void MainWindow::testFunction()
{
    for(int i=0;i<Img_Size;i++)
    {
        imageByteArray[i]++;
    }
    DisplayImage();
}

void MainWindow::DisplayImage()
{
    //DisImage变换大小并存入imgScaled
    imgScaled = QImage(imageByteArray, Img_Width, Img_Height, QImage::Format_RGB888).scaled(ui->label_image->size(),Qt::KeepAspectRatio);
    ui->label_image->setPixmap(QPixmap::fromImage(imgScaled)); //显示变换大小后的QImage对象
}

void MainWindow::on_openimage_clicked()
{
    DisplayImage();
}



//    //获取文件路径
//    QString filename;
//    filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
//    if(filename.isEmpty())
//    {
//         return;
//    }

//    //打开图片
//    QImage* img=new QImage;
//    if(! ( img->load(filename) ) ) //加载图像到QImage对象
//    {
//        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
//        delete img;
//        return;
//    }
