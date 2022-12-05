# PTPE
## Building

    git clone https://github.com/NicoAICP/PTPE.git
    cd PTPE
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make

IMPORTANT!  
Replace the ST7735_TFT.c in pico-st7735/lib-st7735/src with the one in the root of this project.  
This is needed for the display to display text correctly!

## Connecting the LCD:
SCK -> GP14 (Pin 19)  
SDA -> GP15 (Pin 20)  
A0 -> GP10 (Pin 14)  
RESET -> GP11 (Pin 15)  
CS -> GP9 (Pin 12)  
LED -> 3.3V (Pin 36)  
GND -> GND (Pin 38)  
VCC -> 5V (Pin 40)