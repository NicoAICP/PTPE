# PTPE 

If you want to support this Project, feel free to do so on Ko-Fi https://ko-fi.com/nicoaicp

## Building

    git clone https://github.com/NicoAICP/PTPE.git
    cd PTPE
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make

IMPORTANT!  
You **need** a Pi PICO SDK Version of atleast 1.4.0 but you cannot use 1.5.0 or higher. I recommend using 1.4.0

IMPORTANT #2!  
Replace the ST7735_TFT.c in pico-st7735/lib-st7735/src with the one in the root of this project.  
This is needed for the display to display text correctly!

IMPORTANT #3!  
You need to copy the tusb_config.h into this location pico-sdk-location\lib\tinyusb\src\tusb_config.h

IMPORTANT #4!  
You need to copy the lwipopts.h into this location pico-sdk-location\lib\lwip\src\include\lwip\lwipopts.h  


## Connecting the LCD:
SCK -> GP14 (Pin 19)  
SDA -> GP15 (Pin 20)  
A0 -> GP10 (Pin 14)  
RESET -> GP11 (Pin 15)  
CS -> GP9 (Pin 12)  
LED -> 3.3V (Pin 36)  
GND -> GND (Pin 38)  
VCC -> 5V (Pin 40)

## Connecting a SD Card Reader
SD_CS -> GP5 (Pin 7)  
SD_MOSI -> GP3 (Pin 5)  
SD_MISO -> GP4 (Pin 6)  
SD_SCK -> GP2 (Pin 4)  
  
## Connecting the Buttons  
You will be needing 5 Buttons  
- Button1 (Misc 1)  
GP16 (Pin 21)  
- Button2 (Left/Down)  
GP17 (Pin 22)  
- Button3 (Select)  
GP18 (Pin 24)  
- Button4 (Right/Up)  
GP19 (Pin 25)  
- Button5 (Misc 2)  
GP20 (Pin 26)
