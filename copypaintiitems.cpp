#include "copypaintiitems.h"
#include "elementgroup.h"
#include <QDebug>
#include <QIODevice>
#include <QFile>
#include <QBuffer>
#include <QDateTime>

CopyPaintiItems::CopyPaintiItems()
{
}

void CopyPaintiItems::save()
{
    //测试函数
    m_pixmap.load("temp.png");

    int tempw=m_pixmap.width();
    int temph=m_pixmap.height();

    m_pixmap=m_pixmap.scaled(widthScale,heightScale,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    copyPainter=new QPainter(&m_pixmap);
    //设置为混合绘制
    copyPainter->setRenderHint(QPainter::Antialiasing,true);

    saveLineElement(copyPainter);
    saveGraffitiElement(copyPainter);
    saveRectElement(copyPainter);
    saveCircleRectElement(copyPainter);
    saveArrowLineElement(copyPainter);
    saveTextElement(copyPainter);
    saveMasiocGraffitiElement(copyPainter);
    copyPainter->end();

    m_pixmap=m_pixmap.scaled(tempw,temph,Qt::IgnoreAspectRatio,Qt::FastTransformation);

    m_pixmap.save("/root/Drawshot_"+getCurrentDateInfo()+".PNG");
}

void CopyPaintiItems::saveLineElement(QPainter *painter)
{
    int size=m_lineElements.size();
    LineElement *element;
    for(int i=0;i<size;i++){

        element=m_lineElements[i];
        painter->setPen(element->m_pen);
        painter->drawLine(element->m_startPoint/element->m_scale,element->m_endPoint/element->m_scale);
    }
     qDebug()<<"copyline success";
}

void CopyPaintiItems::saveGraffitiElement(QPainter *painter)
{
     int size=m_graffitiElements.size();
     GraffitiElement *element;
     for(int i = 0;i <size;++i)
     {
        element = m_graffitiElements.at(i);
        painter->setPen(element->m_pen);
        int p_size=element->m_startPoint.size();
        for(int j=0;j<p_size;++j)
        {
            painter->drawLine(element->m_startPoint[j]/element->m_scale,element->m_endPoint[j]/element->m_scale);
        }
     }
     qDebug()<<"copygraffic success";
}

void CopyPaintiItems::saveRectElement(QPainter *painter)
{
     int size=m_rectElements.size();
     RectElement *element;
     for(int i = 0;i <size;++i)
     {
        element = m_rectElements.at(i);
        painter->setPen(element->m_pen);
        {
            painter->drawRect(element->m_startPoint.x()/element->m_scale,element->m_startPoint.y()/element->m_scale,element->m_width/element->m_scale,element->m_height/element->m_scale);
        }
     }
     qDebug()<<"copyrect success";
}

void CopyPaintiItems::saveCircleRectElement(QPainter *painter)
{
     int size=m_circleElements.size();
     RectElement *element;
     for(int i = 0;i <size;++i)
     {
        element = m_circleElements.at(i);
        painter->setPen(element->m_pen);
        {
            painter->drawEllipse(element->m_startPoint.x()/element->m_scale,element->m_startPoint.y()/element->m_scale,element->m_width/element->m_scale,element->m_height/element->m_scale);
        }
     }
     qDebug()<<"copycircle success";
}

void CopyPaintiItems::saveArrowLineElement(QPainter *painter)
{
     int size=m_arrowLineElements.size();
     ArrowLineElement *element;
     for(int i = 0;i <size;++i)
     {
        element = m_arrowLineElements.at(i);
        painter->setPen(element->m_pen);
        painter->drawLine(element->m_startPoint/element->m_scale,element->m_endPoint/element->m_scale);
        painter->drawLine(element->m_endPoint/element->m_scale, element->pointA/element->m_scale); // 绘制箭头一半
        painter->drawLine(element->m_endPoint/element->m_scale, element->pointB/element->m_scale); // 绘制箭头另一半
     }
     qDebug()<<"copyarrow success";
}

void CopyPaintiItems::saveTextElement(QPainter *painter)
{

  int size=m_textElements.size();
  TextElement *element;
  for(int i = 0;i <size;++i)
  {
        element = m_textElements.at(i);
        painter->setPen(element->m_pen);

        QFont font=painter->font();
        font.setPixelSize(element->fontSize/element->m_scale);
        painter->setFont(font);

        painter->drawText(element->m_startPoint.x()/element->m_scale,element->m_startPoint.y()/element->m_scale,element->m_width/element->m_scale,element->m_height/element->m_scale,0,element->text);
  }
        qDebug()<<"copytextfinish input";
}

void CopyPaintiItems::saveMasiocGraffitiElement(QPainter *painter)
{
    int size=m_masiocElements.size();
    GraffitiElement *element;
    for(int i = 0;i <size;++i)
    {
        element = m_masiocElements.at(i);
        painter->setPen(element->m_pen);
        int p_size=element->m_startPoint.size();
        for(int j=0;j<p_size;++j)
        {
            painter->drawLine(element->m_startPoint[j]/element->m_scale,element->m_endPoint[j]/element->m_scale);
        }
    }
    qDebug()<<"copymasico success";
}

QString CopyPaintiItems::getCurrentDateInfo()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString dtInfo = dt.toString("yyyyMMdd_hhmmss");
    return dtInfo;
}
////绘画完成的pixmap
//QPixmap* CopyPaintiItems::getFinalPixmap()
//{
//    return &m_pixmap;
//}

