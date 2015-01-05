#include <cmath>
#include <stdlib.h>
#include <string.h>

#include "cmp.h"
#include "haar.h"

unsigned char imgBin[NUM_PIXELS_SQUARED];
int imgBinInited = 0;

void initImgBin() {
    imgBinInited = 1;

    /* setup initial fixed weights that each coefficient represents */
    int i, j;

    /*
      0 1 2 3 4 5 6 i
      0 0 1 2 3 4 5 5
      1 1 1 2 3 4 5 5
      2 2 2 2 3 4 5 5
      3 3 3 3 3 4 5 5
      4 4 4 4 4 4 5 5
      5 5 5 5 5 5 5 5
      5 5 5 5 5 5 5 5
      j
    */

    /* Every position has value 5, */
    memset(imgBin, 5, NUM_PIXELS_SQUARED);

    /* Except for the 5 by 5 upper-left quadrant: */
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            imgBin[i * NUM_PIXELS + j] = max(i, j);
    // Note: imgBin[0] == 0
}


double calcDiff(SigStruct *siga, SigStruct *sigb) {
    /* use it to tell the content-based difference between two images
     */
    if (!imgBinInited) {
        initImgBin();
    }
    double diff = calcAvglDiff(siga, sigb);
    Idx *corea[3] = { siga->sig1, siga->sig2, siga->sig3 };
    Idx *coreb[3] = { sigb->sig1, sigb->sig2, sigb->sig3 };

    for (int b = 0; b < NUM_COEFS; b++)
        for (int c = 0; c < 3; c++)
            for (int b2 = 0; b2 < NUM_COEFS; b2++)
                if (coreb[c][b2] == corea[c][b])
                    diff -= picture_weights[imgBin[abs(corea[c][b])]][c];

    return diff;
}

double calcAvglDiff(SigStruct *siga, SigStruct *sigb) {
	return fabs(siga->avgl[0] - sigb->avgl[0])
            + fabs(siga->avgl[1] - sigb->avgl[1])
            + fabs(siga->avgl[2] - sigb->avgl[2]);
}

