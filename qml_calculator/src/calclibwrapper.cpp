#include "calclibwrapper.h"

extern "C" {
#include "calclib.h"
}

CalclibWrapper::CalclibWrapper(QObject *parent) : QObject(parent)
{

}

double CalclibWrapper::sum(double a, double b)
{
    return calcSum(a, b);
}

double CalclibWrapper::sub(double a, double b)
{
    return calcSub(a, b);
}

double CalclibWrapper::div(double a, double b)
{
    return calcDiv(a, b);
}

double CalclibWrapper::mul(double a, double b)
{
    return calcMul(a, b);
}
