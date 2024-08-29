#include "rtc.h"
#include "f_util.h"
#include "ff.h"
#include "hw_config.h"

void sdCardMenu();
void skylanderSD();
FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
);