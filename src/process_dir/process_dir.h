#ifndef PROCESS_DIR_H
#define PROCESS_DIR_H

#include <dirent.h>
#include <sys/stat.h>

int processDir(const char*);
void printVerbose(const char*, const char*);

void modeString(mode_t, char *);

#endif // PROCESS_DIR_H
