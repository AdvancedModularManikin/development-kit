#!/usr/bin/env bash
# This script will install the current stable AMMDK software stack on an installation of AMMDK Linux

check()
{
    if [ $? -ne 0 ]; then
        exit
    fi
}

echo "Installing dependencies"
sudo apt update -y
sudo apt update -y
sudo apt upgrade -y
sudo apt install -y openocd cmake default-jdk gradle gdb-multiarch tmux libboost-all-dev libtinyxml2-dev gcc-arm-none-eabi rapidjson-dev doxygen sqlite3 libsqlite3-dev sqlite libsqlite-dev man-db
check

pushd ~/
ln -s development-kit/AMMDK/rename_board.sh .

echo "Downloading K66 code"
git clone --recursive https://github.com/AdvancedModularManikin/amm-tiny.git
check
pushd amm-tiny/
echo "Building K66 code"
./gencmake.sh
check
make
check
echo "Flashing K66"
./flash.sh debug/amm-tiny.elf
check
popd

# FIXME: Installing Biogears twice should NOT be necessary
echo "Downloading Biogears"
scp draum@smf.vcom3d.com:/home/draum/usr_aarch64.tar.bz2 .
check
echo "Installing Biogears"
sudo tar xjf usr_aarch64.tar.bz2 --strip-components=1 -C /usr
check

echo "Installing Fast-RTPS"
git clone https://github.com/eProsima/Fast-RTPS.git
check
mkdir Fast-RTPS/build && pushd Fast-RTPS/build
cmake -DBUILD_JAVA=ON -DTHIRDPARTY=ON ..
check
sudo make # Because Fast-RTPS has a dirty repo
check
sudo make install
check
popd

echo "Installing Pistache"
git clone --recursive https://github.com/oktal/pistache.git
check
mkdir pistache/build && pushd pistache/build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
check
make
check
sudo make install
check
popd

echo "Downloading Application code"
git clone --recursive --branch develop https://github.com/AdvancedModularManikin/DDS.git
check
mkdir DDS/AMM_Modules/build && pushd DDS/AMM_Modules/build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
check
make
check
popd

popd
