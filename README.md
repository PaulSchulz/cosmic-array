# Cosmic-Array
## Introduction

This repository holds the code, source and data for the 'cosmic-array'
project. More details can be found on the project website on HackaDay.

  https://hackaday.io/project/16568-cosmic-array

This is still an active work-in-progress so expect frequent changes.

## Installation

To install on a Raspberry Pi which has access to the Internet, checkout this repository in a git
sub-directory, build (with make) and run the 'install.sh' script.

### Dependancies
The following Raspbian packages are required (use apt install):
```
build-essential
espeak
```
### Install Process
```
cd
mkdir git
cd git
git clone https://github.com/PaulSchulz/cosmic-array.git
cd cosmic-array
cd config
./install.sh
```
## Features
- System Setup
	- Setup GPIO PWM for audio output (via overlay).
	- Set audio volume to 100%.
	- Setup program to run at boot via crontab.
	- Speaks the sensor node name after booting (via espeak).
- Sensor
	- Play audio when triggered via GPIO interupt.
- Testing
	- Simulate hardware events by manipulating GPIO levels. 
	
### Features under Development
- IoT
	- Transmit event data to a collector (server).
	- Configuration and Updates via Ansible.
- Event Database
  	- Record data from events for later analysis.
	- Output event data in other formats (CSV,Midi etc.)

## Development
### Building the code
```
cd git/cosmic-array/src
make
```
