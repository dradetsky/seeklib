#ifndef SIG_H
#define SIG_H

#include <string.h>

// needed by test.cpp; can fwd declare to avoid?
#include <magick/api.h>

#include "haar.h"

// Weights for the Haar coefficients.
// Straight from the referenced paper:

const float weights[2][6][3]={
    // For scanned picture (sketch=0):
    //    Y      I      Q       idx total occurs
    {{ 5.00f, 19.21f, 34.37f},  // 0   58.58      1 (`DC' component)
     { 0.83f,  1.26f,  0.36f},  // 1    2.45      3
     { 1.01f,  0.44f,  0.45f},  // 2    1.90      5
     { 0.52f,  0.53f,  0.14f},  // 3    1.19      7
     { 0.47f,  0.28f,  0.18f},  // 4    0.93      9
     { 0.30f,  0.14f,  0.27f}}, // 5    0.71      16384-25=16359

    // For handdrawn/painted sketch (sketch=1):
    //    Y      I      Q
    {{ 4.04f, 15.14f, 22.62f},
     { 0.78f,  0.92f,  0.40f},
     { 0.46f,  0.53f,  0.63f},
     { 0.42f,  0.26f,  0.25f},
     { 0.41f,  0.14f,  0.15f},
     { 0.32f,  0.07f,  0.38f}}
};

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

class SigStruct;

/* persisted signature structure */
class DiskSigStruct {
public:
    // dmr: we don't need ids
    // imageId id;			/* picture id */
    //
    // dmr: Idx is an int, probably for speed, but it looks like it
    // only runs from -16384 through 16383. This could come in handy
    // for packing it.
    Idx sig1[NUM_COEFS];		/* Y positions with largest magnitude */
    Idx sig2[NUM_COEFS];		/* I positions with largest magnitude */
    Idx sig3[NUM_COEFS];		/* Q positions with largest magnitude */
    double avgl[3];		/* YIQ for position [0,0] */
    /* image properties extracted when opened for the first time */
    int width;			/* in pixels */
    int height;			/* in pixels */

    DiskSigStruct() {}
    ~DiskSigStruct()
    {

    }
};

/* in memory signature structure */
class SigStruct: public DiskSigStruct {
public:
    double score;			/* used when doing queries */
    // int_hashset keywords;

    SigStruct(DiskSigStruct* ds) {
        // dmr: no ids
        // id = ds->id;

        memcpy(sig1,ds->sig1,sizeof(sig1));
        memcpy(sig2,ds->sig2,sizeof(sig2));
        memcpy(sig3,ds->sig3,sizeof(sig3));
        memcpy(avgl,ds->avgl,sizeof(avgl));

        width=ds->width;
        height=ds->height;

    }

    SigStruct() {}
    ~SigStruct() {}
    bool operator< (const SigStruct & right) const {
        return score < (right.score);
    }
};

SigStruct *pathSig(char *path);
SigStruct *imgSig(Image *img);
void printSig(SigStruct *sig);

// not api
void printSigSect(Idx *sigSect);

#endif // SIG_H
