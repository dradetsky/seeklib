#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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

    const char *dir_name = argv[1];
    struct dirent *dir_entry;
    DIR *dir = opendir(dir_name);
    if (!dir){
	printf("unable to open directory\n");
	exit(1);
    }
    int count = 0;
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
        if (++count > 1000)
            break;
    }

    printf("ok\n");
    exit(0);
}
