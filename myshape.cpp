#include <QtQuick/QSGNode>
#include "myshape.h"
#include "mygeometry.h"
#include "mymaterial.h"
#include <QDebug>


MyShape::MyShape(QQuickItem *parent)
: QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}

QSGNode *MyShape::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData)
{

    Q_UNUSED(updatePaintNodeData)

    QSGGeometryNode *node=nullptr;
    MyGeometry *geometry=nullptr;
    MyMaterial *material=nullptr;

    //初始化
    if(!oldNode)
    {
        node=new QSGGeometryNode;
        geometry=new MyGeometry(MyGeometry::defaultAttributes_My2D(), 2);

        geometry->setLineWidth(10);
        geometry->setDrawingMode(QSGGeometry::DrawLines);

        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        //给渲染节点添加图像信息并设置为node更新原来的信息会被销毁
        material=new MyMaterial;

   //     material->setColor(QColor(255, 0, 0,255));
        qDebug()<<"new 2";
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
        qDebug()<<"new 1";
    }
    //更新
    else
    {
        qDebug()<<"new 3";
        node = static_cast<QSGGeometryNode *>(oldNode);
        material = static_cast<MyMaterial *>(node->material());
        geometry = static_cast<MyGeometry *>(node->geometry());
    }
    MyGeometry::My2D *vertices = geometry->vertexDataAsMy2D();
    vertices[0].set(0,0,255,0,0,255); //半透明红色
    vertices[1].set(width(),height(),255,0,0,255); //蓝色
    node->markDirty(QSGNode::DirtyGeometry);
    qDebug()<<"new 4";
    return node;
}
