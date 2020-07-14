#ifndef CALCLIB_H
#define CALCLIB_H

typedef long double CalcArg;
typedef CalcArg (*SimpleOperation)(CalcArg, CalcArg);

CalcArg calcSum(CalcArg, CalcArg);

CalcArg calcSub(CalcArg, CalcArg);

CalcArg calcMul(CalcArg, CalcArg);

CalcArg calcDiv(CalcArg, CalcArg);

#endif
