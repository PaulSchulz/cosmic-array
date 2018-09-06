#!/bin/bash

cd ${0%/*}

sudo apt update
sudo apt install espeak
sudo apt install wiringpi

if [ `arch` = "armv7l" ] || [ `arch` = "armv6l" ]; then
    # Set @reboot function
    crontab crontab.pi

fi

sync; sync
