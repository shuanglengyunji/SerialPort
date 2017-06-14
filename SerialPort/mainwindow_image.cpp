#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

void MainWindow::DisplayImage()
{
    int dstSize = 128;
    int wsize = dstSize * dstSize;    //文件大小

    QByteArray a(wsize*4,0xF0);
    QByteArray imageByteArray = a;
    uchar*  transData = (unsigned char*)imageByteArray.data();

    //用transData数组生成图像
    QImage image = QImage(transData, dstSize, dstSize, QImage::Format_RGB32);

    //创建自动变换大小后的QImage对象
    QImage* imgScaled = new QImage;
    *imgScaled = image.scaled(ui->label_image->size(),Qt::KeepAspectRatio);

    //显示变换大小后的QImage对象
    ui->label_image->setPixmap(QPixmap::fromImage(*imgScaled));

    delete imgScaled;

//    delete img;
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
