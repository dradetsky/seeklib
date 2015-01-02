#include <stdio.h>

#include <magick/api.h>

#include "sig.h"

SigStruct *pathSig(char *path) {
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    ImageInfo *image_info;
    image_info = CloneImageInfo((ImageInfo *) NULL);
    (void) strcpy(image_info->filename, path);
    Image *image = ReadImage(image_info, &exception);
    if (exception.severity != UndefinedException) CatchException(&exception);
    DestroyImageInfo(image_info);
    DestroyExceptionInfo(&exception);
    SigStruct *sig = imgSig(image);
    DestroyImage(image);
    return sig;
}

SigStruct *blobSig(const char *blob, const long length) {
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    ImageInfo *image_info;
    image_info = CloneImageInfo((ImageInfo *) NULL);
    Image *image = BlobToImage(image_info, blob, length, &exception);
    SigStruct *sig = imgSig(image);
    DestroyImage(image);
    DestroyImageInfo(image_info);
    return sig;
}

// Not 100% sure this is correct. Need to review the paper. After the
// body of this method, there's another bit* which I thought was just
// about storing it in their db, but might affect the calculated hash.
//
// *the "#else //FAST_POW_GEERT" block
SigStruct *imgSig(Image *img) {
    // Made static for speed; only used locally
    static Unit cdata1[NUM_PIXELS_SQUARED];
    static Unit cdata2[NUM_PIXELS_SQUARED];
    static Unit cdata3[NUM_PIXELS_SQUARED];
    int i;
    int width, height;

    ExceptionInfo exception;

    Image *resize_image;
    /*
      Initialize the image info structure and read an image.
    */
    GetExceptionInfo(&exception);

    width = img->columns;
    height = img->rows;

    resize_image = SampleImage(img, NUM_PIXELS, NUM_PIXELS, &exception);

    // dmr: prolly shouldn't do this here; creator should destroy
    // DestroyImage(image);

    DestroyExceptionInfo(&exception);

    if (resize_image == (Image *) NULL) {
        fprintf(stderr, "ERROR: unable to resize image\n");
        return 0;
    }

    // store color value for basic channels
    unsigned char rchan[NUM_PIXELS_SQUARED];
    unsigned char gchan[NUM_PIXELS_SQUARED];
    unsigned char bchan[NUM_PIXELS_SQUARED];

    GetExceptionInfo(&exception);

    const PixelPacket *pixel_cache = AcquireImagePixels(
        resize_image,
        0,
        0,
        NUM_PIXELS,
        NUM_PIXELS,
        &exception
    );

    for (int idx = 0; idx < NUM_PIXELS_SQUARED; idx++) {
        rchan[idx] = pixel_cache->red;
        gchan[idx] = pixel_cache->green;
        bchan[idx] = pixel_cache->blue;
        pixel_cache++;
    }

    DestroyImage(resize_image);

    transformChar(rchan, gchan, bchan, cdata1, cdata2, cdata3);

    DestroyExceptionInfo(&exception);

    SigStruct *nsig = new SigStruct();
    // dmr: no ids
    // nsig->id = id;
    nsig->width = width;
    nsig->height = height;

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
    
    printf("%d\n", sig->width);
    printf("%d\n", sig->height);
}

void printSigSect(Idx *sigSect) {
    for (int i=0; i<NUM_COEFS; i++) {
        // typedef int Idx
        printf("%d ", sigSect[i]);
    }
    printf("\n");
}
