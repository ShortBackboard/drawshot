#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "screencapture.h"
#include "selectimageprovider.h"
#include "paintitems.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ScreenCapture sc;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextObject(&sc);
    engine.addImageProvider("mypixmap",sc.provider);

    const QUrl url(u"qrc:/drawshot/Main.qml"_qs);

    qmlRegisterType<PaintedItem>("qml.Component", 1, 0, "PaintedItem");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
