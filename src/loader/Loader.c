#include "Loader.h"

#include "../../libs/EmeraldsFileHandler/export/EmeraldsFileHandler.h"
#include "../errors.h"

/**
 * @brief Displays a loader-level error message
 * @param vm -> The vm containing the filename
 * @param message -> The message to display
 */
void loader_error(VM *vm, const char *message) {
  printf(
    "\033[1;31merror:\033[0m %s: \033[1;31m`%s`\033[0m\n", message, vm->filename
  );
  vm->error = message;
}

VM *loader_load(VM *vm) {
  char *res = file_handler_read(vm->filename);

  if(res == NULL) {
    loader_error(vm, ERROR_LOADER_FILE_NOT_FOUND);
  } else {
    vm->source = res;
  }

  return vm;
}
