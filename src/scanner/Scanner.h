#ifndef __SCANNER_H_
#define __SCANNER_H_

#include <stdio.h> /* FILE */

#include "../../libs/readline/readline/readline.h"
#include "../../libs/readline/readline/history.h"

#include "../base/string.h"

/**
 * @brief Scans a string using provided prompt from command line
    Utilizes `Readline` library for saving to history
 * @param prompt -> Displays it for each command
 * @return string* -> Value typed in `string` form
 */
string *scanner_scan(char *prompt);

#endif
