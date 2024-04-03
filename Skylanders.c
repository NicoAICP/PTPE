#include "menu.h"
#include "hw.h"
#include "shared.h"
#include <stdio.h>
#include "ST7735_TFT.h"
#include "f_util.h"
#include "ff.h"
#include "hw_config.h"
#include "rtc.h"
int SkylanderEndsWith(char *str, char *suffix)
{
  int str_len = strlen(str);
  int suffix_len = strlen(suffix);

  return (str_len >= suffix_len) &&
         (0 == strcmp(str + (str_len - suffix_len), suffix));
}

void GetSkylanderCount(){
    FRESULT res;
    DIR dir;
    FILINFO fno;
    bool skylander = false;
    SkylanderCount = 0;
    f_opendir(&dir, "/Skylanders"); // Open Skylanders folder
    do
    {
    skylander = false;
    f_readdir(&dir, &fno);
    if (fno.fname[0] != 0)
    {

      if (SkylanderEndsWith(fno.fname, "bin") == 1 || SkylanderEndsWith(fno.fname, "sky") == 1 || SkylanderEndsWith(fno.fname, "dmp") == 1 || SkylanderEndsWith(fno.fname, "dump") == 1)
      {
        printf("Skylander found: %s\n", fno.fname);
        // skylanderFileNames[sd_skylander_count] = fno.fname;
        SkylanderCount++;
      }
      else
      {
        printf("File is not a Skylander: %s\n", fno.fname);
      }
    }

    } while (fno.fname[0] != 0);
    f_closedir(&dir);
}

void handleSkylander(int selection){
    if(selection != 2)
    {
        
        drawMenu(0);
        if(selection == 0){
            char text[40];
            sprintf(text, "Skylanders found: %i", SkylanderCount);
            drawText(5, 37, text, ST7735_WHITE, ST7735_BLACK, 1);
        }else{
            drawText(5, 37, "Nothing to see here", ST7735_WHITE, ST7735_BLACK, 1);
        }
        
        sleep_ms(1000);
        SkylanderMenu(currSel, 0);
    }
    else
    {
        reboot();
    }
    
}

void SkylanderMenu(int cursor, int select){
    if(select == 1){
        GetSkylanderCount();
        handleSkylander(cursor);
    }
    else
    {
        switch(cursor){
            case 0:
                drawText(5, 37, "-  Add Skylander        <", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 49, "-  Remove Skylander      ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 61, "-  Exit Emulation        ", ST7735_WHITE, ST7735_BLACK, 1);
                break;
            case 1:
                drawText(5, 37, "-  Add Skylander         ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 49, "-  Remove Skylander     <", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 61, "-  Exit Emulation        ", ST7735_WHITE, ST7735_BLACK, 1);
            
                break;
            case 2:
                drawText(5, 37, "-  Add Skylander         ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 49, "-  Remove Skylander      ", ST7735_WHITE, ST7735_BLACK, 1);
                drawText(5, 61, "-  Exit Emulation       <", ST7735_WHITE, ST7735_BLACK, 1);
                break;
        }
    }
}
