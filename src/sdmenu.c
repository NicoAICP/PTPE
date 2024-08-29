#include "shared.h"
#include "rtc.h"
#include "f_util.h"
#include "ff.h"
#include "hw_config.h"
#include "ST7735_TFT.h"
#include <stdio.h>
#include "sdmenu.h"
void sdCardMenu(){
    if(DeviceNum == 0){
        skylanderSD();
    }
}

void skylanderSD(){
    scan_files("/Skylanders");
}

FRESULT scan_files (char* path){
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;

    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) {                    // It is a directory //
                i = strlen(path);
                char *newpath;
                sprintf(newpath, "%s/%s", path, fno.fname);
                char write[26];
                sprintf(write, "%s/%s", path, fno.fname);

                char *text = "ELEMENT: %s";
                char write2[26];
                sprintf(write2, text, fno.fname);
                drawText(5, SDLines, write2, ST7735_WHITE, ST7735_BLACK, 1);
                SDLines = SDLines+12;

                res = scan_files(write);                    // Enter the directory 
                if (res != FR_OK) break;
            } else {                                       // It is a file. 
                if(path != "/Skylanders"){
                    char *text = " - %s";
                    char write[26];
                    sprintf(write, text, fno.fname);
                    drawText(5, SDLines, write, ST7735_WHITE, ST7735_BLACK, 1);
                    SDLines = SDLines+12;
                }
            }
        }
        f_closedir(&dir);
    }

    return res;
}