#!/bin/sh
#ARMGCC_DIR=~/code/arm-gcc-toolchain/gcc-arm-none-eabi-5_4-2016q3/ cmake .
OS=`uname`
if [ $OS = "Darwin" ]
then
	#osx
	ARMGCC_DIR=/usr/local/Cellar/arm-none-eabi-gcc/7-2017-q4-major cmake -DCMAKE_TOOLCHAIN_FILE="armgcc.cmake" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug .
else
	#ammdk boards
	ARMGCC_DIR=/usr/ cmake -DCMAKE_TOOLCHAIN_FILE="armgcc.cmake" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug .
fi
