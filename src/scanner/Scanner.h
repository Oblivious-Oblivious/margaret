#ifndef __SCANNER_H_
#define __SCANNER_H_

#include "../../libs/EmeraldsCrossline/export/crossline/crossline.h"
#include "../vm/vm.h"

/**
 * @brief Scans a string using provided prompt from command line
    Utilizes `Crossline` library for saving to history
 * @param prompt -> Displays it for each command
 * @param vm -> The VM object
 * @return VM* -> The VM object
 */
VM *scanner_scan(VM *vm, char *prompt);

#endif
