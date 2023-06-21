/*
 * author: liChengYang2019051604044
 * date: 2023-6-21
 * Area ScreenRecord
 */
#ifndef AREARECORD_H
#define AREARECORD_H
#include "Gif.h"
#include <QWidget>

class QPushButton;
class QLineEdit;
class QLabel;
class QTimber;

class AreaRecord:public QWidget{
    Q_OBJECT
public:
    AreaRecord(QWidget *parent=0);
    ~AreaRecord();

signals:
    void finish();//截屏完毕

public slots:
    void resizeForm();
    void saveImage();
    void record();
    void closeAll();

protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);

private:
    QWidget *widgetMain;
    QWidget *widgetBottom;
    QLineEdit *txtFps;//帧率
    QLineEdit *txtWidth;//宽度
    QLineEdit *txtHeight;//长度
    Gif gif;//图像
    Gif::GifWriter *gifWriter;
    QPushButton *btnStart;
    QPushButton *closeButton;
    QLabel *labStatus;
    int borderWidth;
    int fps;
    int count;
    QColor bgColor;
    QRect rectGif;
    QString fileName;
    QTimer *timer;

};


#endif // AREARECORD_H
