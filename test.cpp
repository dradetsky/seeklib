#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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

void sizeinfo() {
    printf("%d\n", sizeof(SigStruct));
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof(short));
}

int main(int argc, char** argv) {
    printf("ok\n");
    if (argc < 2) {
        printf("no path");
        exit(0);
    }
    many(argv[1]);
    exit(0);
}
