#include "Loader.h"

#include "../../libs/EmeraldsReadHandler/export/EmeraldsReadHandler.h" /* IWYU pragma: keep */

VM *loader_load(VM *vm) {
  EmeraldsReadHandler *fd = read_handler_new();
  char *res               = read_handler_load(fd, vm->filename);
  read_handler_close(fd);
  vm->source = res;
  return vm;
}
