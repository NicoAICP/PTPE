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