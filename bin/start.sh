#!/bin/bash

cd ${0%/*} #

/usr/bin/gpio mode 0 in
/usr/bin/gpio mode 1 in
/usr/bin/gpio mode 2 in

/usr/bin/gpio mode 0 tri
/usr/bin/gpio mode 1 tri
/usr/bin/gpio mode 2 tri

sudo amixer -c 0 set PCM playback 97% unmute >/dev/null 2>&1

#######################################################################
/usr/bin/espeak "Cosmic Array Sensor starting" >/dev/null 2>&1

if [ -d  audio/`hostname` ]; then
        /usr/bin/espeak "Host based audio found." >/dev/null 2>&1
	rm audio/channel0.wav; ln -s `hostname`/channel0.wav audio/channel0.wav
	rm audio/channel1.wav; ln -s `hostname`/channel1.wav audio/channel1.wav
	rm audio/channel2.wav; ln -s `hostname`/channel2.wav audio/channel2.wav
else
        /usr/bin/espeak "Default audio being used." >/dev/null 2>&1
	rm audio/channel0.wav; ln -s default/channel0.wav audio/channel0.wav
	rm audio/channel1.wav; ln -s default/channel1.wav audio/channel1.wav
	rm audio/channel2.wav; ln -s default/channel2.wav audio/channel2.wav
fi

/usr/bin/espeak "Channel 0" >/dev/null 2>&1
aplay audio/channel0.wav    >/dev/null 2>&1

/usr/bin/espeak "Channel 1" >/dev/null 2>&1
aplay audio/channel1.wav    >/dev/null 2>&1

/usr/bin/espeak "Channel 2" >/dev/null 2>&1
aplay audio/channel2.wav    >/dev/null 2>&1

#######################################################################

/usr/bin/espeak "Node name `hostname`" >/dev/null 2>&1

WIFI=`/sbin/ifconfig wlan0 | grep 'inet ' | awk '{ print $2 }' | sed -e 's/addr://'`
/usr/bin/espeak "Wifi address $WIFI" >/dev/null 2>&1

/usr/bin/espeak "Sensor Online" >/dev/null 2>&1

# $HOME/git/cosmic-array/bin/shoreman >shoreman.log 2>&1
$HOME/git/cosmic-array/bin/shoreman >/dev/null 2>&1 


