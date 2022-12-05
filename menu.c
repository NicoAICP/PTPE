#include "hw.h"
#include "ST7735_TFT.h"

void initScreen(){
    //setTextWrap(true);
    fillScreen(ST7735_BLACK);
    setRotation(3);
    fillScreen(ST7735_BLACK);
}

void clearScreen(){
    fillScreen(ST7735_BLACK);
}

void drawHeader(const char *current_header){
    drawText(5, 5, current_header, ST7735_WHITE, ST7735_BLACK, 1);
    drawFastHLine(0,20,200,ST7735_WHITE);
}

void drawInitMenu(int sel){
    switch(sel){
        case 0:
            drawText(5, 37, "-  Skylanders           <", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Lego Dimensions", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Disney Infinity", ST7735_WHITE, ST7735_BLACK, 1);
            break;
        case 1:
            drawText(5, 37, "-  Skylanders", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Lego Dimensions      <", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Disney Infinity", ST7735_WHITE, ST7735_BLACK, 1);
            break;
        case 2:
            drawText(5, 37, "-  Skylanders", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Lego Dimensions", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Disney Infinity      <", ST7735_WHITE, ST7735_BLACK, 1);
            break;
    }
    
}

void drawInitSelect(){
     drawText(5, 25, "Select ToyPad to emulate:", ST7735_WHITE, ST7735_BLACK, 1);
     drawInitMenu(0);
}

void drawFooterCommands(const char *commands){
    drawText(5, 113, commands, ST7735_WHITE, ST7735_BLACK, 1);
    drawFastHLine(0,108,200,ST7735_WHITE);
}