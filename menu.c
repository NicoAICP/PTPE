#include "hw.h"
#include "shared.h"
#include <stdio.h>
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
void drawFooterCommands(const char *commands){
    drawText(5, 113, commands, ST7735_WHITE, ST7735_BLACK, 1);
    drawFastHLine(0,108,200,ST7735_WHITE);
}

void drawError(int ErrCode){
    clearScreen();
    switch(ErrCode){
        case 0: //No SD Card
            drawText(5, 5, "     Critical Error!     ", ST7735_RED, ST7735_BLACK, 1);
            drawFastHLine(0,20,200,ST7735_RED);
            drawText(5, 25, "Unable to Mount SD Card", ST7735_RED, ST7735_BLACK, 1);
            drawText(5, 37, "Possible Issues:", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "- Faulty / No SD Card", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "- Faulty Wiring", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 73, "- Faulty SD Formating", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 97, "Press SELECT to Reboot", ST7735_WHITE, ST7735_BLACK, 1);
            drawFastHLine(0,108,200,ST7735_RED);
            drawText(5, 113, "Git Wiki: Troubleshoot SD", ST7735_RED, ST7735_BLACK, 1);
            break;
    }
}

void drawSetupMenu(int createdConfig){
    clearScreen();
    drawText(5, 5, "       WiFi  Setup       ", ST7735_WHITE, ST7735_BLACK, 1);
    drawFastHLine(0,20,200,ST7735_WHITE);
    drawText(5, 25, "Insert the SD into your PC", ST7735_WHITE, ST7735_BLACK, 1);
    drawText(5, 37, "Edit config.ptpe:", ST7735_WHITE, ST7735_BLACK, 1);
    drawText(5, 49, "- Fill WIFI_SSID", ST7735_WHITE, ST7735_BLACK, 1);
    drawText(5, 61, "- Fill WIFI_PASS", ST7735_WHITE, ST7735_BLACK, 1);
    drawText(5, 73, "Insert the SD into the Pi", ST7735_WHITE, ST7735_BLACK, 1);
    if(createdConfig == 1){
         drawText(5, 85, "Created config.ptpe on SD", ST7735_WHITE, ST7735_BLACK, 1);
    }  
    drawFastHLine(0,108,200,ST7735_WHITE);
    drawText(5, 113, "- Press SELECT to Reboot ", ST7735_WHITE, ST7735_BLACK, 1);
}

void drawMenu(int sel){
    clearScreen();
    drawFooterCommands(" <>  <v>  <SEL>  <^>  <> ");
    switch(sel){
        case 0: //Skylanders
            drawHeader("       Skylanders        ");
            break;
        case 1: //Lego Dimensions
            drawHeader("     Lego Dimensions     ");
            break;
        case 2: //Disney Infinity
            drawHeader("     Disney Infinity     ");
            break;
        case 3: //WiFi Menu
            drawHeader("        WiFi  Menu       ");
            break;
    }
}

void drawInitMenu(int sel){
    switch(sel){
        case 0:
            DeviceNum = 0;
            drawText(5, 37, "-  Skylanders           <", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Lego Dimensions       ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Disney Infinity       ", ST7735_WHITE, ST7735_BLACK, 1);
            if(WifiAllowed == 1){
                drawText(5, 73, "-  WiFi Menu             ", ST7735_WHITE, ST7735_BLACK, 1);
            }
            break;
        case 1:
            DeviceNum = 1;
            drawText(5, 37, "-  Skylanders            ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Lego Dimensions      <", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Disney Infinity       ", ST7735_WHITE, ST7735_BLACK, 1);
            if(WifiAllowed == 1){
                drawText(5, 73, "-  WiFi Menu             ", ST7735_WHITE, ST7735_BLACK, 1);
            }
            break;
        case 2:
            DeviceNum = 2;
            drawText(5, 37, "-  Skylanders            ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Lego Dimensions       ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Disney Infinity      <", ST7735_WHITE, ST7735_BLACK, 1);
            if(WifiAllowed == 1){
                drawText(5, 73, "-  WiFi Menu             ", ST7735_WHITE, ST7735_BLACK, 1);
            }
            break;
        case 3:
            DeviceNum = 3;
            drawText(5, 37, "-  Skylanders            ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Lego Dimensions       ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Disney Infinity       ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 73, "-  WiFi Menu            <", ST7735_WHITE, ST7735_BLACK, 1);
            break;
    }
    
}

void drawWifiMenu(int sel){

    switch(sel){
        case 0:
            drawText(5, 37, "-  Setup WiFi           <", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Connect To WiFi       ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Start Transfer        ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 73, "-  Return                ", ST7735_WHITE, ST7735_BLACK, 1);
            break;
        case 1:
            drawText(5, 37, "-  Setup WiFi            ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Connect To WiFi      <", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Start Transfer        ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 73, "-  Return                ", ST7735_WHITE, ST7735_BLACK, 1);
            break;
        case 2:
            drawText(5, 37, "-  Setup WiFi            ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Connect To WiFi       ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Start Transfer       <", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 73, "-  Return                ", ST7735_WHITE, ST7735_BLACK, 1);
            break;
        case 3:
            drawText(5, 37, "-  Setup WiFi            ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 49, "-  Connect To WiFi       ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 61, "-  Start Transfer        ", ST7735_WHITE, ST7735_BLACK, 1);
            drawText(5, 73, "-  Return               <", ST7735_WHITE, ST7735_BLACK, 1);
            break;
    }
    
}


void drawPressed(int i){
    char str[5];
    sprintf(str, "%d", i); // integer to string
    drawText(5, 85, str, ST7735_WHITE, ST7735_BLACK, 1);
}

void drawInitSelect(){
     drawText(5, 25, "Select ToyPad to emulate:", ST7735_WHITE, ST7735_BLACK, 1);
     drawInitMenu(0);
}

