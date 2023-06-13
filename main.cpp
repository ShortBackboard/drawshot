#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "screencapture.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ScreenCapture sc;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextObject(&sc);
//    engine.addImageProvider(QLatin1String("pic"), new SelectImageProvider);
    const QUrl url(u"qrc:/drawshot/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
