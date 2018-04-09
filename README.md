# SOUND SENSOR APPLICATION

This application is created as a course project for the Application Development course at Vaasa University of Applied Sciences (VAMK).
It is meant to collect the sound level in the proximity of the Raspberry Pi.
It records one second of audio at 16000Hz sample rate, calculates 80 RMS values for the sound level, and outputs them as a bar graph to the terminal window.

## Table of Contents
1. Configuration
2. Installation
3. Operation
4. Manifest (list of files and short description of their roles)
5. License
6. Contact information

## Pre-installation configuration 

The application is built for Raspberry Pi 3 running Raspbian. In addition, a USB sound card (for example, C-Media Electronics Audio Adapter) and a microphone is required. Superuser privileges are required to perform some configuration. 

### Set USB sound card as default

The USB sound card must be set as the Raspberry Pi's default audio device, as the on-board sound card doesn't have a microphone interface. 

Plug in the USB sound card into the Raspberry Pi, then use the command 

	lsusb

to check that the sound card is mounted. In the example below, the "C-Media Electronics, Inc. Audio Adapter" is the sound card:

	Bus 001 Device 004: ID 0d8c:000c C-Media Electronics, Inc. Audio Adapter
	Bus 001 Device 003: ID 0424:ec00 Standard Microsystems Corp. SMSC9512/9514 Fast Ethernet Adapter
	Bus 001 Device 002: ID 0424:9514 Standard Microsystems Corp. SMC9514 Hub
	Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

After checking that the USB sound card is mounted correctly, edit the asound.conf file to set the sound card as default:

	 sudo nano /etc/asound.conf

Insert the following content into the file:

	pcm.!default {
	  type plug
	  slave {
	    pcm "hw:1,0"
	  }
	}
	ctl.!default {
	    type hw
	    card 1
	}

Then add the same content to the .asoundrc file in your home directory. If the file is empty/doesn't exist, you can use:

	cp /etc/asound.conf ~/.asoundrc

Then, run

	alsamixer

to check that the USB sound card is set as default audio device. The name of the sound card (as seen from lsusb) should be visible under "Card". Press ESC to exit when you have verified that the sound card is set as default. 

### Fix arecord bug (for version 1.0.28).

**Before reading this section, check your alsa-utils version:**

	apt-cache policy alsa-utils

**If the version is earlier or later than 1.0.28, you should be able to safely skip this section. If the version shown in 1.0.28, please follow the instructions in this section.**

Version 1.0.28 of alsa-utils (the default version in Raspbian 8 Jessie) contains a bug that doesn't stop the recording in arecord even when a --duration flag is given. To fix this, alsa-utils has to be downgraded to version 1.0.25, as instructed below.

Edit the file /etc/apt/sources.list:

	sudo nano /etc/apt/sources.list

Add the following line at the end of the file:

	deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi

Use Ctrl-O, Enter, Ctrl-X to save the file and exit nano.

Next, run:

	sudo apt-get update

Check if alsa-utils version 1.0.25 is available:

	aptitude versions alsa-utils

(1.0.25 should be displayed in the output)
Run the following command to downgrade:

	sudo apt-get install alsa-utils=1.0.25-4

It may be a good idea to reboot the Raspberry Pi at this point.

	sudo reboot

Run the following command to verify that arecord and the microphone are working:

	arecord -r44100 -c1 -f S16_LE -d5 test.wav

There should now be a file called test.wav in the current directory. Listen to it using headphones to verify that everything is working:

	aplay test.wav

### Install libcurl

Run the following commands to check if libcurl is already installed:

	ls /usr/include/curl

	ls /usr/include/arm-linux-gnueabihf/curl

If either of these directories contain files, libcurl should already be installed. Otherwise, run the following commands to install libcurl:

	sudo apt-get update
	sudo apt-get install libcurl3
	sudo apt-get install libcurl4-openssl-dev

### Install git

Run the following command to install git if it is not already installed:

	sudo apt-get install git

## Installation

The easiest way to install the application is to clone the github repository (this requires git to be installed as detailed above). It is fine to clone it to the home directory or a subdirectory of the home directory.
Run the following command to clone:

	git clone https://github.com/dgrankvist/sound-detect

Run the following command to install:

	make

## Operation

Run the application with the command:

	./sound.a

You should see the bar graph. In addition, the data is saved to a php page detailed in the file comm.h.

Press Ctrl-C to exit the program.

## Manifest

The application contains the following files:
* comm.c - source code for the function that calculates 8 samples per second to send to a php server
* comm.h - header file for server communication
* main.c - the main function source code file
* makefile - contains compilation instructions for the program. Run "make" to install, "make clean" to remove additional files from the directory, "make archive" to package the files into a tarball.
* README.md - this README file
* screen.c - source code for the file that controls output to the terminal window
* screen.h - header file for the screen control functions
* sound.c - source code for doing the recording, analyzing the recording and outputing information
* sound.h - header file for processing the sound recording 

## License

This information will be added later

## Contact information

Daniel Grankvist

daniel.grankvist@edu.vamk.fi

http://www.cc.puv.fi/~e1700675/
