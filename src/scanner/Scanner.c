#include "Scanner.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */

char *scanner_scan(char *prompt) {
  char bounds_buf[65535];
  char *line =
    string_new(crossline_readline(prompt, bounds_buf, sizeof(bounds_buf)));
  if(string_equals(line, "")) {
    return string_new("");
  } else {
    return line;
  }
}
