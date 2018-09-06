#!/bin/bash

cd ${0%/*}

sudo apt update
sudo apt install build-essential
sudo apt install wiringpi

sudo apt install git
# Git should already be installed, but if it isn't, install it now.

ssh-keygen
# SSH Key rquired for submitting changes back to github.

sync; sync
