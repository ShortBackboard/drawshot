#include "mygeometry.h"


//MyGeometry::MyGeometry(const MyGeometry::AttributeSet &attributes, int vertexCount, int indexCount, int indexType)
//{
//}


const QSGGeometry::AttributeSet &MyGeometry::defaultAttributes_My2D()
{
    static Attribute data[]={
        //描述寄存在第一个位置的属性（点由x,y组成）
        //属性寄存器的位置、属性元组的大小和属性类型
        Attribute::createWithAttributeType(0,2,FloatType,PositionAttribute),
        //描述寄存在第一个位置的属性（画点的颜色）
        Attribute::createWithAttributeType(1,3,UnsignedByteType,ColorAttribute)
    };
    //创建属性组，属性条数，属性大小，属性来源的Attribute
    static AttributeSet attrs={2,2*sizeof(float)+3*sizeof(char),data};
    return attrs;
}

//static_cast强制转换符号
//该函数返回指向此几何对象的原始顶点数据的指针。
//geometry调用则可以获得指向数据My2D的指针访问其结构体内部数据

MyGeometry::My2D *MyGeometry::vertexDataAsMy2D()
{
    return static_cast<My2D*>(vertexData());
}


const MyGeometry::My2D *MyGeometry::vertexDataAsMy2D() const
{
    return static_cast<const My2D*>(vertexData());
}
