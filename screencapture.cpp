
/*
 * author: wanlukuan
 * date: 2023-6-14
 */
#include "screencapture.h"
#include "copypaintiitems.h"
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QClipboard>
#include <QDebug>
#include <QMainWindow>
#include <QApplication>
#include <X11/Xlib.h>
#include <QWindow>

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
    provider->pixmap = screenshot;  //设置图片提供者资源
    m_currentPic = &screenshot;     //保存当前图片，为支持‘保存’功能

    screenshot.save("temp.png");
}

void ScreenCapture::shotFullScreen(int x, int y, int w, int h)
{
    m_screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = m_screen->grabWindow(0,x,y,w,h);
    m_clipBoard = QGuiApplication::clipboard();    //调用系统剪贴板
    m_clipBoard->setPixmap(screenshot);  //保存到剪贴板
    provider->pixmap = screenshot;  //设置图片提供者资源
    m_currentPic = &screenshot;     //保存当前图片，为支持‘保存’功能
    screenshot.save("temp.png");

}

void ScreenCapture::shotActiveWin()
{
    m_screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = m_screen->grabWindow(winId);
    m_clipBoard = QGuiApplication::clipboard();    //调用系统剪贴板
    m_clipBoard->setPixmap(pixmap);  //保存到剪贴板
    provider->pixmap = pixmap;  //设置图片提供者资源
    pixmap.save("temp.png");

}

//获取系统活动窗口ID并保存
void ScreenCapture::setActiveWinId()
{
    Display *display = XOpenDisplay(nullptr);
    Window focusWindow;
    int reverTo;
    XGetInputFocus(display,&focusWindow,&reverTo);
    winId = (WId)focusWindow;

    XCloseDisplay(display);
}
