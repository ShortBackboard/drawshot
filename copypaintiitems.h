#ifndef COPYPAINTIITEMS_H
#define COPYPAINTIITEMS_H

#include <QQuickPaintedItem>
#include<QQuickItem>
#include <QImage>
#include <QPaintEvent>
#include<QPixmap>
#include "elementgroup.h"

class CopyPaintiItems
{
public:
    CopyPaintiItems();
    //保存
    void save();
    void saveLineElement(QPainter* painter);
    void saveGraffitiElement(QPainter* painter);
    void saveRectElement(QPainter* painter);
    void saveCircleRectElement(QPainter* painter);
    void saveArrowLineElement(QPainter* painter);
    void saveTextElement(QPainter* painter);
    void saveMasiocGraffitiElement(QPainter* painter);
    QPainter *copyPainter;

    //涂鸦
    QVector<GraffitiElement*> m_graffitiElements;
    //直线
    QVector<LineElement*>  m_lineElements;
    //矩形
    QVector<RectElement*> m_rectElements;
    //椭圆
    QVector<RectElement*> m_circleElements;
    //箭头
    QVector<ArrowLineElement *> m_arrowLineElements;
    //文字
    QVector<TextElement *> m_textElements;
    //马赛克
    QVector <GraffitiElement*> m_masiocElements;

    QPixmap m_pixmap;
};

#endif // COPYPAINTIITEMS_H
