#!/usr/bin/env bash
# This script will install the current stable AMMDK software stack on an installation of AMMDK Linux

git clone https://github.com/AdvancedModularManikin/development-kit.git
if [ $? -ne 0 ]; then
    exit
fi
./development-kit/AMMDK/bootstrap_software.sh

