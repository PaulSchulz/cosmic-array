#!/bin/bash
# Name: start-setup.sh
cd ${0%/*} 

#######################################################################
# Set GPIO mode
/usr/bin/gpio mode 0 in
/usr/bin/gpio mode 1 in
/usr/bin/gpio mode 2 in

/usr/bin/gpio mode 0 tri
/usr/bin/gpio mode 1 tri
/usr/bin/gpio mode 2 tri

#######################################################################
# Set audio volume
sudo amixer -c 0 set PCM playback 70% unmute >/dev/null 2>&1

#######################################################################
# Set soundscape audio
if [ -d  audio/`hostname` ]; then
	rm audio/channel0.wav; ln -s `hostname`/channel0.wav audio/channel0.wav
	rm audio/channel1.wav; ln -s `hostname`/channel1.wav audio/channel1.wav
	rm audio/channel2.wav; ln -s `hostname`/channel2.wav audio/channel2.wav
else
	rm audio/channel0.wav; ln -s default/channel0.wav audio/channel0.wav
	rm audio/channel1.wav; ln -s default/channel1.wav audio/channel1.wav
	rm audio/channel2.wav; ln -s default/channel2.wav audio/channel2.wav
fi
