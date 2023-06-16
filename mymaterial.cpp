#include "mymaterial.h"
#include "mymaterialshader.h"

#include <QSGMaterialShader>


MyMaterial::MyMaterial()
{
    setFlag(Blending, true);
}

QSGMaterialType *MyMaterial::type() const
{
    //返回一个令牌类型，目前不知道用来做什么
    static QSGMaterialType type;
    return &type;
}

QSGMaterialShader *MyMaterial::createShader(QSGRendererInterface::RenderMode renderMode) const
{

     return new MyMaterialShader;
}
// //setShaderSourceFile(QOpenGLShader::Vertex, QStringLiteral(":/qt-project.org/scenegraph/shaders/vertexcolor.vert"));
//setShaderSourceFile(QOpenGLShader::Fragment, QStringLiteral(":/qt-project.org/scenegraph/shaders/vertexcolor.frag"));

int MyMaterial::compare(const QSGMaterial *other) const
{
    const MyMaterial *mata=static_cast<const MyMaterial *>(other);
    //将此材料与其他材料进行比较，如果它们相等则返回0;-1表示这种材料应该在其他材料之前排序，1表示其他材料应该在之前排序。
    return Color.rgba()-mata->getColor().rgba();
}

void MyMaterial::setColor(const QColor &color)
{
    Color=color;
}


