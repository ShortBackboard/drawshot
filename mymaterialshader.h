#ifndef MYMATERIALSHADER_H
#define MYMATERIALSHADER_H
#include <QSGMaterialShader>
#include <QOpenGLContext>
#include <QOpenGLFunctions>


class MyMaterialShader : public QSGMaterialShader
{
public:

    MyMaterialShader()
    {
        setShaderFileName(VertexStage, QLatin1String(":/root/drawshot/drawshot/src_quick_scenegraph_shaders_ng_vertexcolor.vert.qsb"));
        setShaderFileName(FragmentStage, QLatin1String(":/materialshader.vert.qsb"));
    }

    bool updateUniformData(RenderState &state, QSGMaterial *, QSGMaterial *)
    {
        bool changed = false;
        QByteArray *buf = state.uniformData();
        if (state.isMatrixDirty()) {
            const QMatrix4x4 m = state.combinedMatrix();
            memcpy(buf->data(), m.constData(), 64);
            changed = true;
        }
        return changed;
    }

};

#endif // MYMATERIALSHADER_H
