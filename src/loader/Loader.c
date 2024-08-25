#include "Loader.h"

#include "../../libs/EmeraldsReadHandler/export/EmeraldsReadHandler.h"

VM *loader_load(VM *vm) {
  EmeraldsReadHandler *fd = read_handler_new();
  /* TODO - Ensure loading returns errors that I can print as marg errors */
  char *res               = read_handler_load(fd, vm->filename);
  read_handler_close(fd);
  vm->source = res;
  return vm;
}
