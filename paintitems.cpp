#include "paintitems.h"
#include "copypaintiitems.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QPaintDevice>

#include <QtMath>
void PaintedItem::onFinishGetTextString(int status,int textstatus,QString text,int fontsize)
{
    qDebug()<<"status"<<status<<textstatus<<text;
    m_textElement->m_status=status;
    m_textElement->m_teststatus=textstatus;
    m_textElement->text=text;
    m_textElement->fontSize=fontsize;
    textEditStatus=false;
    emit textEditStatusChanged();
    update();
}

PaintedItem::PaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_lineElement(0)
    , m_bEnabled(true)
    , m_bPressed(false)
    , m_bClicked(false)
    , m_bMoved(false)
    , m_pen(Qt::black)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    connect(this,&PaintedItem::finishGetTextString,this,&PaintedItem::onFinishGetTextString);
}

PaintedItem::~PaintedItem()
{
    purgePaintElements();
}

void PaintedItem::clear()
{
    purgePaintElements();
    update();
}
//清空所有的数据，clear操作的细节
void PaintedItem::purgePaintElements()
{
    //先判断容器内有无数据后在进行清除
    int lsize = m_lineElements.size();
    if(lsize > 0)
    {
        for(int i = 0; i < lsize; ++i)
        {
            delete m_lineElements.at(i);
        }
        m_lineElements.clear();
    }
    qDebug()<<"直线清除数据后"<<m_lineElements.size();
     //涂鸦
    int gsize = m_graffitiElements.size();
    if(gsize > 0)
    {
        for(int i = 0; i < gsize; ++i)
        {
            delete m_graffitiElements.at(i);
        }
        m_graffitiElements.clear();
    }
    qDebug()<<"涂鸦清除数据后"<<m_graffitiElements.size();

    //矩形
    int rsize = m_rectElements.size();
    if(rsize > 0)
    {
        for(int i = 0; i < rsize; ++i)
        {
            delete m_rectElements.at(i);
        }
        m_rectElements.clear();
    }
    qDebug()<<"矩形清除数据后"<<m_rectElements.size();
     //文本
    int tsize = m_textElements.size();
    if(tsize > 0)
    {
        for(int i = 0; i < tsize; ++i)
        {
            delete m_textElements.at(i);
        }
        m_textElements.clear();
    }
    qDebug()<<"文本清除数据后"<<m_textElements.size();
    //椭圆
    int csize = m_circleElements.size();
    if(csize > 0)
    {
        for(int i = 0; i < csize; ++i)
        {
            delete m_circleElements.at(i);
        }
        m_circleElements.clear();
    }
    qDebug()<<"椭圆清除数据后"<<m_circleElements.size();
    //箭头
     int asize = m_arrowLineElements.size();
    if(asize > 0)
    {
        for(int i = 0; i < asize; ++i)
        {
            delete m_arrowLineElements.at(i);
        }
        m_arrowLineElements.clear();
    }
    qDebug()<<"箭头清除数据后"<<m_arrowLineElements.size();
     //马赛克
        int msize = m_masiocElements.size();
    if(msize > 0)
    {
        for(int i = 0; i < msize; ++i)
        {
            delete m_masiocElements.at(i);
        }
        m_masiocElements.clear();
    }
    qDebug()<<"马赛克清除数据后"<<m_masiocElements.size();
}

//撤销当前操作，
void PaintedItem::undo()
{
    if(m_sequence.size()!=0)
    {
        int i=m_sequence[m_sequence.size()-1];
        if(i==1){
            if(m_lineElements.size()>0)
                delete m_lineElements.takeLast();
        }
        else if(i==2)
        {
            if(m_graffitiElements.size()>0)
                delete m_graffitiElements.takeLast();
        }
        else if(i==3)
        {
            if(m_rectElements.size()>0)
                delete m_rectElements.takeLast();
        }
        else if(i==4)
        {
            if(m_textElements.size()>0)
                delete m_textElements.takeLast();
        }
        else if(i==5)
        {
            if(m_circleElements.size()>0)
                delete m_circleElements.takeLast();
        }
        else if(i==6)
        {
            if(m_arrowLineElements.size()>0)
                delete m_arrowLineElements.takeLast();
        }
        else if(i==7)
        {
            if(m_masiocElements.size()>0)
                delete m_masiocElements.takeLast();
        }
        m_sequence.removeLast();
    }
    update();
}

//事件处理后自动调用的绘图
void PaintedItem::paint(QPainter *painter)
{
    qDebug()<<"painting";
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true );

    m_pximap.load(":/icons/test.png");
    //画数据
    painter->begin(&m_pximap);
    drawLine(painter);
    drawGraffiti(painter);
    drawRectangle(painter);
    drawText(painter);
    drawCircle(painter);
    drawArrowLine(painter);
    drawMasicLine(painter);
}

