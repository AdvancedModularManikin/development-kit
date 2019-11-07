#!/usr/bin/env bash
# This script will install the current stable AMMDK software stack on an installation of AMMDK Linux

# Run me via: $ bash <(curl -s https://raw.githubusercontent.com/AdvancedModularManikin/development-kit/master/board_init.sh)

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
./development-kit/software/bootstrap_software.sh

