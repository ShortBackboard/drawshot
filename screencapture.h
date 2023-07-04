/* 屏幕捕获的接口，用于提供所有屏幕捕获功能，向上返回屏幕捕获信息
 *
 * author: wanlukuan
 * date: 2023-6-13
 *
 */

#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QObject>
#include "selectimageprovider.h"

class QScreen;
class QPixmap;
class QClipboard;

class ScreenCapture: public QObject
{
    Q_OBJECT

public:
    ScreenCapture(QWidget *parent = 0);
    //初始设定图片截取后，暂不返回任何值
    Q_INVOKABLE void shotFullScreen();  //全屏截取
    Q_INVOKABLE void shotFullScreen(int x,int y,int w,int h);  //指定区域截取
    Q_INVOKABLE void shotActiveWin();   //活动窗口截取
//    Q_INVOKABLE void shotIrregular();   //不规则截图
    Q_INVOKABLE void setActiveWinId();  //获取并保存系统当前活动窗口ID
    QPixmap *getCurrentPixmap();
    
public:
    SelectImageProvider *provider;  //图片提供者

private:
    QScreen *m_screen;  //当前屏幕
    QClipboard *m_clipBoard;    //剪贴板
    QPixmap *m_currentPic;  //当前的截图
    WId winId;   //当前活动窗口ID
};

#endif // SCREENCAPTURE_H
