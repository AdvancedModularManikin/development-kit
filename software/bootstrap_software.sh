#!/usr/bin/env bash
# This script will install the current stable AMMDK software stack on an installation of AMMDK Linux

check()
{
    if [ $? -ne 0 ]; then
        exit
    fi
}

echo "Installing dependencies"
sudo apt-mark hold firmware-atheros
sudo apt-mark hold lxqt*
sudo apt-mark hold liblxqt*
sudo apt update -y
sudo apt update -y
sudo apt upgrade -y
sudo apt install -y openocd cmake default-jdk xrdp tigervnc-standalone-server gradle gdb-multiarch tmux libboost-all-dev libtinyxml2-dev gcc-arm-none-eabi rapidjson-dev doxygen sqlite3 libsqlite3-dev sqlite libsqlite-dev man-db nginx supervisor fastboot
check

pushd ~/
ln -s development-kit/software/rename_board.sh .

sudo usermod -aG plugdev amm

echo "Downloading K66 code"
git clone --recursive https://github.com/AdvancedModularManikin/amm-tiny.git
check
sudo cp amm-tiny/spi_proto/99-spidev-open.rules /etc/udev/rules.d/
check
sudo udevadm control --reload-rules && sudo udevadm trigger
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

## FIXME: Installing Biogears twice should NOT be necessary
#echo "Downloading Biogears"
#scp draum@smf.vcom3d.com:/home/draum/usr_aarch64.tar.bz2 .
#check
#echo "Installing Biogears"
#sudo tar xjf usr_aarch64.tar.bz2 --strip-components=1 -C /usr
#check
#
#echo "Installing Fast-RTPS"
#git clone https://github.com/eProsima/Fast-RTPS.git
#check
#mkdir Fast-RTPS/build && pushd Fast-RTPS/build
#cmake -DBUILD_JAVA=ON -DTHIRDPARTY=ON ..
#check
#sudo make # Because Fast-RTPS has a dirty repo
#check
#sudo make install
#check
#popd
#
#echo "Installing Pistache"
#git clone --recursive https://github.com/oktal/pistache.git
#check
#mkdir pistache/build && pushd pistache/build
#cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
#check
#make
#check
#sudo make install
#check
#popd
#
#echo "Downloading Application code"
#git clone --recursive --branch develop https://github.com/AdvancedModularManikin/DDS.git
#check
#mkdir DDS/AMM_Modules/build && pushd DDS/AMM_Modules/build
#echo "Building Applications"
#cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
#check
#make
#check
#popd
#
#echo "Installing Web Interface"
#scp draum@smf.vcom3d.com:/home/draum/amm_instructor.tar.bz2 .
#check
#sudo rm -rf /var/www/html/*
#check
#sudo tar jxf amm_instructor.tar.bz2 -C /var/www/html/
#check
#ln -s DDS/AMM_Modules/build/bin/ AMM
#check
#sudo cp DDS/AMM_Modules/support/supervisor_scripts/*.conf /etc/supervisor/conf.d/
#check
#sudo systemctl restart supervisor
#check

popd
echo "Setup Completed"
