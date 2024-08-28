# PTPE

Don't worry, PTPE is not dead, i just haven't coded in a while due to burnout.

## Building under Windows using WSL

 - Make sure to have Virtualisation enabled

 - Activate WSL
   
    System Control Panel -> Programs and Features -> Activate/Deactivate Windows Features -> Activate Windows Subsystem for Linux

 - Open Powershell and enter
    wsl --install

 - Reboot your computer

 - Go into the Microsoft Store and Get Ubuntu

 - Open Ubuntu

 - Setup Ubuntu

 - Exit Ubuntu

 - Open Powershell and enter
    wsl --set-version Ubuntu 1

 - Open Ubuntu and do following steps:

    > sudo apt-get update
    > 
    > sudo apt-get upgrade
    > 
    > sudo apt-get install doxygen
    > 
    > sudo apt-get install g++
    > 
    > sudo apt-get install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
    > 
    > cd [Path of your Development Folder]
    >
    > 
    > git clone clone https://github.com/raspberrypi/pico-sdk
    > 
    > cd pico-sdk
    > 
    > git submodule update --init
    > 
    > cd ..
    > 
    > git clone https://github.com/NicoAICP/PTPE.git
    > 
    > cd PTPE
    > 
    > git submodule update --init --recursive

 - Now in your File Explorer do following things:
   
    In the PTPE repository please copy the tusb_config.h file to [Path of your Development Folder]\pico-sdk\lib\tinyusb\src\tusb_config.h

 - Go back to the WSL/Ubuntu Windows

 - Building for RP2040 (Pico 1)
   
    > mkdir build_rp2040
    > 
    > cd build_rp2040
    > 
    > export PICO_SDK_PATH=../../pico-sdk
    > 
    > cmake ..
    > 
    > make

 - Building for RP2350 (Pico 2)

    > mkdir build_rp2350
    > 
    > cd build_rp2350
    > 
    > export PICO_SDK_PATH=../../pico-sdk
    > 
    > cmake .. -DPICO_PLATFORM=rp2350-arm-s
    > 
    > make

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
