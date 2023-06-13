#include "screencapture.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QClipboard>

ScreenCapture::ScreenCapture(QWidget *parent){}

//初步完成截取屏幕后保存QPixmap文件到剪贴板
void ScreenCapture::shotFullScreen()
{
    m_screen = QGuiApplication::primaryScreen();
    QRect rect = m_screen->geometry();  //获取屏幕尺寸
    QPixmap screenshot = m_screen->grabWindow(0,0,0,rect.width(),rect.height());
    m_clipBoard = QGuiApplication::clipboard();    //调用系统剪贴板
    m_clipBoard->setPixmap(screenshot);  //保存到剪贴板
}
