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
#include "hardware/watchdog.h"

#include "rtc.h"
#include "f_util.h"
#include "ff.h"
#include "hw_config.h"

#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

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

void reboot(){
    clearScreen();
    sleep_ms(500);
    watchdog_enable(1, 1);
    while(1);
}

void handleWifi(){
    if(Connected == 1){
        char text[26];
        sprintf(text," Pico IP: %s",ip4addr_ntoa(netif_ip4_addr(netif_list)));
        drawIPHeader(text);
    }
    drawWifiMenu(0);
    int wifiSel = 0;
    int Selected = 0;

    while(Selected == 0)
    {
        if (!gpio_get(BUTTON_LEFT))
        {
            if(wifiSel < 4){
                wifiSel++;
            }
            drawWifiMenu(wifiSel);
        }
        else if (!gpio_get(BUTTON_SELECT))
        {
            Selected = 1;
        }
        else if (!gpio_get(BUTTON_RIGHT))
        {
             if(wifiSel > 0){
                wifiSel--;
            }
            drawWifiMenu(wifiSel);
        }
        
    }
    
    FRESULT res;
    DIR dir;
    FILINFO fno;
    FIL fp;
    
    switch(wifiSel){
        case 0:
            f_opendir(&dir, "/"); // Open Root
            res = f_open(&fp, "config.ptpe", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
            int i = f_puts("[CONFIG_WIFI];WIFI_SSID=;WIFI_PASS=;",&fp);
            f_close(&fp);
            drawSetupMenu(1);
            while(1)
            {
                if(!gpio_get(BUTTON_SELECT))
                {
                    reboot();
                }
            }
            break;
        case 1:
            //TODO: Connect to Wifi
            f_opendir(&dir, "/"); // Open Root
            res = f_open(&fp, "config.ptpe", FA_READ);
            if(res){
                drawError(1);
                while(1)
                {   
                    if(!gpio_get(BUTTON_SELECT))
                    {
                        reboot();
                    }
                }
            }
            TCHAR buff;
            char *pre_ssid;
            char *pre_pass;
            char *ssid;
            char *pass;
            f_gets(&buff, 1000, &fp);
            f_close(&fp);
            
            strtok(&buff,";");
            pre_ssid = strtok(NULL,";");
            pre_pass = strtok(NULL,";");
            
            strtok(pre_ssid, "=");
            ssid = strtok(NULL,"=");

            strtok(pre_pass, "=");
            pass = strtok(NULL,"=");

            cyw43_arch_enable_sta_mode();
            int err = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 20000);
            if (err != 0) {
                drawError(2);
                while(1)
                {   
                    if(!gpio_get(BUTTON_SELECT))
                    {
                        reboot();
                    }
                }
            }
            Connected = 1;
            handleWifi();
            
            break;
        case 2:
            //TODO: TCP Transfer Server
            //opens a tcp transfer server to recieve Files
            drawError(99); //ERROR FOR NOT IMPLEMENTED
            while(1)
            {   
                if(!gpio_get(BUTTON_SELECT))
                {
                    reboot();
                }
            }
            break;
        case 3:
            reboot();
            break;
    }
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

    drawHeader("        INIT PTPE        ");

    if(WifiAllowed == 1){
        maxSel = 3;
    }

    // SDCARD INIT
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    if (FR_OK != fr)
    {
        drawError(0);
        while(true){
           if (!gpio_get(BUTTON_SELECT))
            {
                reboot();
            }    
        };
    }
    clearScreen();
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

    if(DeviceNum == 3){
        handleWifi();
    }

    void hid_task(void);    
    
    
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