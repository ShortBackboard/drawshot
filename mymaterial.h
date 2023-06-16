#ifndef MYMATERIAL_H
#define MYMATERIAL_H
#include <QSGMaterial>
#include <QColor>
#include <QSGTexture>

//使用时设置Flag！

class MyMaterial:public QSGMaterial
{
public:

    MyMaterial();
    //函数返回一个指针，指针指向静态，全局可用的QSGMaterialType实例
    //QSGMaterialType：与QSGMaterial结合使用作为唯一类型令牌，不清楚类型令牌是什么

    QSGMaterialType *type() const override;

    QSGMaterialShader *createShader(QSGRendererInterface::RenderMode renderMode) const override;

  //将此材料与其他材料进行比较，如果它们相等则返回0;-1表示这种材料应该在其他材料之前排序，1表示其他材料应该在之前排序。
  //场景图可以重新排序几何节点以最小化状态变化。在排序过程中调用比较函数，以便对材料进行排序
  //以最小化每次调用QSGMaterialShader::updateState()时的状态变化。this指针和other指针保证具有相同的类型()。
    int compare(const QSGMaterial *other) const override;

    //材料属性的property
    const QColor& getColor() const {return Color;}
    void setColor(const QColor &color);

private:
    //材料
    QColor Color;
//    QSGTexture texture;
};

#endif // MYMATERIAL_H
