#!/usr/bin/env bash
# This script will change the hostname of the OS

HOSTS_FILE=/etc/hosts
OLD_HOSTNAME=`cat /etc/hostname`
if [[ $# -eq 0 || $1 == -* ]]; then
    echo "Specify desired new name. e.g. AMM-Core, AMM-Torso, or AMM-Fluidics"
else
    if [ `whoami` != root ]; then
        >&2 echo "Script must be run using sudo."
        exit
    fi
    NEW_HOSTNAME=$1
    hostnamectl set-hostname ${NEW_HOSTNAME}
    sed -i "s/${OLD_HOSTNAME}/${NEW_HOSTNAME}/g" ${HOSTS_FILE}
    echo "Renamed board from ${OLD_HOSTNAME} to ${NEW_HOSTNAME}"
fi
