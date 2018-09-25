#!/usr/bin/env bash
# This script will install the current stable AMMDK software stack on an installation of AMMDK Linux

echo "Installing dependencies"
sudo apt update -y
sudo apt install -y openocd cmake default-jdk gradle libboost-all-dev libtinyxml2-dev

echo "Downloading K66 code"
pushd ~/
git clone --recursive https://github.com/AdvancedModularManikin/amm-tiny.git
pushd amm-tiny/
echo "Building K66 code"
./gencmake.sh
make
echo "Flashing K66"
./flash.sh debug/amm-tiny.elf
popd

echo "Installing Fast-RTPS"
git clone --branch v1.6.0 https://github.com/eProsima/Fast-RTPS.git
pushd Fast-RTPS
mkdir build && pushd build
cmake -DTHIRDPARTY=ON ..
make
sudo make install
popd

echo "Downloading Application code"
git clone --branch develop https://github.com/AdvancedModularManikin/DDS.git
pushd DDS
mkdir build && pushd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
popd
popd
popd
