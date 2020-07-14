#include "resultsaver.h"

#include <cmath>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

const QString ResultSaver::PATH = QStringLiteral("./output.json");

ResultSaver::ResultSaver(QObject *parent) : QObject(parent)
{

}

void ResultSaver::save(double result)
{
    QFile file(PATH);
    QJsonDocument doc;

    if (file.exists()) {
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) return;
        doc = QJsonDocument::fromJson(file.readAll());
    } else {
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    }

    if (!doc.isObject()) {
        doc.setObject(QJsonObject());
    }

    QJsonObject rootObject = doc.object();
    rootObject.insert(
        QDateTime::currentDateTime().toString(Qt::ISODateWithMs),
        std::isinf(result) ? (
            result < 0 ? QJsonValue("-Infinity") : QJsonValue("Infinity")
        ) : QJsonValue(result)
    );
    doc.setObject(rootObject);
    if(!file.resize(0)) return;
    if(!file.seek(0)) return;
    file.write(doc.toJson());
}