//划线
void PaintedItem::drawLine(QPainter *painter)
{
    //直线
    int size=m_lineElements.size();
    LineElement *element;  
    for(int i = 0;i <size;++i)
    {
        element = m_lineElements.at(i);
        painter->setPen(element->m_pen);
        qDebug()<<"缩放大小"<<changedScale;
                element = m_lineElements.at(i);
        //status判断：0过去，1现在
        if(element->m_status==0)
        {
            painter->drawLine(element->m_startPoint/element->m_scale*changedScale,element->m_endPoint/element->m_scale*changedScale);
        }
        if(element->m_status==1)
        {
            painter->drawLine(element->m_startPoint,element->m_endPoint);
        }
    }
        qDebug()<<"linfinish";
}
//涂鸦
void PaintedItem::drawGraffiti(QPainter *painter)
{

    int size=m_graffitiElements.size();
    GraffitiElement *element;
    //    直线
    for(int i = 0;i <size;++i)
    {
        element = m_graffitiElements.at(i);
        painter->setPen(element->m_pen);
        int p_size=element->m_startPoint.size();
        //0过去，1现在
        if(element->m_status==0)
        {
             for(int j=0;j<p_size;++j)
             {
                 painter->drawLine(element->m_startPoint[j]/element->m_scale*changedScale,element->m_endPoint[j]/element->m_scale*changedScale);
             }
             qDebug()<<"nooo当前：";
        }
        if(element->m_status==1)
        {
             for(int j=0;j<p_size;++j)
             {
                 painter->drawLine(element->m_startPoint[j],element->m_endPoint[j]);
             }
             qDebug()<<"当前：";
        }
    }
        qDebug()<<"GraffitiElementfinish";
}
//矩形
void PaintedItem::drawRectangle(QPainter *painter)
{
    //矩形
    int size=m_rectElements.size();
    RectElement *element;
    for(int i = 0;i <size;++i)
    {
        element = m_rectElements.at(i);
        painter->setPen(element->m_pen);
        if(element->m_status==0)
        {
             painter->drawRect(element->m_startPoint.x()/element->m_scale*changedScale,element->m_startPoint.y()/element->m_scale*changedScale,element->m_width/element->m_scale*changedScale,element->m_height/element->m_scale*changedScale);
        }
        if(element->m_status==1)
        {
             painter->drawRect(element->m_startPoint.x(),element->m_startPoint.y(),element->m_width,element->m_height);
        }
    }
    qDebug()<<"rectfinish";

}
//椭圆
void PaintedItem::drawCircle(QPainter *painter)
{
    //椭圆
    int size=m_circleElements.size();
    RectElement *element;
    for(int i = 0;i <size;++i)
    {
        element = m_circleElements.at(i);
        painter->setPen(element->m_pen);
        if(element->m_status==0)
        {
             painter->drawEllipse(element->m_startPoint.x()/element->m_scale*changedScale,element->m_startPoint.y()/element->m_scale*changedScale,element->m_width/element->m_scale*changedScale,element->m_height/element->m_scale*changedScale);
        }
        if(element->m_status==1)
        {
             painter->drawEllipse(element->m_startPoint.x(),element->m_startPoint.y(),element->m_width,element->m_height);
        }
    }
    qDebug()<<"rectfinish";
}

