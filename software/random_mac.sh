#!/bin/bash
od -An -N6 -tx1 /dev/urandom | sed -e 's/^  *//' -e 's/  */:/g' -e 's/:$//' -e 's/^\(.\)[13579bdf]/\10/'
# Blatantly stolen from https://stackoverflow.com/questions/42660218/bash-generate-random-mac-address-unicast
