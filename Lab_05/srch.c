
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int search_dir(char *file_name, char *dir_name) {
    
    struct stat inode;
    char path[1000];
    sprintf(path, "%s/%s", dir_name, file_name);
    if(stat(path, &inode) != -1) {
        return 1;
    }

    /*
    // Slower method of iterating trough a directory
    DIR *dir = NULL;
    dir = opendir(dir_name);
    struct dirent *dir_entry;

    while((dir_entry = readdir(dir)) != NULL) {
        printf("Directory entry: %s\n", dir_entry->d_name);
        if(strcmp(dir_name, dir_entry->d_name) == 0)
        return 1;
    }
    */
    
    return 0;
}




int main(int argc, char **argv) {

    if(argc != 3) {
        printf("USAGE: %s <name> <path>\n", argv[0]);
        return 1;
    }

    struct stat inode;
    if(stat(argv[2], &inode) == -1) {
        perror("Cannot get inode of the dir\n");
        return 2;
    }

    if(search_dir(argv[1], argv[2]) == 0) {
        printf("Did not find file %s in dir %s\n", argv[1], argv[2]);
    }
    else {
        printf("File was found: %s%s\n", argv[2], argv[1]);
    }

    return 0;
}