//画文字
void PaintedItem::drawText(QPainter *painter)
{

    int size=m_textElements.size();
    TextElement *element;


    for(int i = 0;i <size;++i)
    {
        qDebug()<<"drawimage circul";
        element = m_textElements.at(i);
        painter->setPen(element->m_pen);
        if(element->m_status==0&&element->m_teststatus==1)
        {
             QFont font=painter->font();
             font.setPixelSize(element->fontSize/element->m_scale*changedScale);
             painter->setFont(font);
             painter->drawText(element->m_startPoint.x()/element->m_scale*changedScale,element->m_startPoint.y()/element->m_scale*changedScale,element->m_width/element->m_scale*changedScale,element->m_height/element->m_scale*changedScale,0,element->text);
             qDebug()<<"finish input";
        }
        //现在
        if(element->m_status==1)
        {
             painter->drawRect(element->m_startPoint.x(),element->m_startPoint.y(),element->m_width,element->m_height);
              qDebug()<<"nofinish input";
        }

    }
      qDebug()<<"textdraw";
}
//画箭头
void PaintedItem::drawArrowLine(QPainter *painter)
{

    int size=m_arrowLineElements.size();
    ArrowLineElement *element;
      //    直线
      for(int i = 0;i <size;++i)
      {
        qDebug()<<"缩放大小"<<changedScale;
         element = m_arrowLineElements.at(i);
        painter->setPen(element->m_pen);
        //status判断：0过去，1现在
        if(element->m_status==0)
        {
              painter->drawLine(element->m_startPoint/element->m_scale*changedScale,element->m_endPoint/element->m_scale*changedScale);
              painter->drawLine(element->m_endPoint/element->m_scale*changedScale, element->pointA/element->m_scale*changedScale); // 绘制箭头一半
              painter->drawLine(element->m_endPoint/element->m_scale*changedScale, element->pointB/element->m_scale*changedScale); // 绘制箭头另一半
        }
        if(element->m_status==1)
        {
              painter->drawLine(element->m_startPoint,element->m_endPoint);
              painter->drawLine(element->m_endPoint, element->pointA); // 绘制箭头一半
              painter->drawLine(element->m_endPoint, element->pointB); // 绘制箭头另一半
        }
    }
      qDebug()<<"drawArrowLinefinish";
}
//对箭头数据进行处理
void PaintedItem::calculateArrowPosition()
{
      double angle = atan2(m_arrowLineElement->m_endPoint.y() - m_arrowLineElement->m_startPoint.y(), m_arrowLineElement->m_endPoint.x() - m_arrowLineElement->m_startPoint.x())+ 3.1415926;

      m_arrowLineElement->pointA.setX(m_arrowLineElement->m_endPoint.x()+m_arrowLineElement->arrowLength*cos(angle-m_arrowLineElement->arrowDegrees));

      m_arrowLineElement->pointA.setY(m_arrowLineElement->m_endPoint.y()+m_arrowLineElement->arrowLength*sin(angle-m_arrowLineElement->arrowDegrees));

      m_arrowLineElement->pointB.setX(m_arrowLineElement->m_endPoint.x()+m_arrowLineElement->arrowLength*cos(angle+m_arrowLineElement->arrowDegrees));

      m_arrowLineElement->pointB.setY(m_arrowLineElement->m_endPoint.y()+m_arrowLineElement->arrowLength*sin(angle+m_arrowLineElement->arrowDegrees));
}
//马赛克
void PaintedItem::drawMasicLine(QPainter *painter)
{
    int size=m_masiocElements.size();
    GraffitiElement *element;
    for(int i = 0;i <size;++i)
    {
        element = m_masiocElements.at(i);

        element->m_pen.setWidth(20/element->m_scale*changedScale);
        painter->setPen(element->m_pen);
        int p_size=element->m_startPoint.size();
        //0过去，1现在
        if(element->m_status==0)
        {
              for(int j=0;j<p_size;++j)
              {
                 painter->drawLine(element->m_startPoint[j]/element->m_scale*changedScale,element->m_endPoint[j]/element->m_scale*changedScale);
              }
              qDebug()<<"nooo当前：";
        }
        if(element->m_status==1)
        {
              for(int j=0;j<p_size;++j)
              {
                 painter->drawLine(element->m_startPoint[j],element->m_endPoint[j]);
              }
              qDebug()<<"当前：";
        }
    }

    painter->setBrush( QBrush(Qt::SolidPattern));
    qDebug()<<"drawMasicLinefinish";
}

//保存
void PaintedItem::save()
{
    qDebug()<<"save image";
    CopyPaintiItems *copy=new CopyPaintiItems();
    copy->m_lineElements=m_lineElements;
    copy->m_graffitiElements=m_graffitiElements;
    copy->m_arrowLineElements=m_arrowLineElements;
    copy->m_circleElements=m_circleElements;
    copy->m_rectElements=m_circleElements;
    copy->m_textElements=m_textElements;
    copy->m_masiocElements=m_masiocElements;
    copy->m_pixmap=m_pximap;
    copy->save();
    //在copy的save中输出图片
    this->clear();
}

