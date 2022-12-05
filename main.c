#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hw.h"
#include "ST7735_TFT.h"

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
    //setTextWrap(true);
    fillScreen(ST7735_BLACK);
    setRotation(3);
    fillScreen(ST7735_BLACK);

    drawText(5, 5, "  Pico Toy Pad Emulator  ", ST7735_WHITE, ST7735_BLACK, 1);
    drawFastHLine(0,20,200,ST7735_WHITE);

    while(1);
    return 0;
}
