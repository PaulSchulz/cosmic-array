#!/bin/bash

cd ${0%/*}

/usr/bin/gpio mode 0 in
/usr/bin/gpio mode 1 in
/usr/bin/gpio mode 2 in

/usr/bin/gpio mode 0 tri
/usr/bin/gpio mode 1 tri
/usr/bin/gpio mode 2 tri

cd $HOME/git/cosmic-array/bin

/usr/bin/espeak "Cosmic Array Sensor Online. Node name `hostname`" >/dev/null 2>&1 &

$HOME/git/cosmic-array/bin/shoreman >/dev/null 2>&1 


