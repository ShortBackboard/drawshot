#ifndef MYSHAPE_H
#define MYSHAPE_H

#include <QQuickItem>

class MyShape : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MyShape(QQuickItem *parent = nullptr);

    //渲染时会调用组件的此接口
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData) override;

signals:

};

#endif // MYSHAPE_H
