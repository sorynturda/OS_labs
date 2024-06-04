#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

off_t dirSize(const char *path)
{
    off_t size = 0;
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL) {
        perror("Could not open directory");
        return 0;
    }
    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0) {
                printf("%s\n", fullPath);
                size += statbuf.st_size;
                if(S_ISDIR(statbuf.st_mode)) {
                   size += dirSize(fullPath);
                }
            }
        }
    }
    closedir(dir);
    return size;
}

int main(int argc, char **argv)
{
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <dir_name>\n", argv[0]);
        return 1;
    }
    printf("%ld bytes\n", dirSize(argv[1]));
    return 0;
}
