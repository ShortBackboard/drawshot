/*
 * author: liChengYang2019051604044
 * date: 2023-6-21
 * Area ScreenRecord
 */
#include "arearecord.h"
#include <QApplication>
#include <QScreen>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMouseEvent>
#include <QDialog>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>

//初始化布局
AreaRecord::AreaRecord(QWidget *parent):QWidget(parent){
    setObjectName(tr("GifWidget"));
    resize(800,600);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);//垂直布局
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0,0,0,0);

    widgetMain = new QWidget(this);//主窗口
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(widgetMain->sizePolicy().hasHeightForWidth());
    widgetMain->setSizePolicy(sizePolicy1);
    verticalLayout->addWidget(widgetMain);

    widgetBottom = new QWidget(this);//底部工具栏
    widgetBottom->setMinimumSize(0, 45);
    widgetBottom->setMaximumSize(8000, 45);

    //底部工具栏布局
    QHBoxLayout *layoutBottom = new QHBoxLayout(widgetBottom);
    layoutBottom->setSpacing(6);
    layoutBottom->setContentsMargins(9,9,-1,-1);

    QLabel *labFps = new QLabel(widgetBottom);//帧率
    layoutBottom->addWidget(labFps);

    txtFps = new QLineEdit(widgetBottom);//帧率文本框
    txtFps->setMaximumSize(50, 12580);
    txtFps->setAlignment(Qt::AlignCenter);
    layoutBottom->addWidget(txtFps);

    QLabel *labWidth = new QLabel(widgetBottom);//宽度
    layoutBottom->addWidget(labWidth);

    txtWidth = new QLineEdit(widgetBottom);//宽度文本框
    txtWidth->setEnabled(true);
    txtWidth->setMaximumSize(50, 12580);
    txtWidth->setAlignment(Qt::AlignCenter);
    layoutBottom->addWidget(txtWidth);

    QLabel *labHeight = new QLabel(widgetBottom);//高度
    layoutBottom->addWidget(labHeight);

    txtHeight = new QLineEdit(widgetBottom);//高度文本框
    txtHeight->setEnabled(true);
    txtHeight->setMaximumSize(50, 12580);
    txtHeight->setAlignment(Qt::AlignCenter);
    layoutBottom->addWidget(txtHeight);

    labStatus = new QLabel(widgetBottom);//截屏时提示信息
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setHeightForWidth(labStatus->sizePolicy().hasHeightForWidth());
    sizePolicy2.setVerticalStretch(0);
    labStatus->setSizePolicy(sizePolicy2);
    layoutBottom->addWidget(labStatus);

    btnStart = new QPushButton(widgetBottom);//开始按钮
    QSizePolicy sizePolicy;
    sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
    btnStart->setSizePolicy(sizePolicy);
    layoutBottom->addWidget(btnStart);

    QPushButton *btnClose = new QPushButton(widgetBottom);//关闭按钮
    sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
    btnStart->setSizePolicy(sizePolicy);
    layoutBottom->addWidget(btnClose);

    verticalLayout->addWidget(widgetBottom);


    labFps->setText(tr("帧率"));
    labWidth->setText(tr("宽度"));
    labHeight->setText(tr("高度"));
    btnStart->setText(tr("开始"));
    btnClose->setText(tr("关闭"));

    connect(btnStart, SIGNAL(clicked()), this, SLOT(record()));
    connect(txtWidth, SIGNAL(editingFinished()), this, SLOT(resizeForm()));
    connect(txtHeight, SIGNAL(editingFinished()), this, SLOT(resizeForm()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(closeAll()));

    borderWidth = 1;
    bgColor = QColor("grey");

    fps = 10;
    txtFps->setText(QString::number(fps));
    gifWriter = 0;

    //1s后开始录屏
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &AreaRecord::saveImage);

    setAttribute(Qt::WA_TranslucentBackground);//指示小部件具有半透明背景
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);//生成无边框窗口 || 保持在所有其他窗口的顶部
    installEventFilter(this);


    txtWidth->setEnabled(true);
    txtHeight->setEnabled(true);

    labStatus->setObjectName("labStatus");
}


