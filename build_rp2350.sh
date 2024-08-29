#!/bin/sh
#Building for RP2350
rm -rf /build_rp2350
mkdir build_rp2350
cd build_rp2350 || exit
export PICO_SDK_PATH=$pico_sdk_path
cmake .. -DPICO_PLATFORM=rp2350-arm-s
make
cd .. 