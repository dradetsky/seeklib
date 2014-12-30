#ifndef CMP_H
#define CMP_H

#include <cmath>

#include "haar.h"
#include "sig.h"

double calcDiff(SigStruct *siga, SigStruct *sigb);

// not api
double calcAvglDiff(SigStruct *siga, SigStruct *sigb);

#endif // CMP_H
