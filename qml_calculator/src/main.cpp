#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "calclibwrapper.h"
#include "resultsaver.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QScopedPointer<CalclibWrapper> calclibWrapper(new CalclibWrapper());
    QScopedPointer<ResultSaver> resultSaver(new ResultSaver());
    QQmlApplicationEngine engine;
    qmlRegisterSingletonInstance("org.orgname.CalclibWrapper", 1, 0, "CalclibWrapper", calclibWrapper.get());
    qmlRegisterSingletonInstance("org.orgname.ResultSaver", 1, 0, "ResultSaver", resultSaver.get());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject * obj, const QUrl & objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
