#include "Application.hpp"
#include "gui/ImageRender.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("unofficial-discord-client");
    QGuiApplication::setOrganizationName("Coding Bunker");
    QGuiApplication::setApplicationVersion("0.0.1");
   // QGuiApplication;

    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<ImageRender>("ui", 1, 0, "ImageRender");

    Application a(engine.rootContext());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    a.loadSettings();

    return app.exec();
}
