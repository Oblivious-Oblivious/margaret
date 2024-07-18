#include "Scanner.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */

#include <string.h>

char *scanner_scan(char *prompt) {
  char bounds_buf[65535];
  char *line = crossline_readline(prompt, bounds_buf, sizeof(bounds_buf));
  if(!strcmp(line, "")) {
    return string_new("");
  } else {
    return string_new(line);
  }
}
