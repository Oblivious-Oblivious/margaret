#ifndef __SCANNER_H_
#define __SCANNER_H_

#include "../../libs/EmeraldsCrossline/export/crossline/crossline.h"

/**
 * @brief Scans a string using provided prompt from command line
    Utilizes `Crossline` library for saving to history
 * @param prompt -> Displays it for each command
 * @return string* -> Value typed in `string` form
 */
char *scanner_scan(char *prompt);

#endif
