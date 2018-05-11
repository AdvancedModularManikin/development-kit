Change all `jessie` in `/etc/apt/sources.list` sources to `stretch`

Add `stretch-backports` for openocd 0.10

result:
```
deb http://httpredir.debian.org/debian stretch main
deb http://ftp.debian.org/debian/ stretch main contrib non-free
deb http://ftp.debian.org/debian/ stretch-updates main contrib non-free
deb http://ftp.debian.org/debian/ stretch-backports main contrib
deb-src http://ftp.debian.org/debian/ stretch main contrib non-free
deb-src http://ftp.debian.org/debian/ stretch-updates main contrib non-free
```

execute:
`sudo dpkg-reconfigure locales`
select en us utf8 in the gui

execute in tmux:
```
sudo apt update
sudo apt -y dist-upgrade
```

Some of the approvals will not be handled by -y so babysit it

untar physiology.tar.gz into /usr/local/ so that it's /usr/local/physiology

    sudo apt install libboost-all-dev openjdk-8-jdk

untar Fast-RTPS.tar.gz into ~/
execute:
```
cd Fast-RTPS
rm -rf build
mkdir build
cd build
cmake -DTHIRDPARTY=ON -DBUILD_JAVA=ON .. 
make
make install
```

    git clone https://github.com/AdvancedModularManikin/DDS.git

In DDS/AMM_Modules/CMakeLists.txt edit the line
SET(ENV{BIOGEARS_HOME} "~/workspace/physiology")
to
SET(ENV{BIOGEARS_HOME} "/usr/local/physiology")

execute:
```
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
```
	
how to install gdb and openocd on the board?


openocd

    install the tool that lets you add repos from the command line
	add stretch-backports repo
	sudo apt-get install openocd


This will also install the arm-none-eabi toolchain

    sudo apt-get install arm-none-eabi-gdb

To compile k66 code, edit `gencmake.sh` with the path to arm-none-eabi-gcc and run `./gencmake.sh && make`

copy the USB MSD flashing script, `flash.sh`, onto SoM and chmod +x it
