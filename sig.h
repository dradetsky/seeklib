#ifndef SIG_H
#define SIG_H

#include "haar.h"

// Weights for the Haar coefficients.
// Straight from the referenced paper:

const float picture_weights[6][3] = {
    // For scanned picture (sketch=0):
    //    Y      I      Q       idx total occurs
    { 5.00f, 19.21f, 34.37f},  // 0   58.58      1 (`DC' component)
    { 0.83f,  1.26f,  0.36f},  // 1    2.45      3
    { 1.01f,  0.44f,  0.45f},  // 2    1.90      5
    { 0.52f,  0.53f,  0.14f},  // 3    1.19      7
    { 0.47f,  0.28f,  0.18f},  // 4    0.93      9
    { 0.30f,  0.14f,  0.27f}   // 5    0.71      16384-25=16359
};

// Global typedefs
typedef long int imageId;

namespace cimg_library {
    template<typename T> struct CImg;
};

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SigStruct {
    Idx sig1[NUM_COEFS];		/* Y positions with largest magnitude */
    Idx sig2[NUM_COEFS];		/* I positions with largest magnitude */
    Idx sig3[NUM_COEFS];		/* Q positions with largest magnitude */
    double avgl[3];		/* YIQ for position [0,0] */
    /* image properties extracted when opened for the first time */
} SigStruct;



SigStruct *pathSig(char *path);
SigStruct *imgSig(cimg_library::CImg<unsigned char> *img);
// TODO: blob -> cimg
// SigStruct *blobSig(const char *blob, const long length);


#ifdef __cplusplus
}
#endif

void printSig(SigStruct *sig);

// not api
void printSigSect(Idx *sigSect);

#endif // SIG_H