void PaintedItem::mousePressEvent(QMouseEvent *event)
{
    m_bMoved = false;   
    m_bPressed = true;

    if(!m_bEnabled || !(event->button() & acceptedMouseButtons()))
    {
        qDebug()<<"move press:"+currentGraphical;
        QQuickPaintedItem::mousePressEvent(event);
    }
    else
    {
        //初始化按下时的坐标
        m_startPoint = event->pos();
        m_endPoint=event->pos();
        //通过前端传回的数据，初始化不同的图形
        switch (currentGraphical) {
        case 1:
        {
            //直线
            m_lineElement = new LineElement(m_pen);
            m_lineElements.append(m_lineElement);

            m_startPoint=event->pos();
            m_endPoint=event->pos();

            m_lineElement->m_startPoint=m_startPoint;
            m_lineElement->m_endPoint=m_endPoint;
            m_lineElement->m_status=1;

            qDebug()<<"直线press："<<event->pos();
            m_sequence.append(1);
            break;
        }
        case 2:
        {
            //涂鸦
            m_graffitiElement = new GraffitiElement(m_pen);
            m_graffitiElements.append(m_graffitiElement);

            m_startPoint=event->pos();
            m_endPoint=event->pos();

            m_graffitiElement->m_startPoint.append(m_startPoint);
            m_graffitiElement->m_endPoint.append(m_endPoint);
            m_graffitiElement->m_status=1;
            m_sequence.append(2);
            qDebug()<<"涂鸦press："<<event->pos();
                                            break;
        }
        case 3:
        {
            //矩形
            m_rectElement=new RectElement(m_pen);
            m_rectElements.append(m_rectElement);

            m_endPoint=event->pos();

            m_rectElement->m_startPoint=m_startPoint;
            m_rectElement->m_width=0;
            m_rectElement->m_height=0;
            m_sequence.append(3);
            qDebug()<<"矩形press： "<<event->pos();
                                             break;

        }
        case 4:
        {
            //显示文字框
            m_textElement=new TextElement(m_pen);
            m_textElements.append(m_textElement);

            m_startPoint=event->pos();
            m_textElement->m_startPoint=m_startPoint;
            qDebug()<<"文字矩形press： "<<event->pos();
                                                       m_sequence.append(4);
            break;
        }
        case 5:
        {
            m_circleElement=new RectElement(m_pen);
            m_circleElements.append(m_circleElement);
            m_endPoint=event->pos();

            m_circleElement->m_startPoint=m_startPoint;
            m_circleElement->m_width=0;
            m_circleElement->m_height=0;
            m_sequence.append(5);
            qDebug()<<"椭圆press： "<<event->pos();
                                             break;
        }
        case 6:
        {
            //初始化一个直线并加入直线组中
            m_arrowLineElement = new ArrowLineElement(m_pen);
            m_arrowLineElements.append(m_arrowLineElement);

            m_arrowLineElement->m_startPoint=event->pos();;
            m_arrowLineElement->m_endPoint=event->pos();;
            m_arrowLineElement->m_status=1;
            //对箭头数据进行处理
            calculateArrowPosition();
            m_sequence.append(6);
            qDebug()<<"箭头press："<<event->pos();
                                            break;

        }
        case 7:
        {
            //马赛克
            //实现马赛克
            QBrush masicBrush;
            masicBrush.setStyle(Qt::TexturePattern);
            masicBrush.setTextureImage(QImage(":/icons/moasicdraw.png"));
            QPen temp;
            temp=m_pen;
            m_pen.setBrush(masicBrush);
            m_pen.setWidth(15);

            m_masiocElement = new GraffitiElement(m_pen);
            m_masiocElements.append(m_masiocElement);

            m_startPoint=event->pos();
            m_endPoint=event->pos();

            m_masiocElement->m_startPoint.append(m_startPoint);
            m_masiocElement->m_endPoint.append(m_endPoint);
            m_masiocElement->m_status=1;

            m_pen=temp;
            m_sequence.append(7);
            qDebug()<<"马赛克press："<<event->pos();
                break;

        }
        default:
            break;

        }
        event->setAccepted(true);
        update();
    }
}


