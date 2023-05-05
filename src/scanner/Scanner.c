#include "Scanner.h"

string *scanner_scan(char *prompt) {
    char *line = readline(prompt);
    if(!strcmp(line, ""))
        return string_new("()");
    else if(!strcmp(line, "<<exit>>") || !strcmp(line, "<<quit>>"))
        exit(0);
    else {
        add_history(line);
        return string_new(line);
    }
}
