#ifndef CALCLIBWRAPPER_H
#define CALCLIBWRAPPER_H

#include <QObject>

class CalclibWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CalclibWrapper(QObject *parent = nullptr);
    Q_INVOKABLE double sum(double a, double b);
    Q_INVOKABLE double sub(double a, double b);
    Q_INVOKABLE double div(double a, double b);
    Q_INVOKABLE double mul(double a, double b);
signals:

};

#endif // CALCLIBWRAPPER_H
