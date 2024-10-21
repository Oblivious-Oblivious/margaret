#include "scanner.h"

#include "../libs/EmeraldsReadline/export/EmeraldsReadline.h"
#include "../libs/EmeraldsString/export/EmeraldsString.h"

#include <stdlib.h> /* exit */

char *scan(const char *prompt) {
  char *source = NULL;
  char *line   = readline(prompt);

  if(line == NULL) {
    exit(0);
  } else if(*line == '\0') {
    source = string_new("");
  } else {
    HIST_ENTRY *prev = history_length > 0 ? history_get(history_length) : NULL;
    if(!prev || !string_equals(string_new(line), string_new(prev->line))) {
      add_history(line);
    }
    source = string_new(line);
  }

  return source;
}
