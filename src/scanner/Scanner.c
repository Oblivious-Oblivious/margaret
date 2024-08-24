#include "Scanner.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h"

VM *scanner_scan(VM *vm, char *prompt) {
  char bounds_buf[65535];
  char *line = crossline_readline(prompt, bounds_buf, sizeof(bounds_buf));

  if(line == NULL) {
    exit(0);
  } else if(!strncmp(line, "", 0)) {
    vm->source = string_new("");
  } else {
    vm->source = string_new(line);
  }

  return vm;
}
