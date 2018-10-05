#!/usr/bin/env bash
# This script will install the current stable AMMDK software stack on an installation of AMMDK Linux

echo "Installing dependencies"
sudo apt update -y
sudo apt install -y openocd cmake default-jdk gradle libboost-all-dev libtinyxml2-dev gcc-arm-none-eabi rapidjson-dev sqlite3 libsqlite3-dev sqlite libsqlite-dev

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

echo "Downloading Biogears"
scp draum@smf.vcom3d.com:/home/draum/usr_aarch64.tar.bz2 .
echo "Installing Biogears"
sudo tar xjf usr_aarch64.tar.bz2 --strip-components=1 -C /usr

echo "Installing Fast-RTPS"
git clone https://github.com/eProsima/Fast-RTPS.git
pushd Fast-RTPS
mkdir build && pushd build
cmake -DBUILD_JAVA=ON -DTHIRDPARTY=ON ..
sudo make # Because Fast-RTPS has a dirty repo
sudo make install
popd

echo "Downloading Application code"
git clone --recursive --branch develop https://github.com/AdvancedModularManikin/DDS.git
mkdir DDS/AMM_Modules/build && pushd DDS/AMM_Modules/build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
popd
popd
popd
