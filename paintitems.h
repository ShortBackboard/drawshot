#ifndef PAINTITEMS_H
#define PAINTITEMS_H
//author：2021051615215huangruixian
//继承QQuickPaintedItem，在qml中实现绘画功能，PaintedItem是一个组建绘画工具可理解为带有很多功能的画布

#include <QQuickPaintedItem>
#include <QQmlEngine>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QVector>
#include <QPen>
#include <QString>
#include "elementgroup.h"
//直线

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    //获取qml端的笔的size
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth)
    //获取qml端的笔的color
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    //获取当前状态
    Q_PROPERTY(int currentGraphical  WRITE setCurrentGraphical)
    Q_PROPERTY(bool m_bEnabled READ getm_bEnabled WRITE setm_bEnabled )

    //保存截图的pixmap数据进行绘制
    Q_PROPERTY(QPixmap m_pximap  WRITE setm_pximap)

//    Q_PROPERTY(int m_width  WRITE setm_width)
//    Q_PROPERTY(int m_height  WRITE setm_height)
//    Q_PROPERTY(int display_width  WRITE setdisplay_width)
//    Q_PROPERTY(int display_height  WRITE setdisplay_height)
    Q_PROPERTY(float changedScale READ getChangeScale WRITE setChangedScale)

    //文字相关的共享数据
    Q_PROPERTY(int s_textStatus WRITE sets_textStatus NOTIFY s_textStatusChanged)
    Q_PROPERTY(int s_textFinishStatus WRITE sets_textFinishStatus NOTIFY s_textFinishStatusChanged)
    Q_PROPERTY(QString s_string WRITE sets_string NOTIFY s_stringChanged)

    Q_PROPERTY(QPoint s_textPoint READ gets_textPoint WRITE sets_textPoint NOTIFY s_textPointChanged)
    Q_PROPERTY(int s_width READ gets_width WRITE sets_width NOTIFY s_widthChanged)
    Q_PROPERTY(int s_height READ gets_height WRITE sets_height NOTIFY s_heightChanged)

    Q_PROPERTY(bool textEditStatus READ getTextEditStatus  NOTIFY textEditStatusChanged)
    //笔数据
    QML_ELEMENT
signals:
    //设置qml端的textEdit的位置大小
    void s_textPointChanged();
    void s_widthChanged();
    void s_heightChanged();

    void s_stringChanged();
    void s_textStatusChanged();
    void s_textFinishStatusChanged();
    void textEditStatusChanged();
    //完成文本获取信号
    Q_INVOKABLE void finishGetTextString(int status,int textstatus,QString text,int fontsize);
public slots:
    //对获得的文字进行处理
    Q_INVOKABLE void onFinishGetTextString(int status,int textstatus,QString text,int fontsize);
public:
    PaintedItem(QQuickItem *parent = 0);
    ~PaintedItem();
    //设置是否进行绘画的事件处理标志
    bool getm_bEnabled() const{ return m_bEnabled;}
    void setm_bEnabled(bool b){m_bEnabled=b;}
    //设置画笔的宽度
    int penWidth() const { return m_pen.width(); }
    void setPenWidth(int width) { m_pen.setWidth(width); }

    //设置画笔的颜色
    QColor penColor() const { return m_pen.color(); }
    void setPenColor(QColor color) { m_pen.setColor(color); }

    //设置当前的绘画模式，直线，举行，涂鸦，圆圈，矩形等
    void setCurrentGraphical(int cg){currentGraphical=cg;}

    //设置绘画的图片内容即pixmap-改变
    void setm_pximap(QPixmap pximap){m_pximap=pximap;}

    //缩放
    void setChangedScale(float qreal){changedScale=qreal;}
    float getChangeScale(){return changedScale;}

    //文字相关操作
    Q_INVOKABLE void sets_textStatus(int i){s_textStatus==i; emit s_textStatusChanged();}
    Q_INVOKABLE void sets_textFinishStatus(int i){s_textFinishStatus==i; emit s_textFinishStatusChanged();}
    Q_INVOKABLE void sets_string(QString str){s_string==str; emit s_stringChanged();}

    void sets_textPoint(QPoint p){s_textPoint=p;}
    void sets_width(int w){s_width=w;}
    void sets_height(int h){s_height=h;}

    QPoint gets_textPoint(){return s_textPoint;}
    int gets_width(){return s_width;}
    int gets_height(){return s_height;}
    bool getTextEditStatus(){return textEditStatus;}

    //清除所有
    Q_INVOKABLE void clear();
    //撤销上一步
    Q_INVOKABLE void undo();
    //保存-copyItem对截图的pixmap进行绘画
    Q_INVOKABLE void save();
    Q_INVOKABLE void setScale(int qreal){changedScale=qreal;}

    void paint(QPainter *painter);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //双击用于确定文字起始点
//    void mouseDoubleClickEvent(QMouseEvent *event);
    void purgePaintElements();
    //画直线
    void drawLine(QPainter *painter);
    //画涂鸦
    void drawGraffiti(QPainter *painter);
    //画矩形
    void drawRectangle(QPainter *painter);
    //画圆
    void drawCircle(QPainter *painte);
    //画文字
    void drawText(QPainter *painter);
    //画箭头
    void drawArrowLine(QPainter*painter);
    void calculateArrowPosition();
    //马赛克
    void drawMasicLine(QPainter*painter);
    //画图片
//    void drawPixmap(QPainter *painter);
protected:


    //要画的图
    QPixmap m_pximap;
//    //实现缩放,缩放程度

    //缩放程度-初始化为1
    float changedScale=1;

    //绘画形状所需要的点
    QPoint m_startPoint;
    QPoint m_endPoint;

    //绘画原理：mouseevent是处理当前段的数据，然后存储到所有的数据中，在当前进行图像的重绘操作
    //画直线
    QVector<LineElement*> m_lineElements;  // 所有的线段数据
    LineElement * m_lineElement;  // 当前的线段数据

    //涂鸦
    QVector <GraffitiElement*> m_graffitiElements;
    GraffitiElement*m_graffitiElement;

    //矩形
    QVector<RectElement*> m_rectElements;
    RectElement *m_rectElement;

    //椭圆
    QVector<RectElement*> m_circleElements;
    RectElement *m_circleElement;

    //箭头
    QVector<ArrowLineElement*> m_arrowLineElements;
    ArrowLineElement * m_arrowLineElement;

    //文字
    QVector<TextElement*> m_textElements;
    TextElement *m_textElement;
    int s_textStatus;
    int s_textFinishStatus;
    QString s_string;
    QPoint s_textPoint;
    int s_width;
    int s_height;
    bool textEditStatus;
    int s_textSize;

    //马赛克
    QVector <GraffitiElement*> m_masiocElements;
    GraffitiElement*m_masiocElement;

    //事件判断
    bool m_bEnabled;
    bool m_bPressed;
    bool m_bMoved;
    bool m_bClicked;

    QPen m_pen; // the Current Pen
    QColor m_color;//当前颜色

    //当前绘画状态
    int currentGraphical;
    //记录绘画顺序
    QVector <int> m_sequence;
};

#endif // PAINTEDITEM_H

