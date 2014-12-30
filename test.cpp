#include <stdio.h>
#include <stdlib.h>

#include "haar.h"
#include "sig.h"

int main(int argc, char** argv) {
    printf("ok\n");
    printf("%d\n", sizeof(SigStruct));
    printf("%d\n", sizeof(char));
    printf("ok\n");
    if (argc < 2) {
        printf("no path");
        exit(0);
    }
    SigStruct *sig = pathSig(argv[1]);
    printSig(sig);
    printf("ok\n");
    exit(0);
}
