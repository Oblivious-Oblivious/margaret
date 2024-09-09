#include "Scanner.h"

#include "../../libs/EmeraldsReadline/export/EmeraldsReadline.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"

VM *scanner_scan(VM *vm, char *prompt) {
  char *line = readline(prompt);

  if(line == NULL) {
    exit(0);
  } else if(*line == '\0') {
    vm->source = string_new("");
  } else {
    HIST_ENTRY *prev = history_length > 0 ? history_get(history_length) : NULL;
    if(!prev || !string_equals(string_new(line), string_new(prev->line))) {
      add_history(line);
    }
    vm->source = string_new(line);
  }

  return vm;
}
