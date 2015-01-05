#ifndef CMP_H
#define CMP_H

#include "sig.h"

#ifdef __cplusplus
extern "C" {
#endif

double calcDiff(SigStruct *siga, SigStruct *sigb);

#ifdef __cplusplus
}
#endif

// not api
double calcAvglDiff(SigStruct *siga, SigStruct *sigb);

#endif // CMP_H
