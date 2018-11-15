#!/usr/bin/env bash
# This script will change the hostname of the OS

HOSTNAME_FILE=/etc/hostname
HOSTS_FILE=/etc/hosts
HOSTNAME_SCRIPT=/etc/init.d/hostname.sh
OLD_HOSTNAME=`cat /etc/hostname`
if [[ $# -eq 0 || $1 == -* ]]; then
    echo "Specify desired new name. e.g. AMM-Core, AMM-Torso, or AMM-Fluidics"
else
    if [ `whoami` != root ]; then
        echo "Script must be run using sudo."
    fi
    NEW_HOSTNAME=$1
    sed -i "s/${OLD_HOSTNAME}/${NEW_HOSTNAME}/g" ${HOSTNAME_FILE}
    sed -i "s/${OLD_HOSTNAME}/${NEW_HOSTNAME}/g" ${HOSTS_FILE}
    ${HOSTNAME_SCRIPT} start
    echo "Renamed board from ${OLD_HOSTNAME} to ${NEW_HOSTNAME}"
fi
