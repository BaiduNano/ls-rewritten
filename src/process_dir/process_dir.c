#include <math.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "globals/globals.h"
#include "process_dir.h"

int processDir(const char* path) {
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    };
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (!(flags & F_SHOW_HIDDEN) && (entry->d_name[0] == '.'))
            continue;

        if (flags & F_VERBOSE) printVerbose(path, entry->d_name);
        else printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}

void printVerbose(const char* dir, const char* name) {
    char fullPath[4092];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, name);

    struct stat st;
    if (lstat(fullPath, &st) < 0){
        perror(name);
        return;
    }
    char modes[11];
    modeString(st.st_mode, modes);

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    const char *u = pw ? pw->pw_name : "?";
    const char *g = gr ? gr->gr_name : "?";

    char timeBuffer[64];

    struct tm *tm = localtime(&st.st_mtime);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M", tm);

    unsigned long sizeBytes = (unsigned long)st.st_size;
    unsigned long KB = 1024UL;
    unsigned long MB = 1024UL * 1024UL;
    unsigned long GB = 1024UL * 1024UL * 1024UL;

    int isGB = (sizeBytes >= GB);
    int isMB = (!isGB && sizeBytes >= MB);

    float_t size;
    const char* unit;

    if (isGB) {
        size = (float_t)sizeBytes / GB;
        unit = "GB";
    } else if (isMB) {
        size = (float_t)sizeBytes / MB;
        unit = "MB";
    } else {
        size = (float_t)sizeBytes / KB;
        unit = "KB";
    }

    printf(
        "%s %lu %s %s %.1f%s %s %s\n",
        modes,
        (unsigned long)st.st_nlink,
        u,
        g,
        size,
        unit,
        timeBuffer,
        name
    );

}

void modeString(mode_t mode, char *str) {
    if (S_ISDIR(mode)) str[0] = 'd';
    else if (S_ISLNK(mode)) str[0] = 'l';
    else if (S_ISCHR(mode)) str[1] = 'c';
    else if (S_ISBLK(mode)) str[1] = 'b';
    else if (S_ISFIFO(mode)) str[1] = 'p';
    else if (S_ISSOCK(mode)) str[1] = 's';
    else str[0] = '-';

    // User
    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    // Group
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    // Other
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';
    str[10] = '\0';
}
