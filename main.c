#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "hw.h"
#include "shared.h"
#include "menu.h"
#include "ST7735_TFT.h"
#include "bsp/board.h"
#include "tusb.h"
#include "pico/cyw43_arch.h"
#include "usb_descriptors.h"



#define PicoW 1
#define BUTTON_MISC1 16
#define BUTTON_LEFT 17
#define BUTTON_SELECT 18
#define BUTTON_RIGHT 19
#define BUTTON_MISC2 20
// ---------------------------------------------------------------------------
// hardware-specific intialization
// SPI_* constants from CMakeLists.txt or user.h

void init_hw() {
  stdio_init_all();
  spi_init(SPI_PORT, 1000000);                // SPI with 1Mhz
  gpio_set_function(SPI_RX, GPIO_FUNC_SPI);
  gpio_set_function(SPI_SCK,GPIO_FUNC_SPI);
  gpio_set_function(SPI_TX, GPIO_FUNC_SPI);
  tft_spi_init();
}

void init_buttons(){
    // INIT GPIO for buttons
  gpio_init(BUTTON_MISC1);
  gpio_set_dir(BUTTON_MISC1, GPIO_IN);
  gpio_pull_up(BUTTON_MISC1);

  gpio_init(BUTTON_LEFT);
  gpio_set_dir(BUTTON_LEFT, GPIO_IN);
  gpio_pull_up(BUTTON_LEFT);

  gpio_init(BUTTON_RIGHT);
  gpio_set_dir(BUTTON_RIGHT, GPIO_IN);
  gpio_pull_up(BUTTON_RIGHT);

  gpio_init(BUTTON_SELECT);
  gpio_set_dir(BUTTON_SELECT, GPIO_IN);
  gpio_pull_up(BUTTON_SELECT);

  gpio_init(BUTTON_MISC2);
  gpio_set_dir(BUTTON_MISC2, GPIO_IN);
  gpio_pull_up(BUTTON_MISC2);
}

// ---------------------------------------------------------------------------
int main() {

    init_hw();
    init_buttons();
//This code snippet will only be called if PicoW is set to 1. There will be a Wifi and a no Wifi build
#if PicoW == 1
    if( cyw43_arch_init() == 0){
        WifiAllowed = 1;
    };
#endif

#ifdef TFT_ENABLE_BLACK
    TFT_BlackTab_Initialize();
#elif defined(TFT_ENABLE_GREEN)
    TFT_GreenTab_Initialize();
#elif defined(TFT_ENABLE_RED)
    TFT_RedTab_Initialize();
#elif defined(TFT_ENABLE_GENERIC)
    TFT_ST7735B_Initialize();
#endif
    DeviceNum = 1; //TODO: ADD TO SELECTION
    initScreen();
    clearScreen();

    int currSel = 0;
    int maxSel = 2;

    if(WifiAllowed == 1){
        maxSel = 3;
    }

    drawHeader("  Pico Toy Pad Emulator  ");
    drawInitSelect();
    drawFooterCommands(" <>  <v>  <SEL>  <^>  <> ");

    //Menu Selection
    while(Selected == 0)
    {
        if (!gpio_get(BUTTON_LEFT))
        {
            if(currSel < maxSel){
                currSel++;
            }
            drawInitMenu(currSel);
        }
        else if (!gpio_get(BUTTON_SELECT))
        {
            Selected = 1;
        }
        else if (!gpio_get(BUTTON_RIGHT))
        {
             if(currSel > 0){
                currSel--;
            }
            drawInitMenu(currSel);
        }
        
    }

    drawMenu(currSel);

    void hid_task(void);

    if(DeviceNum != 3 && DeviceNum != 2) //IF DeviceNum == 3 then we selected wifi menu (Num2 disabled since no Disney support)
    {   
        //TINY USB INIT 
        board_init();
        tud_init(0);

        while(1){
            tud_task();
        }
    }
    return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void)remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint8_t len)
{
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) // Console/ Computer sends data (Query, Shutdown etc.)
{
 
  
}