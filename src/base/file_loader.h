#ifndef __FILE_LOADER_H_
#define __FILE_LOADER_H_

#include <stdio.h>  /* FILE */

#include "string.h"

/**
 * @struct file_loader
 * @brief File handler for making file read operations more intuitive
 * @param fd -> The current file descriptor
 * @param filepath -> The name of the file to read from
 */
typedef struct file_loader {
    FILE *fd;
    char *filepath;
} file_loader;

/**
 * @func: file_loader
 * @brief Creates a new instance of a file_loader struct
 * @return file_loader* -> The newly allocated file_loader
 */
file_loader *file_loader_new(void);

/**
 * @brief Open a file in read mode
 * @param filepath -> The path to open
 * @return a boolean signaling if the opening was successful
 */
int file_loader_open(file_loader *self, char *filepath);

/**
 * @brief Attempts to close the buffers to avoid memory overflows
 */
int file_loader_close(file_loader *self);

/**
 * @brief Loads each character into a vector
 * @param self -> The file_loader to read from
 * @param filepath -> The name of the file to read from
 * @return string* 
 */
string *file_loader_load(file_loader *self, char *filepath);

#endif
