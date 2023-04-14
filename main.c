
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "hw.h"
#include "ST7735_TFT.h"

//#include "bsp/board.h"
//#include "tusb.h"

#include "shared.h"

#include "menu.h"

//#include "rtc.h"
//#include "f_util.h"
//#include "ff.h"
//#include "hw_config.h"
/*
#include "pico/cyw43_arch.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
*/
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
  spi_init(SPI_PORT, 25000000);                // SPI with 1Mhz
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
// main loop

int main() {
  init_hw();
  init_buttons();
#ifdef TFT_ENABLE_BLACK
  TFT_BlackTab_Initialize();
#elif defined(TFT_ENABLE_GREEN)
  TFT_GreenTab_Initialize();
#elif defined(TFT_ENABLE_RED)
  TFT_RedTab_Initialize();
#elif defined(TFT_ENABLE_GENERIC)
  TFT_ST7735B_Initialize();
#endif

  DeviceNum = 1;
  int currSel = 0;
  int maxSel = 2;

  initScreen();
  clearScreen();

  drawHeader("        INIT PTPE        ");

  clearScreen();
  drawHeader("  Pico Toy Pad Emulator  ");
  drawInitSelect();
  drawFooterCommands(" <>  <v>  <SEL>  <^>  <> ");

  while(Selected == 0)
  {
        if (!gpio_get(BUTTON_LEFT))
        {
            if(currSel < maxSel){
                currSel++;
            }
            sleep_ms(300);
            drawInitMenu(currSel);
        }
        else if (!gpio_get(BUTTON_SELECT))
        {
            Selected = 1;
            sleep_ms(300);
        }
        else if (!gpio_get(BUTTON_RIGHT))
        {
             if(currSel > 0){
                currSel--;
            }
            sleep_ms(300);
            drawInitMenu(currSel);
        }
        
    }

  drawMenu(currSel);

  if(DeviceNum == 3){
      //handleWifi();
  }


  while(1);
  return 0;
}