void PaintedItem::mouseMoveEvent(QMouseEvent *event)
{
    m_bMoved=true;
    if(!m_bEnabled ||! m_bPressed  & acceptedMouseButtons())
    {
        qDebug()<<"move move:"+currentGraphical;
        QQuickPaintedItem::mousePressEvent(event);
    }
    else
    {
        switch (currentGraphical) {
        case 1:
        {
            //移动时更改直线的点
            m_lineElement->m_endPoint=event->pos();;
            qDebug()<<"直线mouve："<<event->pos();
                                            break;
        }
        case 2:
        {
            //笔移动更新涂鸦内容
            m_startPoint=m_endPoint;
            m_endPoint=event->pos();

            m_graffitiElement->m_startPoint.append(m_startPoint);
            m_graffitiElement->m_endPoint.append(m_endPoint);
            qDebug()<<"涂鸦move："<<event->pos();
                                           break;
        }
        case 3:
        {
            //矩形
            m_endPoint=event->pos();
            m_rectElement->m_width=m_endPoint.x()-m_startPoint.x();
            m_rectElement->m_height=m_endPoint.y()-m_startPoint.y();

            qDebug()<<"矩形move： "<<event->pos();
                                            break;

        }
        case 4:
        {
            m_endPoint=event->pos();

            m_textElement->m_width=m_endPoint.x()-m_startPoint.x();
            m_textElement->m_height=m_endPoint.y()-m_startPoint.y();

            qDebug()<<"文字矩形move： "<<event->pos();
                break;
        }
        case 5:
        {
            m_endPoint=event->pos();
            m_circleElement->m_width=m_endPoint.x()-m_startPoint.x();
            m_circleElement->m_height=m_endPoint.y()-m_startPoint.y();

            qDebug()<<"椭圆move： "<<event->pos();
                                            break;
        }
        case 6:
        {
            //初始化一个直线并加入直线组中
            m_arrowLineElement->m_endPoint=event->pos();

            calculateArrowPosition();

            qDebug()<<"箭头press："<<event->pos();
                                            break;

        }
        case 7:
        {
            //马赛克
            m_startPoint=m_endPoint;
            m_endPoint=event->pos();

            m_masiocElement->m_startPoint.append(m_startPoint);
            m_masiocElement->m_endPoint.append(m_endPoint);
            qDebug()<<"马赛克mouve："<<event->pos();
                break;
        }
        default:
            break;
        }
        update();

    }

}

void PaintedItem::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPressed = false;
    m_bMoved = false;
    if(!m_bEnabled || !(event->button() & acceptedMouseButtons()))
    {

        qDebug()<<"mouse realse:"+currentGraphical;
        QQuickPaintedItem::mousePressEvent(event);
    }
    else
    {
        switch (currentGraphical) {
        case 1:
        {
            //直线
            m_endPoint=event->pos();

            m_lineElement->m_endPoint=m_endPoint;
            m_lineElement->m_status=0;
            m_lineElement->m_scale=changedScale;
            qDebug()<<"直线realse："<<event->pos();
                                             break;
        }
        case 2:
        {
            //涂鸦
            m_startPoint=m_endPoint;
            m_endPoint=event->pos();

            m_graffitiElement->m_startPoint.append(m_startPoint);
            m_graffitiElement->m_endPoint.append(m_endPoint);

            m_graffitiElement->m_status=0;
            m_graffitiElement->m_scale=changedScale;

            qDebug()<<"涂鸦realse："<<event->pos();
                                             break;
        }
        case 3:
        {
            //矩形
            m_endPoint=event->pos();
            m_rectElement->m_width=m_endPoint.x()-m_startPoint.x();
            m_rectElement->m_height=m_endPoint.y()-m_startPoint.y();

            m_rectElement->m_status=0;
            m_rectElement->m_scale=changedScale;

            qDebug()<<"矩形realse： "<<event->pos();
                                              break;

        }
        case 4:
        {
            //文字
            m_endPoint=event->pos();

            m_textElement->m_width=m_endPoint.x()-m_startPoint.x();
            m_textElement->m_height=m_endPoint.y()-m_startPoint.y();
            m_textElement->m_scale=changedScale;

            s_textPoint=m_textElement->m_startPoint;
            s_width=m_textElement->m_width;
            s_height=m_textElement->m_height;

            s_textFinishStatus=0;
            s_textStatus=1;
            textEditStatus=true;
            emit s_heightChanged();
            emit s_widthChanged();
            emit s_textPointChanged();
            emit textEditStatusChanged();
            qDebug()<<"文字矩形relase"<<event->pos();
                break;
        }
        case 5:
        {
            //椭圆
            m_endPoint=event->pos();
            m_circleElement->m_width=m_endPoint.x()-m_startPoint.x();
            m_circleElement->m_height=m_endPoint.y()-m_startPoint.y();

            m_circleElement->m_status=0;
            m_circleElement->m_scale=changedScale;

            qDebug()<<"椭圆realse： "<<event->pos();
                                              break;
        }
        case 6:
        {
            //初始化一个直线并加入直线组中
            m_arrowLineElement->m_endPoint=event->pos();
            calculateArrowPosition();
            m_arrowLineElement->m_status=0;
            m_arrowLineElement->m_scale=changedScale;
            qDebug()<<"箭头press："<<event->pos();
                                            break;
        }
        case 7:
        {

            //马赛克
            m_startPoint=m_endPoint;
            m_endPoint=event->pos();

            m_masiocElement->m_startPoint.append(m_startPoint);
            m_masiocElement->m_endPoint.append(m_endPoint);

            m_masiocElement->m_status=0;
            m_masiocElement->m_scale=changedScale;

            qDebug()<<"马赛克realse："<<event->pos();
                break;
        }
        default:
            break;
        }
        update();
    }
}

