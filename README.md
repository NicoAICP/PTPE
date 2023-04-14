Demo/Test program for the Library pico-st7735
=============================================

Quickstart:

    git clone https://github.com/bablokb/pico-st7735-demo.git
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make

Note that both the toplevel `CMakeLists.txt` and the
library-level `pico-st7735/CMakeLists.txt` write variables
into the cache. Once written, they are kept until manually
deleted. This is to set default values in the lib-file
and override them on first run from the top-level file
(or the cmake commandline).

