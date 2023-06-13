/* 屏幕捕获的接口，用于提供所有屏幕捕获功能，向上返回屏幕捕获信息
 *
 * author: wanlukuan
 * date: 2023-6-13
 *
 */

#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QObject>

class QScreen;
class QPixmap;
class QClipboard;

class ScreenCapture: public QObject
{
    Q_OBJECT

public:
    ScreenCapture(QWidget *parent = 0);
    //初始设定图片截取后，暂不返回任何指
    Q_INVOKABLE void shotFullScreen();  //全屏截取
private:
    QScreen *m_screen;  //当前屏幕
    QClipboard *m_clipBoard;    //剪贴板
};

#endif // SCREENCAPTURE_H
