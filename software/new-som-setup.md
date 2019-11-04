Change all `jessie` in `/etc/apt/sources.list` sources to `stretch` (edit as `root`)

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

    sudo dpkg-reconfigure locales

select `en_US-UTF8` in the gui

execute in tmux:

    sudo apt update && sudo apt -y dist-upgrade

Some of the approvals will not be handled by -y so babysit it

Install additional dependencies:

    sudo apt install -y libboost-all-dev openjdk-8-jdk gdb-arm-none-eabi
    
    sudo apt -t stretch-backports install openocd 

Go to /usr/local: 

    cd /usr/local

Unpack physiology engine:

    sudo tar xzf physiology.tar.gz

Copy & extract FastRTPS from ~/ on the nuc: 

    sudo scp user@10.0.1.20:~/Fast-RTPS.tar.gz . && sudo tar xzf Fast-RTPS.tar.gz

execute:
```
cd Fast-RTPS
sudo rm -rf build
mkdir build
cd build
cmake -DTHIRDPARTY=ON -DBUILD_JAVA=ON .. 
sudo make && sudo make install
```
Go home:

    cd

Get AMM DDS repo:

    git clone https://github.com/AdvancedModularManikin/DDS.git

Fix old path:

    sed -i 's/~\/workspace/\/usr\/local/g' DDS/AMM_Modules/CMakeLists.txt

execute:
```
cd DDS/AMM_Modules
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
cd
```
