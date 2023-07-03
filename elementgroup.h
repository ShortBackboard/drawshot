#ifndef ELEMENTGROUP_H
#define ELEMENTGROUP_H
#include <QQuickPaintedItem>
#include <QPoint>
#include <QPainter>
#include <QVector>
#include <QPen>
#include <string>
//直线：线和笔

class LineElement{
public:
    LineElement(){}

    LineElement(const QPen &pen)
        : m_pen(pen){}

    LineElement(const LineElement &e)
    {
        //存储
        m_line=e.m_line;
        m_startPoint=e.m_startPoint;
        m_endPoint=e.m_endPoint;
        m_scale=e.m_scale;
    }

    LineElement & operator=(const LineElement &e)
    {
        if(this != &e)
        {
            m_line = e.m_line;
            m_pen = e.m_pen;
            m_startPoint=e.m_startPoint;
            m_endPoint=e.m_endPoint;
            m_scale=e.m_scale;
        }
        return *this;
    }

    ~LineElement() {}
    QLine m_line;
    QPoint m_startPoint;
    QPoint m_endPoint;
    //每次操作的scale
    float m_scale;
    //0表示过去，1表示现在
    int m_status=1;
    int m_linestatus=1;
    QPen m_pen;
};
//箭头
class ArrowLineElement{
public:
    ArrowLineElement(){}

    ArrowLineElement(const QPen &pen)
        : m_pen(pen){}

    ArrowLineElement(const ArrowLineElement &e)
    {
        //存储
        m_startPoint=e.m_startPoint;
        m_endPoint=e.m_endPoint;
        m_scale=e.m_scale;
    }

    ArrowLineElement & operator=(const ArrowLineElement &e)
    {
        if(this != &e)
        {
            m_pen = e.m_pen;
            m_startPoint=e.m_startPoint;
            m_endPoint=e.m_endPoint;
            m_scale=e.m_scale;
        }
        return *this;
    }

    ~ArrowLineElement() {}
    QPoint m_startPoint;
    QPoint m_endPoint;
    //箭头坐标
    QPoint pointA;
    QPoint pointB;

    double arrowLength = 15;      // 箭头长度
    double arrowDegrees = 0.5;    // 箭头角度

    //每次操作的scale
    float m_scale;
    //0表示过去，1表示现在
    int m_status=1;
    int m_linestatus=1;


    QPen m_pen;
};

class GraffitiElement{
public:
    GraffitiElement(){}

    GraffitiElement(const QPen &pen)
        : m_pen(pen){}

    GraffitiElement(const GraffitiElement &e)
    {
        //存储
        m_startPoint=e.m_startPoint;
        m_endPoint=e.m_endPoint;
        m_scale=e.m_scale;
    }

    GraffitiElement & operator=(const GraffitiElement &e)
    {
        if(this != &e)
        {
            m_startPoint=e.m_startPoint;
            m_endPoint=e.m_endPoint;
            m_scale=e.m_scale;
            m_pen = e.m_pen;
        }
        return *this;
    }

    ~GraffitiElement() {}
    QVector<QPoint> m_startPoint;
    QVector<QPoint> m_endPoint;

    //每次操作的scale
    float m_scale;
    //0表示过去，1表示现在
    int m_status=1;
    QPen m_pen;
};

class RectElement{
public:
    RectElement(){}

    RectElement(const QPen &pen)
        : m_pen(pen){}

    RectElement(const RectElement &e)
    {
        //存储
        m_startPoint=e.m_startPoint;
        m_width=e.m_width;
        m_height=e.m_height;

        m_scale=e.m_scale;
    }

    RectElement & operator=(const RectElement &e)
    {
        if(this != &e)
        {
            m_startPoint=e.m_startPoint;
            m_width=e.m_width;
            m_height=e.m_height;

            m_scale=e.m_scale;
            m_pen = e.m_pen;
        }
        return *this;
    }

    ~RectElement() {}
    //画矩形需要的数据
    QPoint m_startPoint;
    int m_width;
    int m_height;

    //每次操作的scale
    float m_scale;
    //0表示过去，1表示现在
    int m_status=1;

    QPen m_pen;
    QVector<QRect> earseRects;
};

class TextElement{
    public:
    TextElement(const QPen &pen)
        : m_pen(pen){}

    TextElement(const TextElement &e)
    {
        //存储
        m_startPoint=e.m_startPoint;
        m_width=e.m_width;
        m_height=e.m_height;
        m_scale=e.m_scale;

        textStartPoint= e.textStartPoint;
        m_textway= e.m_textway;
        text= e.text;
        m_pen = e.m_pen;
        fontSize=e.fontSize;
    }

    TextElement & operator=(const TextElement &e)
    {
        if(this != &e)
        {
            m_startPoint=e.m_startPoint;
            m_width=e.m_width;
            m_height=e.m_height;
            m_scale=e.m_scale;

            textStartPoint= e.textStartPoint;
            m_textway= e.m_textway;
            text= e.text;
            m_pen = e.m_pen;
            fontSize=e.fontSize;
        }
        return *this;
    }

    ~TextElement() {}
    //文字对齐方式
    int flags;
    //文字大小:默认大小也可更改
    int fontSize=20;

    QPoint m_startPoint;
    int m_width;
    int m_height;

    //每次操作的scale
    float m_scale;
    //0表示过去，1表示现在
    int m_status=1;
    int m_teststatus=0;

    QString text;
    QPoint textStartPoint;
    QPen m_pen;

    int m_textway;
};

#endif // ELEMENTGROUP_H
