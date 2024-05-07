#include "file_loader.h"

#include <stdio.h> /* FILE, fopen, fclose, FILENAME_MAX, printf */
#ifdef ON_WINDOWS
  #include <direct.h> /* _getcwd */
  #define present_working_directory _getcwd
#else
  #include <unistd.h> /* getcwd */
  #define present_working_directory getcwd
#endif

#include "../base/memory.h"

/**
 * @brief Check if the path file exists in the filesystem
 * @param self -> Current file loader
 * @return true if it does not exist
 */
static int file_loader_file_does_not_exist(file_loader *self) {
  /* Try to open for reading */
  FILE *f;
  if((f = fopen(self->filepath, "r"))) {
    fclose(f);
    return 0;
  }
  return 1;
}

file_loader *file_loader_new(void) {
  file_loader *self =
    (struct file_loader *)collected_malloc(sizeof(file_loader));

  self->filepath = NULL;
  self->fd       = NULL;

  return self;
}

int file_loader_open(file_loader *self, const char *filepath) {
  self->filepath = filepath;

  if(file_loader_file_does_not_exist(self)) {
    return 0;
  }

  if(!(self->fd = fopen(self->filepath, "r"))) {
    return 0;
  }
  return 1;
}

int file_loader_close(file_loader *self) {
  if(self == NULL) {
    return 0;
  }
  if((fclose(self->fd))) {
    return 0;
  }
  return 1;
}

string *file_loader_load(file_loader *self, const char *filepath) {
  file_loader_open(self, filepath);
  string *result = string_new("");

  char ch;
  while((ch = fgetc(self->fd)) != EOF) {
    string_add_char(result, ch);
  }

  return result;
}

char *file_loader_present_working_directory(void) {
  char *pwd = (char *)collected_malloc(sizeof(char) * FILENAME_MAX);
  present_working_directory(pwd, FILENAME_MAX);
  return pwd;
}
