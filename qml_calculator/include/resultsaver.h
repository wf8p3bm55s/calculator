#ifndef RESULTSAVER_H
#define RESULTSAVER_H

#include <QObject>

class ResultSaver : public QObject
{
    Q_OBJECT
public:
    explicit ResultSaver(QObject *parent = nullptr);
    Q_INVOKABLE void save(double result);
private:
    static const QString PATH;
};

#endif // RESULTSAVER_H
