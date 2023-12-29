#include "menu.h"
#include "hw.h"
#include "shared.h"
#include <stdio.h>
#include "ST7735_TFT.h"


void handleSkylander(int selection){
    if(selection != 2)
    {
        drawMenu(0);
        drawText(5, 37, "Nothing to see here", ST7735_WHITE, ST7735_BLACK, 1);
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
