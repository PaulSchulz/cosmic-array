#!/bin/bash

cd ${0%/*} #

/usr/bin/gpio mode 0 in
/usr/bin/gpio mode 1 in
/usr/bin/gpio mode 2 in

/usr/bin/gpio mode 0 tri
/usr/bin/gpio mode 1 tri
/usr/bin/gpio mode 2 tri

sudo amixer -c 0 set PCM playback 90% unmute >/dev/null 2>&1

#######################################################################
# Selftest
/usr/bin/espeak "Channel 0" >/dev/null 2>&1
aplay audio/channel0.wav    >/dev/null 2>&1

/usr/bin/espeak "Channel 1" >/dev/null 2>&1
aplay audio/channel1.wav    >/dev/null 2>&1

/usr/bin/espeak "Channel 2" >/dev/null 2>&1
aplay audio/channel2.wav    >/dev/null 2>&1

/usr/bin/espeak "Channel 3" >/dev/null 2>&1
aplay audio/channel3.wav    >/dev/null 2>&1
#######################################################################

/usr/bin/espeak "Cosmic Array Sensor Online. Node name `hostname`" \
  >/dev/null 2>&1

$HOME/git/cosmic-array/bin/shoreman >/dev/null 2>&1 


