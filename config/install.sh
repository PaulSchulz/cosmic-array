#!/bin/bash

cd ${0%/*}

sudo apt update
sudo apt install espeak

if [ `arch` = "armv7l" ] || [ `arch` = "armv6l" ]; then
    # Set @reboot function
    crontab crontab.pi

    # Set audio overlay to send audio to PWM pins. 
    sudo bash -c "cat config.txt >> /boot/config.txt"

    # Set Volume
    sudo amixer -c 0 set PCM playback 100% unmute 
fi

sync; sync
