#!/usr/bin/env bash
# This script will install the current stable AMMDK software stack on an installation of AMMDK Linux

check()
{
    if [ $? -ne 0 ]; then
        exit
    fi
}

if [ $USER != 'amm' ]; then
    su amm
    check
fi
git clone https://github.com/AdvancedModularManikin/development-kit.git
check
./development-kit/AMMDK/bootstrap_software.sh

