#include "screencapture.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QClipboard>
#include <QRectF>
#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QDebug>

ScreenCapture::ScreenCapture(QWidget *parent)
    :provider(new SelectImageProvider)
{}

//初步完成截取屏幕后保存QPixmap文件到剪贴板
void ScreenCapture::shotFullScreen()
{
    m_screen = QGuiApplication::primaryScreen();
    QRect rect = m_screen->geometry();  //获取屏幕尺寸
    QPixmap screenshot = m_screen->grabWindow(0,0,0,rect.width(),rect.height());
    m_clipBoard = QGuiApplication::clipboard();    //调用系统剪贴板
    m_clipBoard->setPixmap(screenshot);  //保存到剪贴板
    provider->pixmap = screenshot;  //图片提供者
    m_currentPic = &screenshot;     //保存当前图片，为支持‘保存’功能
}

//自由不规则区域截取，测试。。。
//void ScreenCapture::shotIrregular()
//{
//    // 定义选取框
//    QRectF selectRect;

//    // 定义画笔
//    QPen pen;
//    pen.setWidth(2);
//    pen.setColor(Qt::red);

//    // 定义画刷
//    QBrush brush;
//    brush.setColor(Qt::red);
//    brush.setStyle(Qt::DiagCrossPattern);

//    // 定义PainterPath，并画出选取框
//    QPainterPath path;
//    path.addRect(selectRect);
//    painter.setPen(pen);
//    painter.setBrush(brush);
//    painter.drawPath(path);

//    // 进行截图
//    QPixmap screenshot = widget->grab(selectRect.toRect());
//}
