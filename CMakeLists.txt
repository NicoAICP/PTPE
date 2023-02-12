cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
set(PICO_BOARD pico_w)
project(ptpe C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()


# Initialize the SDK
pico_sdk_init()

# library configuration (override if necessary, see pico-st7735 for a complete list)
set(SPI_TFT_PORT "spi1" CACHE STRING "TFT spi port-name")
set(SPI_TFT_CS   "9"    CACHE STRING "TFT CS  pin number")
set(SPI_TFT_DC   "10"   CACHE STRING "TFT DC  pin number")
set(SPI_TFT_RST  "11"   CACHE STRING "TFT RST pin number")
set(TFT_OPTIONS TFT_ENABLE_ALL
            CACHE STRING "TFT options/functions") #RED TFT_ENABLE_RESET TFT_ENABLE_TEXT TFT_ENABLE_SHAPES
                #TFT_ENABLE_ROTATE TFT_ENABLE_SCROLL

#program configuration
set(SPI_PORT "spi1" CACHE STRING "spi port-name")
set(SPI_RX   "12"   CACHE STRING "RX  pin number")
set(SPI_TX   "15"   CACHE STRING "TX  pin number")
set(SPI_SCK  "14"   CACHE STRING "SCK pin number")

add_compile_definitions(SPI_PORT=${SPI_PORT})
add_compile_definitions(SPI_RX=${SPI_RX})
add_compile_definitions(SPI_TX=${SPI_TX})
add_compile_definitions(SPI_SCK=${SPI_SCK})
foreach(opt IN LISTS TFT_OPTIONS)
    message(">>> using: ${opt}")
    add_compile_definitions(${opt})
endforeach(opt)

# ENABLE_FONTS: set on command-line or select from
# VSCode-menu (see .vscode/cmake-variants.json)
if(ENABLE_FONTS)
  message(">>> Font test")
  add_compile_definitions(TFT_ENABLE_FONTS ENABLE_TEST9 ENABLE_TEST9A)
else()
  message(">>> Normal test")
  add_compile_definitions(ENABLE_TESTR ENABLE_TEST1 ENABLE_TEST1A
                           ENABLE_TEST2 ENABLE_TEST3 ENABLE_TEST4
                           ENABLE_TEST5 ENABLE_TEST6 ENABLE_TEST7)
endif()

# add preprocessor-constant DEBUG for Debug-builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_VERBOSE_MAKEFILE 1)
  add_compile_definitions(DEBUG)
else()
endif()
set(INCLUDE_DIR /libs)
include_directories (${INCLUDE_DIR})
add_executable(PTPE
        main.c
        )

target_sources(PTPE PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/menu.c
        ${CMAKE_CURRENT_LIST_DIR}/shared.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/hw_config.c
        )
add_subdirectory(no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)
add_subdirectory(pico-st7735)       
#add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)
#include_directories(lib/openssl/include )

# pull in common dependencies 
target_link_libraries(
        PTPE 
        PUBLIC 
        pico_stdlib tinyusb_device tinyusb_board hardware_i2c hardware_gpio
        hardware_spi
        pico_cyw43_arch_lwip_threadsafe_background 
        st7735
        FatFs_SPI
)

# Tell CMake where to find other source code

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(PTPE)