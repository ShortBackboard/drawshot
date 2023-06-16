#ifndef MYGEOMETRY_H
#define MYGEOMETRY_H

#include <QSGGeometry>
//自定node义图像类型——通过获得点的信息来调用drawline或者是point或者是三角形，矩形由四条线组成
class MyGeometry:public QSGGeometry
{
public:

    using QSGGeometry::QSGGeometry;

    struct My2D{
        //坐标
        float m_x;
        float m_y;
        //点的颜色,和透明度
        uchar m_r;
        uchar m_g;
        uchar m_b;
        uchar m_a;
        void set(float _x,float _y, uchar _r, uchar _g, uchar _b, uchar _a)
        {
            m_x=_x;
            m_y=_y;
            m_r=_r;
            m_g=_g;
            m_b=_g;
            m_a=_a;
        }
        //返回自己点的纯色绘制属性

//        static const AttributeSet &defaultAttributes_ColoredMy2D();  //纹理
//        static const AttributeSet &defaultAttributes_TexturedMy2D(); //彩色
        //一套渲染My2D图像的属性，Attribute包括有Position,Color,Texture
    };

    static const AttributeSet &defaultAttributes_My2D();
    //一个geometry中的struct结构

    //获得点的具体信息
    My2D *vertexDataAsMy2D(); //可变
    const My2D *vertexDataAsMy2D() const; //不可变
};

#endif // MYGEOMETRY_H
