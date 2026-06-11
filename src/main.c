#include <stdio.h>
#include <getopt.h>
#include "globals/globals.h"
#include "process_dir/process_dir.h"

#define PATH_SIZE 32

void assignPath(char*[], char*[], int, int);
int processOpts(int, char*[]);

int main(int argc, char* argv[]) {
    char* path[PATH_SIZE] = {NULL};
    int ret = 0;

    if (processOpts(argc, argv) != 0) return 1;

    assignPath(argv, path, argc, optind);

    for (int i = 0; i < PATH_SIZE; i++) {
        if (path[i] == NULL) break;

        printf("== Content of %s ==\n", path[i]);
        ret = processDir(path[i]);
        printf("\n");
    }

    return ret;
}

void assignPath(char* argv[], char* path[], int argc, int start_index) {
    if (start_index >= argc) {
        path[0] = ".";
        return;
    }
    int path_idx = 0;
    for (int i = start_index; (i < argc) && (path_idx < PATH_SIZE); i++) {
        path[path_idx++] = argv[i];
    }
}

int processOpts(int argc, char* argv[]) {
    int opt;
    optind = 1;

    while ((opt = getopt(argc, argv, "al")) != -1) {
        switch (opt) {
            case 'a':
                flags |= F_SHOW_HIDDEN; break;
            case 'l':
                flags |= F_VERBOSE; break;
            default:
                fprintf(stderr, "Usage: %s [-al] [path...]\n", argv[0]);
                return 1;
        }
    }
    return 0;
}
