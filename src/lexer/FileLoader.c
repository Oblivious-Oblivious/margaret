#include "FileLoader.h"

#include <stdio.h>  /* FILE, fopen, fclose, printf */
#include <stdlib.h> /* malloc, free */

/**
 * @brief Check if the path file exists in the filesystem
 * @return true if it does not exist
 */
static int file_loader_file_does_not_exist(FileLoader *self) {
    /* Try to open for reading */
    FILE *f;
    if((f = fopen(self->filepath, "r"))) {
        fclose(f);
        return 0;
    }
    printf("File: `%s` does not exist\n", self->filepath);
    return 1;
}

FileLoader *file_loader_new(void) {
    FileLoader *self = (struct FileLoader*)malloc(sizeof(FileLoader));

    self->filepath = NULL;
    self->fd = NULL;

    return self;
}

int file_loader_open(FileLoader *self, char *filepath) {
    self->filepath = filepath;

    if(file_loader_file_does_not_exist(self))
        return 0;

    if(!(self->fd = fopen(self->filepath, "r"))) {
        printf("Error on reading file: `%s`\n", self->filepath);
        return 0;
    }
    return 1;
}

int file_loader_close(FileLoader *self) {
    if(self == NULL)
        return 0;
    if((fclose(self->fd))) {
        printf("Error on closing file: `%s`\n", self->filepath);
        free(self);
        return 0;
    }
    free(self);
    return 1;
}

marg_string *file_loader_load(FileLoader *self, char *filepath) {
    file_loader_open(self, filepath);
    marg_string *result = marg_string_new("");

    char ch;
    while((ch = fgetc(self->fd)) != EOF)
        marg_string_add_char(result, ch);

    file_loader_free(self);
    return result;
}

void file_loader_free(FileLoader *self) {
    file_loader_close(self);
}
