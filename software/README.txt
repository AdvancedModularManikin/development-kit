AMMDK Tiny SDK documentation

#Installing

Download the gnu arm embedded toolchain from the debian repos:
    sudo apt-get install gcc-arm-none-eabi
    sudo apt-get install gdb-arm-none-eabi

Download JLink GDB Server from https://www.segger.com/downloads/jlink/ , it is in the J-Link Software and Documentation Pack. Move it to a location of your choice. Add it to your PATH if you want.

Included in this package is the freely redistributable portions of the Kinetis SDK. If you would like the full SDK, which will add some middleware, download the Kinetis SDK 2.3 from https://mcuxpresso.nxp.com/en/welcome by selecting the SDK for the K66F board. Registration for an NXP account is required. The SDK contains packages with BSD 3-clause, GPL2, and Apache2 licenses, as well as a CC0 and one personal license that's open source compatible. 

Edit gencmake.sh with the path to the location of the gnu arm embedded toolchain. If you installed with apt-get, this location is /usr/. Ensure you have CMake installed and on your path. Execute `gencmake.sh` to create your initial build files, then `make` and `make clean` will build and clean the environment. The executable is produced in debug/ for a debug build.

#Debugging
Launch JLinkGDBServer. You will need to provide several flags, which are listed in `ammdk-tiny-example/gdb_instructions.txt`.
Launch the GDB frontend of your choice. In GDB, you will need to use the `file` command to load data onto the chip and "target remote ip-of-machine-JLinkGDBServer-is-on:port-jlink-mentioned" to select the k66f as your target. after loading, type `monitor reset` to reset the system and then `c` to begin (continue) execution. ^C will halt execution. gdb has many other features which are beyond the scope of this file.

Contact ammdk@entropicengineering.com for support.