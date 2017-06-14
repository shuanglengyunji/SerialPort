#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#define Img_Width   48
#define Img_Height  40

void MainWindow::Image_Init()
{
    //构造DisImage初始化数组
    QByteArray imageByteArray(Img_Width*Img_Height*4,0x80); //设置初始颜色
    uchar* transData = (unsigned char*)imageByteArray.data();

    //用transData数组生成图像
    DisImage = QImage(transData, Img_Width, Img_Height, QImage::Format_RGB32);

    //变换大小并显示
    QImage* imgScaled = new QImage; //创建自动变换大小后的QImage对象
    *imgScaled = DisImage.scaled(ui->label_image->size(),Qt::KeepAspectRatio);
    ui->label_image->setPixmap(QPixmap::fromImage(*imgScaled)); //显示变换大小后的QImage对象
    delete imgScaled;

}

void MainWindow::DisplayImage()
{

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
