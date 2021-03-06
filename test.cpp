#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "cmp.h"
#include "haar.h"
#include "sig.h"

void many(char *dir_name) {
    struct dirent *dir_entry;
    DIR *dir = opendir(dir_name);
    if (!dir){
	printf("unable to open directory\n");
	exit(1);
    }
    char path[1024];
    path[0] = '\0';
    while ((dir_entry = readdir(dir)) != 0){
	if (strcmp(dir_entry->d_name,".") && strcmp(dir_entry->d_name,"..")){
	    strcat(path, dir_name);
	    strcat(path, "/");
	    strcat(path, dir_entry->d_name);
            SigStruct *sig = pathSig(path);
            printSig(sig);
        }
        path[0]='\0';
    }
    exit(0);
}

void cmp_many(char *dir_name) {
    SigStruct *sig_last = NULL;
    char path[1024];
    path[0] = '\0';
    struct dirent **dirents;
    struct dirent *dir_entry;
    int i, n;
    n = scandir(dir_name, &dirents, NULL, alphasort);
    for (i=0; i<n; i++) {
        dir_entry = dirents[i];
	if (strcmp(dir_entry->d_name,".") && strcmp(dir_entry->d_name,"..")){
	    strcat(path, dir_name);
	    strcat(path, "/");
	    strcat(path, dir_entry->d_name);
            SigStruct *sig = pathSig(path);
            if (sig_last) {
                double diff = calcDiff(sig, sig_last);
                printf("%f\n", diff);
                delete sig_last;
            }
            sig_last = sig;
        }
        path[0]='\0';
    }
    exit(0);
}

void cmp2(char *path0, char *path1) {
    SigStruct *sig0 = pathSig(path0);
    SigStruct *sig1 = pathSig(path1);
    double diff = calcDiff(sig0, sig1);
    printf("%f\n", diff);
}

void sizeinfo() {
    printf("%d\n", sizeof(SigStruct));
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof(short));
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("no path");
        sizeinfo();
    } else if (argc < 3) {
        cmp_many(argv[1]);
    } else {
        cmp2(argv[1], argv[2]);
    }
    exit(0);
}