//保存GIF
void AreaRecord::saveImage(){
    if(!gifWriter){
        return;
    }

    QScreen *screen = QApplication::primaryScreen();
    QPixmap pix = screen->grabWindow(0, x() + rectGif.x(), y() + rectGif.y(), rectGif.width(), rectGif.height());
    QImage image = pix.toImage().convertToFormat(QImage::Format_RGBA8888);//该图像使用24位RGB格式（8-8-8）进行存储。

    gif.GifWriteFrame(gifWriter, image.bits(), rectGif.width(), rectGif.height(), fps);
    count++;
    labStatus->setText(QString("正在录制 第 %1 帧").arg(count));

}

//开始录屏
void AreaRecord::record(){
    if(btnStart->text() == "开始"){
        if (0 != gifWriter) {
            delete gifWriter;
            gifWriter = 0;
        }

        fileName = QFileDialog::getSaveFileName(this, "选择保存位置", qApp->applicationDirPath() + "/", "视频(*.mkv)");
        if (fileName.isEmpty()) {
            return;
        }

        int width = txtWidth->text().toInt();
        int height = txtHeight->text().toInt();
        fps = txtFps->text().toInt();

        gifWriter = new Gif::GifWriter;

        //Creates a gif file.
        bool bOk = gif.GifBegin(gifWriter, fileName.toLocal8Bit().data(), width, height, fps);
        if (!bOk) {
            delete gifWriter;
            gifWriter = 0;
            return;
        }

        count = 0;
        labStatus->setText("开始录制...");
        btnStart->setText("停止");
        //延时启动
        timer->setInterval(1000 / fps);
        QTimer::singleShot(1000, timer, SLOT(start()));
    } else {
        timer->stop();
        gif.GifEnd(gifWriter);

        delete gifWriter;
        gifWriter = 0;

        labStatus->setText(QString("录制完成 共 %1 帧").arg(count));
        btnStart->setText("开始");
        QDesktopServices::openUrl(QUrl(fileName));//自动打开录制文件
    }
}

//设置窗口状态
void AreaRecord::paintEvent(QPaintEvent *){
    int width = txtWidth->text().toInt();
    int height = txtHeight->text().toInt();

    rectGif = QRect(borderWidth,1, width-(borderWidth*2), height);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawRoundedRect(this->rect(), 5, 5);
    //定义数字图像合成支持的模式。组合模式用于指定如何将源图像中的像素与目标图像中的像素合并。
    painter.setCompositionMode(QPainter::CompositionMode_Clear);//目标中的像素被清除(设置为完全透明)，独立于源。
    painter.fillRect(rectGif, Qt::SolidPattern);
}


//关闭录制屏幕
void AreaRecord::closeAll(){
    close();
    emit finish();
}

//重新设置录屏区域大小
void AreaRecord::resizeForm(){
    int width = txtWidth->text().toInt();
    int height = txtHeight->text().toInt();
    resize(width, height+widgetBottom->height());
}


bool AreaRecord::eventFilter(QObject *watched, QEvent *e){
    static QPoint mousePoint;
    static bool mousePressed = false;

     QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
    if(mouseEvent->type() == QEvent::MouseButtonPress)
    {
        if(mouseEvent->button() == Qt::LeftButton)
        {
            mousePressed = true;
            mousePoint = mouseEvent->globalPosition().toPoint() - this->pos();
            return true;
        }
    }
    else if(mouseEvent->type() == QEvent::MouseButtonRelease)
    {
        mousePressed = false;
        return true;
    }
    else if(mouseEvent->type() == QEvent::MouseMove)
    {
        if(mousePressed)
        {
            this->move(mouseEvent->globalPosition().toPoint() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(watched, e);
}

//重置宽度高度文本内容
void AreaRecord::resizeEvent(QResizeEvent *){
    txtWidth->setText(QString::number(widgetMain->width()));
    txtHeight->setText(QString::number(widgetMain->height()));
}


AreaRecord::~AreaRecord(){
    delete widgetMain;  widgetMain=nullptr;
    delete widgetBottom; widgetBottom=nullptr;
    delete txtFps;    txtFps=nullptr;
    delete txtWidth; txtWidth=nullptr;
    delete txtHeight; txtHeight=nullptr;
    delete gifWriter; gifWriter=nullptr;
    delete btnStart; btnStart=nullptr;
    delete closeButton; closeButton=nullptr;
    delete labStatus; labStatus=nullptr;
    delete timer;  timer=nullptr;
}
















