#include "Scanner.h"

#include <string.h>

EmeraldsString *scanner_scan(char *prompt) {
  char bounds_buf[4096];
  char *line = crossline_readline(prompt, bounds_buf, sizeof(bounds_buf));
  if(!strcmp(line, "")) {
    return string_new("()");
  } else {
    return string_new(line);
  }
}
