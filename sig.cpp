#include <stdio.h>

#include <CImg.h>

#include "sig.h"

using namespace cimg_library;

SigStruct *pathSig(char *path) {
    CImg<unsigned char> img(path);
    SigStruct *sig = imgSig(&img);
    return sig;
}

SigStruct *imgSig(CImg<unsigned char> *img) {
    img->resize(NUM_PIXELS, NUM_PIXELS);
    static Unit cdata1[NUM_PIXELS_SQUARED];
    static Unit cdata2[NUM_PIXELS_SQUARED];
    static Unit cdata3[NUM_PIXELS_SQUARED];
    unsigned char rchan[NUM_PIXELS_SQUARED];
    unsigned char gchan[NUM_PIXELS_SQUARED];
    unsigned char bchan[NUM_PIXELS_SQUARED];
    int i = 0;
    cimg_for(img->get_shared_channel(0), p, unsigned char) {
        rchan[i] = *p;
        i++;
    }
    i = 0;
    cimg_for(img->get_shared_channel(1), p, unsigned char) {
        gchan[i] = *p;
        i++;
    }
    i = 0;
    cimg_for(img->get_shared_channel(2), p, unsigned char) {
        bchan[i] = *p;
        i++;
    }
    transformChar(rchan, gchan, bchan, cdata1, cdata2, cdata3);
    SigStruct *nsig = new SigStruct();
    calcHaar(cdata1, cdata2, cdata3,
             nsig->sig1, nsig->sig2, nsig->sig3, nsig->avgl);

    return nsig;
}

void printSig(SigStruct *sig) {
    printSigSect(sig->sig1);
    printSigSect(sig->sig2);
    printSigSect(sig->sig3);
}

void printSigObj(SigStruct *sig) {
    printSig(sig);
    // avg lum
    for (int i=0; i<3; i++) {
        printf("%e ", sig->avgl[i]);
    }
    printf("\n");
}

void printSigSect(Idx *sigSect) {
    for (int i=0; i<NUM_COEFS; i++) {
        // typedef int Idx
        printf("%d ", sigSect[i]);
    }
    printf("\n");
}
