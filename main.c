#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hw.h"
#include "shared.h"
#include "menu.h"
#include "ST7735_TFT.h"
#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"
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

// ---------------------------------------------------------------------------
int main() {

    init_hw();
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
    drawHeader("  Pico Toy Pad Emulator  ");
    drawInitSelect();
    drawFooterCommands(" <>  <v>  <SEL>  <^>  <> ");
    void hid_task(void);

    ////TODO: THIS IS ONLY TO BE CALLED AFTER MENU SELECTION, SETS THE DEVICENUM
    //TINY USB INIT 
    board_init();
    tud_init(0);


    while(1){
        tud_task();
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