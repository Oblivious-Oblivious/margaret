#include "Scanner.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h"

#include <stdio.h> /* fgets, fputs, fflush */

#if defined(MARG_USE_READLINE)
  #include <readline/history.h>  /* add_history, get_history */
  #include <readline/readline.h> /* readline */
#endif

VM *scanner_scan(VM *vm, char *prompt) {
  char line_buf[512];
  char *line = line_buf;
#if defined(MARG_USE_READLINE)
  line = readline(prompt);
#else
  fputs(prompt, stdout);
  fflush(stdout);
  fgets(line, 512, stdin);
#endif

  if(line == NULL) {
    exit(0);
  } else if(*line == '\0') {
    vm->source = string_new("");
  } else {
#if defined(MARG_USE_READLINE)
    HIST_ENTRY *prev = history_length > 0 ? history_get(history_length) : NULL;
    if(!prev || !string_equals(string_new(line), string_new(prev->line))) {
      add_history(line);
    }
#endif
    vm->source = string_new(line);
  }

  return vm;
}
