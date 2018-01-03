#!/bin/bash
# Name: start-post.sh
#   Power-on Self Test

cd ${0%/*}

#######################################################################
/usr/bin/espeak "Audio Settings" >/dev/null 2>&1
/usr/bin/espeak "Channel 0" >/dev/null 2>&1
aplay audio/channel0.wav    >/dev/null 2>&1

/usr/bin/espeak "Channel 1" >/dev/null 2>&1
aplay audio/channel1.wav    >/dev/null 2>&1

/usr/bin/espeak "Channel 2" >/dev/null 2>&1
aplay audio/channel2.wav    >/dev/null 2>&1

#######################################################################
/usr/bin/espeak "Network Settings" >/dev/null 2>&1
/usr/bin/espeak "Node name `hostname`" >/dev/null 2>&1

WIFI=`/sbin/ifconfig wlan0 | grep 'inet ' | awk '{ print $2 }' | sed -e 's/addr://'`
/usr/bin/espeak "Wifi address $WIFI" >/dev/null 2>&1

/usr/bin/espeak "Sensor Online" >/dev/null 2>&1

