# rpi-kmod
Example code for a diagnostic Raspberry Pi OS Linux Kernel Driver (Version 5)

This serves as a starting point for developing Linux Kernel Modules for the Raspberry Pi.

It was built using the standard `make`, `build-essential`, `arm-linux-gnueabihf-gcc` and `raspberrypi-kernel-headers` from the Raspbian repository.

A text file is written to /home/pi/Desktop/logfile.txt by default.

`make` - builds the Kernel Module

`make install` - installs the Kernel Module into Linux (if `make` was successful)

`make status` - checks the status of all Kernel Modules (output of `printk()`)

`make remove` - uninstalls the Kernel Module from Linux (if previously installed)

`make clean` - clears up all intermediate files of the Kernel Module
