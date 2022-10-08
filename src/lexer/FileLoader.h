#ifndef __FILE_LOADER_H_
#define __FILE_LOADER_H_

#include <stdio.h>  /* FILE */

#include "../base/marg_string.h"

/**
 * @struct FileLoader
 * @brief File handler for making file read operations more intuitive
 * @param fd -> The current file descriptor
 * @param filepath -> The name of the file to read from
 */
typedef struct FileLoader {
    FILE *fd;
    char *filepath;
} FileLoader;

/**
 * @func: FileLoader
 * @brief Creates a new instance of a FileLoader struct
 * @return FileLoader* -> The newly allocated FileLoader
 */
FileLoader *file_loader_new(void);

/**
 * @brief Open a file in read mode
 * @param filepath -> The path to open
 * @return a boolean signaling if the opening was successful
 */
int file_loader_open(FileLoader *self, char *filepath);

/**
 * @brief Attempts to close the buffers to avoid memory overflows
 */
int file_loader_close(FileLoader *self);

/**
 * @brief Loads each character into a vector
 * @param self -> The FileLoader to read from
 * @param filepath -> The name of the file to read from
 * @return marg_string* 
 */
marg_string *file_loader_load(FileLoader *self, char *filepath);

#endif
