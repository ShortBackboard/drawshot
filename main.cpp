#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "screencapture.h"
#include "selectimageprovider.h"
#include "share.h"//exports
#include "arearecord.h"
#include "paintitems.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ScreenCapture sc;
    Share *share = new Share;
    AreaRecord *arearecord = new AreaRecord;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextObject(&sc);
    engine.rootContext()->setContextProperty("share",share);
    engine.rootContext()->setContextProperty("arearecort",arearecord);
    engine.addImageProvider("mypixmap",sc.provider);

    const QUrl url(u"qrc:/drawshot/Main.qml"_qs);

    qmlRegisterType<PaintedItem>("qml.Component", 1, 0, "PaintedItem");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
